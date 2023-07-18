# Basic gRPC example

This program is vaguely based off <https://grpc.io/docs/languages/cpp/basics/>

## How to compile

1. `cmake -B build`
2. `make -C build -j $(nproc)`

## How to run

- `./build/grpc/server`

in another terminal run:

- `./build/grpc/client`
