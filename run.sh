#!/usr/bin/env bash

server_pid=

function run_server()
{
    local server=build/src/server

    if ! [ -e "${server}" ]; then
        echo "Error. No ${server} found."
        exit 1
    fi

    ./${server}&
    server_pid=$!
}

function run_client()
{
    local client=build/src/client

    if ! [ -e "${client}" ]; then
        echo "Error. No ${client} found."
        exit 1
    fi

    if [ "$#" == "0" ]; then
        ./${client}
    else
        ./${client} "$*"
    fi
}

run_server
run_client Buddy
run_client Friend
run_client
set -x
kill -s SIGTERM $server_pid
set +x
