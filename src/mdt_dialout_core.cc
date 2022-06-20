#include <iostream>
#include <fstream>
#include <thread>
#include <typeinfo>
#include <grpcpp/grpcpp.h>
#include "grpc/socket_mutator.h"
#include <grpcpp/support/channel_arguments.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <json/json.h>
//#include <librdkafka/rdkafkacpp.h>
#include "kafka/KafkaProducer.h"
#include "mdt_dialout_core.h"
#include "cisco_dialout.grpc.pb.h"
#include "cisco_telemetry.pb.h"
#include "huawei_dialout.grpc.pb.h"
#include "huawei_telemetry.pb.h"
#include <google/protobuf/arena.h>
#include <google/protobuf/message.h>
#include <google/protobuf/util/json_util.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "cfg_handler.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;


bool CustomSocketMutator::bindtodevice_socket_mutator(int fd)
{
    int type;
    int length = sizeof(int);
    socklen_t len = sizeof(type);

    // --- Required for config parameters ---
    std::unique_ptr<MainCfgHandler> main_cfg_handler(new MainCfgHandler());
    std::string iface = main_cfg_handler->get_iface();
    // --- Required for config parameters ---

    if (getsockopt(fd, SOL_SOCKET, SO_TYPE, &type, &len) != 0) {
        //std::cout << "Issues with getting the iface type ..." << std::endl;
    }

    if (setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE,
                                iface.c_str(), strlen(iface.c_str())) != 0) {
        //std::cout << "Issues with iface binding for ..." << std::endl;
    }

    return true;
}

bool custom_socket_mutator_fd(int fd, grpc_socket_mutator *mutator0) {
    CustomSocketMutator *csm = (CustomSocketMutator *)mutator0;
    return csm->bindtodevice_socket_mutator(fd);
}

#define GPR_ICMP(a, b) ((a) < (b) ? -1 : ((a) > (b) ? 1 : 0))
int custom_socket_compare(grpc_socket_mutator *mutator1,
                                grpc_socket_mutator *mutator2)
{
    return GPR_ICMP(mutator1, mutator2);
}

void custom_socket_destroy(grpc_socket_mutator *mutator)
{
    gpr_free(mutator);
}

const grpc_socket_mutator_vtable
        custom_socket_mutator_vtable = grpc_socket_mutator_vtable{
                                    custom_socket_mutator_fd,
                                    custom_socket_compare,
                                    custom_socket_destroy,
                                    nullptr};

void ServerBuilderOptionImpl::UpdateArguments(
                                        grpc::ChannelArguments *custom_args) {
    CustomSocketMutator *csm_ = new CustomSocketMutator();
    custom_args->SetSocketMutator(csm_);
}

CustomSocketMutator::CustomSocketMutator() {
    grpc_socket_mutator_init(this, &custom_socket_mutator_vtable);
}

Srv::~Srv()
{
    cisco_server_->grpc::ServerInterface::Shutdown();
    huawei_server_->grpc::ServerInterface::Shutdown();
    cisco_cq_->grpc::ServerCompletionQueue::Shutdown();
    huawei_cq_->grpc::ServerCompletionQueue::Shutdown();
}

void Srv::CiscoBind(std::string cisco_srv_socket)
{
    grpc::ServerBuilder cisco_builder;
    cisco_builder.RegisterService(&cisco_service_);
    std::unique_ptr<ServerBuilderOptionImpl>
                                        csbo(new ServerBuilderOptionImpl());
    cisco_builder.SetOption(std::move(csbo));
    cisco_builder.AddListeningPort(cisco_srv_socket,
                                grpc::InsecureServerCredentials());
    cisco_cq_ = cisco_builder.AddCompletionQueue();
    cisco_server_ = cisco_builder.BuildAndStart();

    std::thread t1(&Srv::CiscoFsmCtrl, this);
    std::thread t2(&Srv::CiscoFsmCtrl, this);
    std::thread t3(&Srv::CiscoFsmCtrl, this);

    t1.join();
    t2.join();
    t3.join();
}

