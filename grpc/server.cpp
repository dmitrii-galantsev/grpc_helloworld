#include <grpc/status.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <iostream>
#include <memory>
#include <string>
#include "helloworld.grpc.pb.h"
// #include "helloworld.pb.h"

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
        std::cout << "RESPONSE: [" << message << "]\n";
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

    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main() {
    std::cout << "Server main entered\n";
    run_server(51234);

    return 0;
}
