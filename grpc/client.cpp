#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <memory>
#include <string>
#include "helloworld.grpc.pb.h"
#include "helloworld.pb.h"

int main() {
    // prepare request
    std::shared_ptr<grpc::Channel> channel;
    channel = grpc::CreateChannel(
        "localhost:51234", grpc::InsecureChannelCredentials());
    auto stub = Greeter::NewStub(channel);
    grpc::ClientContext context;
    auto request = HelloRequest();
    request.set_name("Lame guy");
    auto response = HelloResponse();

    SPDLOG_INFO("REQUEST: [{}]", request.name());

    // send request
    stub->SayHello(&context, request, &response);

    // std::cout << "RESPONSE: [" << response.message() << "]" << std::endl;
    SPDLOG_INFO("RESPONSE: [{}]", response.message());

    return 0;
}