void Srv::HuaweiBind(std::string huawei_srv_socket)
{
    grpc::ServerBuilder huawei_builder;
    huawei_builder.RegisterService(&huawei_service_);
    std::unique_ptr<ServerBuilderOptionImpl>
                                        hsbo(new ServerBuilderOptionImpl());
    huawei_builder.SetOption(std::move(hsbo));
    huawei_builder.AddListeningPort(huawei_srv_socket,
                                grpc::InsecureServerCredentials());
    huawei_cq_ = huawei_builder.AddCompletionQueue();
    huawei_server_ = huawei_builder.BuildAndStart();

    std::thread t1(&Srv::HuaweiFsmCtrl, this);
    std::thread t2(&Srv::HuaweiFsmCtrl, this);
    std::thread t3(&Srv::HuaweiFsmCtrl, this);

    t1.join();
    t2.join();
    t3.join();
}

void Srv::CiscoFsmCtrl()
{
    new Srv::CiscoStream(&cisco_service_, cisco_cq_.get());
    int cisco_counter {0};
    void *cisco_tag {nullptr};
    bool cisco_ok {false};
    while (true) {
        //std::cout << "Cisco: " << cisco_counter << std::endl;
        GPR_ASSERT(cisco_cq_->Next(&cisco_tag, &cisco_ok));
        if (!cisco_ok) {
            static_cast<CiscoStream *>(cisco_tag)->Srv::CiscoStream::Stop();
            continue;
        }
        static_cast<CiscoStream *>(cisco_tag)->Srv::CiscoStream::Start();
        //cisco_counter++;
    }
}

void Srv::HuaweiFsmCtrl()
{
    new Srv::HuaweiStream(&huawei_service_, huawei_cq_.get());
    int huawei_counter {0};
    void *huawei_tag {nullptr};
    bool huawei_ok {false};
    while (true) {
        //std::cout << "Huawei: " << huawei_counter << std::endl;
        GPR_ASSERT(huawei_cq_->Next(&huawei_tag, &huawei_ok));
        if (!huawei_ok) {
            static_cast<HuaweiStream *>(huawei_tag)->Srv::HuaweiStream::Stop();
            continue;
        }
        static_cast<HuaweiStream *>(huawei_tag)->Srv::HuaweiStream::Start();
        //huawei_counter++;
    }
}

Srv::CiscoStream::CiscoStream(
                    mdt_dialout::gRPCMdtDialout::AsyncService *cisco_service,
                    grpc::ServerCompletionQueue *cisco_cq) :
                                        cisco_service_ {cisco_service},
                                        cisco_cq_ {cisco_cq},
                                        cisco_resp {&cisco_server_ctx},
                                        cisco_stream_status {START}
{
    Srv::CiscoStream::Start();
}

Srv::HuaweiStream::HuaweiStream(
                huawei_dialout::gRPCDataservice::AsyncService *huawei_service,
                grpc::ServerCompletionQueue *huawei_cq) :
                                        huawei_service_ {huawei_service},
                                        huawei_cq_ {huawei_cq},
                                        huawei_resp {&huawei_server_ctx},
                                        huawei_stream_status {START}
{
    Srv::HuaweiStream::Start();
}

