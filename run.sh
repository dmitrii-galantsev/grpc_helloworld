#!/usr/bin/env bash

server_pid=

function run_server()
{
    local server=build/grpc/server

    if ! [ -e "${server}" ]; then
        echo "Error. No ${server} found."
        exit 1
    fi

    ./${server}&
    server_pid=$!
}

function run_client()
{
    local client=build/grpc/client

    if ! [ -e "${client}" ]; then
        echo "Error. No ${client} found."
        exit 1
    fi

    ./${client}
}

run_server
run_client
set -x
kill -s SIGTERM $server_pid
set +x
