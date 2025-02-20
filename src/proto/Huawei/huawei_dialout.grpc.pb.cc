// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: huawei_dialout.proto

#include "huawei_dialout.pb.h"
#include "huawei_dialout.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace huawei_dialout {

static const char* gRPCDataservice_method_names[] = {
  "/huawei_dialout.gRPCDataservice/dataPublish",
};

std::unique_ptr< gRPCDataservice::Stub> gRPCDataservice::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< gRPCDataservice::Stub> stub(new gRPCDataservice::Stub(channel, options));
  return stub;
}

gRPCDataservice::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_dataPublish_(gRPCDataservice_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::ClientReaderWriter< ::huawei_dialout::serviceArgs, ::huawei_dialout::serviceArgs>* gRPCDataservice::Stub::dataPublishRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::huawei_dialout::serviceArgs, ::huawei_dialout::serviceArgs>::Create(channel_.get(), rpcmethod_dataPublish_, context);
}

void gRPCDataservice::Stub::async::dataPublish(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::huawei_dialout::serviceArgs,::huawei_dialout::serviceArgs>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::huawei_dialout::serviceArgs,::huawei_dialout::serviceArgs>::Create(stub_->channel_.get(), stub_->rpcmethod_dataPublish_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::huawei_dialout::serviceArgs, ::huawei_dialout::serviceArgs>* gRPCDataservice::Stub::AsyncdataPublishRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::huawei_dialout::serviceArgs, ::huawei_dialout::serviceArgs>::Create(channel_.get(), cq, rpcmethod_dataPublish_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::huawei_dialout::serviceArgs, ::huawei_dialout::serviceArgs>* gRPCDataservice::Stub::PrepareAsyncdataPublishRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::huawei_dialout::serviceArgs, ::huawei_dialout::serviceArgs>::Create(channel_.get(), cq, rpcmethod_dataPublish_, context, false, nullptr);
}

gRPCDataservice::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      gRPCDataservice_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< gRPCDataservice::Service, ::huawei_dialout::serviceArgs, ::huawei_dialout::serviceArgs>(
          [](gRPCDataservice::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::huawei_dialout::serviceArgs,
             ::huawei_dialout::serviceArgs>* stream) {
               return service->dataPublish(ctx, stream);
             }, this)));
}

gRPCDataservice::Service::~Service() {
}

::grpc::Status gRPCDataservice::Service::dataPublish(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::huawei_dialout::serviceArgs, ::huawei_dialout::serviceArgs>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace huawei_dialout