void Srv::CiscoStream::Start()
{
    // Initial stream_status set to START
    if (cisco_stream_status == START) {
        cisco_service_->RequestMdtDialout(
                                        &cisco_server_ctx,
                                        &cisco_resp,
                                        cisco_cq_,
                                        cisco_cq_,
                                        this);
        cisco_stream_status = FLOW;
    } else if (cisco_stream_status == FLOW) {
        bool parsing_str;
        std::string stream_data_in;
        std::string stream_data_out;
        std::string peer = cisco_server_ctx.peer();

        std::unique_ptr<DataManipulation> data_manipulation(
                new DataManipulation());
        std::unique_ptr<DataDelivery> data_delivery(new DataDelivery());
        std::unique_ptr<cisco_telemetry::Telemetry> cisco_tlm(
                new cisco_telemetry::Telemetry());

        // the key-word "this" is used as a unique TAG
        cisco_resp.Read(&cisco_stream, this);
        // returns true for GPB-KV & GPB, false for JSON
        parsing_str = cisco_tlm->ParseFromString(cisco_stream.data());

        stream_data_in = cisco_stream.data();

        // Handling empty data
        if (stream_data_in.empty()) {
            // ---
            auto type_info = typeid(stream_data_in).name();
            std::cout << peer << " CISCO Handling empty data: " << type_info
                                                                << std::endl;
            // ---

        // Handling GPB-KV
        } else if (!(cisco_tlm->data_gpbkv().empty()) and parsing_str == true) {
            // ---
            auto type_info = typeid(stream_data_in).name();
            std::cout << peer << " CISCO Handling GPB-KV: " << type_info
                                                            << std::endl;
            // ---

            data_manipulation->cisco_gpbkv2json(cisco_tlm, stream_data_in);
            if (data_manipulation->append_label_map(stream_data_in,
                        stream_data_out) == 0) {
                data_delivery->async_kafka_producer(stream_data_out);
            }

        // Handling GPB
        } else if (cisco_tlm->has_data_gpb() == true and parsing_str == true) {
            // ---
            auto type_info = typeid(stream_data_in).name();
            std::cout << peer << " CISCO Handling GPB: " << type_info
                                                        << std::endl;
            // ---

        // Handling JSON string
        } else {
            // ---
            auto type_info = typeid(stream_data_in).name();
            std::cout << peer << " CISCO Handling JSON string: " << type_info
                                                                << std::endl;
            // ---
            if (data_manipulation->append_label_map(stream_data_in,
                        stream_data_out) == 0) {
                data_delivery->async_kafka_producer(stream_data_out);
            }
        }
    } else {
        GPR_ASSERT(cisco_stream_status == END);
        delete this;
    }
}

void Srv::HuaweiStream::Start()
{
    if (huawei_stream_status == START) {
        huawei_service_->RequestdataPublish(
                                    &huawei_server_ctx,
                                    &huawei_resp,
                                    huawei_cq_,
                                    huawei_cq_,
                                    this);
        huawei_stream_status = FLOW;
    } else if (huawei_stream_status == FLOW) {
        bool parsing_str;
        std::string stream_data_in;
        std::string stream_data_out;
        std::string peer = huawei_server_ctx.peer();

        std::unique_ptr<DataManipulation> data_manipulation(
                new DataManipulation());
        std::unique_ptr<DataDelivery> data_delivery(new DataDelivery());
        std::unique_ptr<huawei_telemetry::Telemetry> huawei_tlm(
                                            new huawei_telemetry::Telemetry());

        huawei_resp.Read(&huawei_stream, this);
        parsing_str = huawei_tlm->ParseFromString(huawei_stream.data());

        stream_data_in = huawei_stream.data();

        // Handling empty data
        if (stream_data_in.empty()) {
            // ---
            auto type_info = typeid(stream_data_in).name();
            std::cout << peer << " HUAWEI Handling empty data: " << type_info
                                                                << std::endl;
            // ---
        }

        // Handling GPB
        else {
            if (!(huawei_tlm->has_data_gpb() == true and parsing_str == true)) {
                google::protobuf::util::JsonOptions opt;
                opt.add_whitespace = true;
                google::protobuf::util::MessageToJsonString(
                                                            *huawei_tlm,
                                                            &stream_data_in,
                                                            opt);
                // ---
                auto type_info = typeid(stream_data_in).name();
                std::cout << peer << " HUAWEI Handling GPB-KV: " << type_info
                                                                << std::endl;
                // ---
                if (data_manipulation->append_label_map(stream_data_in,
                            stream_data_out) == 0) {
                    data_delivery->async_kafka_producer(stream_data_out);
                }
            }
        }

        stream_data_in = huawei_stream.data_json();

        // Handling empty data_json
        if (stream_data_in.empty()) {
            // ---
            auto type_info = typeid(stream_data_in).name();
            std::cout << peer << " HUAWEI Handling empty data_json: "
                                                                << type_info
                                                                << std::endl;
            // ---
        }
        // Handling JSON string
        else {
            // ---
            auto type_info = typeid(stream_data_in).name();
            std::cout << peer << " HUAWEI Handling JSON string: " << type_info
                                                                << std::endl;
            // ---
            if (data_manipulation->append_label_map(stream_data_in,
                        stream_data_out) == 0) {
                data_delivery->async_kafka_producer(stream_data_out);
            }
        }
    } else {
        GPR_ASSERT(huawei_stream_status == END);
        delete this;
    }
}

