#include <iostream>
#include <fstream>
#include "cisco_dialout.grpc.pb.h"
#include "cisco_telemetry.pb.h"
#include <json/json.h>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;



int cisco_gpbkv2json(
    const std::unique_ptr<cisco_telemetry::Telemetry>& cisco_tlm,
    std::string& json_str_out);
Json::Value cisco_gpbkv_field2json(
                                const cisco_telemetry::TelemetryField& field);
void google_serialize(
    const std::unique_ptr<cisco_telemetry::Telemetry>& cisco_tlm,
    std::string& json_str_out);

    

int main(int argc, char *args[]) {
    if (argc < 2) {
        std::cout << "No input file provided" <<std::endl;
        return -1;
    }

    std::string input_file = args[1];
    std::ifstream input_stream(input_file);
    
    std::unique_ptr<cisco_telemetry::Telemetry> cisco_tlm(
                new cisco_telemetry::Telemetry());
    std::string json_str_out;
    cisco_tlm->ParseFromIstream(&input_stream);

    int num_warmpup = 1000;
    int num_iterations = 10000;
    std::cout << "Warm up for google serialize" << std::endl;
    for (int i = 0; i < num_warmpup; i++) {
        google_serialize(cisco_tlm, json_str_out);
    }
    std::cout << "Benchmarking google serialize" << std::endl;
    int64_t google_sum = 0;
    for (int i = 0; i < num_iterations; i++) {
        auto t1 = high_resolution_clock::now();
        google_serialize(cisco_tlm, json_str_out);
        auto t2 = high_resolution_clock::now();
        auto ns_int = duration_cast<nanoseconds>(t2 - t1);
        google_sum += ns_int.count();
    }
    std::cout << "Google total time: " << google_sum << " for " << num_iterations << " iterations " << google_sum / num_iterations<< "ns/iter" << std::endl;
    std::cout << "Warm up for Custom serialize" << std::endl;
    for (int i = 0; i < num_warmpup; i++) {
        cisco_gpbkv2json(cisco_tlm, json_str_out);
    }
    std::cout << "Benchmarking custom serialize" << std::endl;
    int64_t cust_sum = 0;
    for (int i = 0; i < num_iterations; i++) {
        auto t1 = high_resolution_clock::now();
        cisco_gpbkv2json(cisco_tlm, json_str_out);
        auto t2 = high_resolution_clock::now();
        auto ns_int = duration_cast<nanoseconds>(t2 - t1);
        cust_sum += ns_int.count();
    }
    std::cout << "Custom total time: " << cust_sum << " for " << num_iterations << " iterations " << cust_sum / num_iterations << "ns/iter" << std::endl;

    return 0;
}


void google_serialize(
    const std::unique_ptr<cisco_telemetry::Telemetry>& cisco_tlm,
    std::string& json_str_out)
{
    google::protobuf::util::JsonOptions opt;
    google::protobuf::util::MessageToJsonString(
                                                *cisco_tlm,
                                                &json_str_out,
                                                opt);
}




Json::Value cisco_gpbkv_field2json(
                                const cisco_telemetry::TelemetryField& field)
{
    Json::Value root;
    // gpbkv allows for nested kv fields, we recursively decode each one of them.
    Json::Value sub_fields;
    for (const cisco_telemetry::TelemetryField& sub_field: field.fields()) {
        Json::Value sub_field_value =
            cisco_gpbkv_field2json(sub_field);
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


int cisco_gpbkv2json(
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
        Json::Value value = cisco_gpbkv_field2json(field);
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
