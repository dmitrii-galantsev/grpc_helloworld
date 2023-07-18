#include <grpc/status.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <memory>
#include <string>
#include "helloworld.grpc.pb.h"

class SayHelloImpl final : public Greeter::Service {
 public:
    ~SayHelloImpl() override = default;
    ::grpc::Status SayHello(
        ::grpc::ServerContext* context,
        const ::HelloRequest* request,
        ::HelloResponse* response) override {
        const std::string message =
            "Hello " + request->name() + " <" + context->peer() + ">";
        response->set_message(message);
        SPDLOG_DEBUG("RESPONSE: [{}]", message);
        return grpc::Status::OK;
    }
};

void run_server(int port) {
    SayHelloImpl service;
    grpc::ServerBuilder builder;

    std::string server_address("0.0.0.0:" + std::to_string(port));

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    SPDLOG_INFO("Server listening on <{}>", server_address);
    server->Wait();
}

int main() {
    spdlog::set_level(spdlog::level::trace);
    SPDLOG_DEBUG("Server started");
    run_server(51234);

    return 0;
}