void Srv::CiscoStream::Stop()
{
    //std::cout << "Streaming Interrupted ..." << std::endl;
    cisco_stream_status = END;
}

void Srv::HuaweiStream::Stop()
{
    //std::cout << "Streaming Interrupted ..." << std::endl;
    huawei_stream_status = END;
}

// forge JSON & enrich with MAP (node_id/platform_id)
int DataManipulation::append_label_map(const std::string& json_str,
                                    std::string& json_str_out)
{
    const auto json_str_length = static_cast<int>(json_str.length());
    JSONCPP_STRING err;
    Json::Value root;
    Json::CharReaderBuilder builderR;
    Json::StreamWriterBuilder builderW;
    builderW["indentation"] = "";
    const std::unique_ptr<Json::CharReader> reader(builderR.newCharReader());
    const std::unique_ptr<Json::StreamWriter> writer(
                                                builderW.newStreamWriter());
    Json::Value label_map;
    label_map["node_id"] = "node_id";
    label_map["platform_id"] = "platform_id";

    if (!reader->parse(json_str.c_str(), json_str.c_str() + json_str_length,
                      &root, &err) and json_str_length != 0) {
        std::cout << "ERROR parsing the string, conversion to JSON Failed!"
                                                                << err
                                                                << std::endl;
        std::cout << "Failing str : " << json_str << std::endl;
        return EXIT_FAILURE;
    }

    root["label"] = label_map;
    json_str_out = Json::writeString(builderW, root);

    return EXIT_SUCCESS;
}

int DataManipulation::cisco_gpbkv2json(
    const std::unique_ptr<cisco_telemetry::Telemetry>& cisco_tlm,
    std::string& json_str_out)
{
     Json::Value root;
    // First read the metadata defined in cisco_telemtry.proto
    if (cisco_tlm->has_node_id_str()) {
        root["node_id"] = cisco_tlm->node_id_str();
    }
    if (cisco_tlm->has_subscription_id_str()) {
        root["subscription_id"] = cisco_tlm->subscription_id_str();
    }
    root["encoding_path"] = cisco_tlm->encoding_path();
    root["collection_id"] = (Json::UInt64) cisco_tlm->collection_id();
    root["collection_start_time"] =
        (Json::UInt64) cisco_tlm->collection_start_time();
    root["msg_timestamp"] =
        (Json::UInt64) cisco_tlm->msg_timestamp();
    root["collection_end_time"] =
        (Json::UInt64) cisco_tlm->collection_end_time();

    // Iterate through the key/values in data_gpbkv
    Json::Value gpbkv;
    for (auto const& field: cisco_tlm->data_gpbkv()) {
        Json::Value value = DataManipulation::cisco_gpbkv_field2json(field);
        if (field.name().empty()) {
            gpbkv.append(value);
        } else {
            Json::Value json_field;
            json_field[field.name()] = value;
            gpbkv.append(json_field);
        }
    }
    root["data_gpbkv"] = gpbkv;

    // Serialize the JSON value into a string
    Json::StreamWriterBuilder builderW;
    builderW["indentation"] = "";
    const std::unique_ptr<Json::StreamWriter> writer(
                                                builderW.newStreamWriter());
    json_str_out = Json::writeString(builderW, root);

    return EXIT_SUCCESS;
}

Json::Value DataManipulation::cisco_gpbkv_field2json(
                                const cisco_telemetry::TelemetryField& field)
{
    Json::Value root;
    // gpbkv allows for nested kv fields, we recursively decode each one of them.
    Json::Value sub_fields;
    for (const cisco_telemetry::TelemetryField& sub_field: field.fields()) {
        Json::Value sub_field_value =
            DataManipulation::cisco_gpbkv_field2json(sub_field);
        Json::Value sub_field_json;
        if (sub_field.name().size() == 0) {
            sub_fields.append(sub_field_value);
        } else {
            sub_field_json[sub_field.name()] = sub_field_value;
            sub_fields.append(sub_field_json);
        }
    }

    // the value of the field can be one of several predefined types, or null.
    Json::Value value;
    if (field.has_bytes_value()) {
        value = field.bytes_value();
    } else if (field.has_string_value()) {
        value = field.string_value();
    } else if (field.has_bool_value()) {
        value = field.bool_value();
    } else if (field.has_uint32_value()) {
        value = field.uint32_value();
    } else if (field.has_uint64_value()) {
        value = (Json::UInt64) field.uint64_value();
    } else if (field.has_sint32_value()) {
        value = field.sint32_value();
    } else if (field.has_sint64_value()) {
        value = (Json::Int64) field.sint64_value();
    } else if (field.has_double_value()) {
        value = field.double_value();
    }  else if (field.has_float_value()) {
        value = field.float_value();
    }

    // timestamp is required field for each field, routers send zero for basic
    // fields (e.g., int64)
    if (field.timestamp() != 0) {
        root["timestamp"] = (Json::UInt64) field.timestamp();
    }

    // Clean up the output to send only the properties that have values
    if (!sub_fields.empty()) {
        root["fields"] = sub_fields;
    }
    if (!root.empty()) {
        if (!value.empty()) {
            root["value"] = value;
        }
        return root;
    }
    return value;
}

int DataDelivery::async_kafka_producer(const std::string& json_str)
{
    using namespace kafka::clients;

    // --- Required for config parameters ---
    std::unique_ptr<KafkaCfgHandler> kafka_cfg_handler(new KafkaCfgHandler());

    kafka::Topic topic =
                        kafka_cfg_handler->get_kafka_topic();
    std::string bootstrap_servers =
                        kafka_cfg_handler->get_kafka_bootstrap_servers();
    std::string enable_idempotence =
                        kafka_cfg_handler->get_kafka_enable_idempotence();
    std::string client_id =
                        kafka_cfg_handler->get_kafka_client_id();
    std::string security_protocol =
                        kafka_cfg_handler->get_kafka_security_protocol();
    std::string ssl_key_location =
                        kafka_cfg_handler->get_kafka_ssl_key_location();
    std::string ssl_certificate_location =
                        kafka_cfg_handler->get_kafka_ssl_certificate_location();
    std::string ssl_ca_location =
                        kafka_cfg_handler->get_kafka_ssl_ca_location();
    std::string log_level =
                        kafka_cfg_handler->get_kafka_log_level();
    // --- Required for config parameters ---

    try {
        // Additional kafka producer's config options here
        kafka::Properties properties ({
            {"bootstrap.servers",  bootstrap_servers},
            {"enable.idempotence", enable_idempotence},
            {"client.id", client_id},
            {"security.protocol", security_protocol},
            {"ssl.key.location", ssl_key_location},
            {"ssl.certificate.location", ssl_certificate_location},
            {"ssl.ca.location", ssl_ca_location},
            {"log_level", log_level},
        });

        KafkaProducer producer(properties);

        if (json_str.empty()) {
            // Implementing a better handling
            std::cout << "KAFKA - Empty JSON received " << std::endl;
            return EXIT_FAILURE;
        }

        auto msg = producer::ProducerRecord(topic,
                    kafka::NullKey,
                    kafka::Value(json_str.c_str(), json_str.size()));

        producer.send(
            msg,
            [](const producer::RecordMetadata& mdata,
                const kafka::Error& err) {
            if (!err) {
                std::cout << "Msg delivered: "
                        << mdata.toString() << std::endl;
            } else {
                std::cerr << "Msg delivery failed: "
                        << err.message() << std::endl;
            }
        }, KafkaProducer::SendOption::ToCopyRecordValue);
    } catch (const kafka::KafkaException& ex) {
        std::cerr << "Unexpected exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

