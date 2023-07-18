#!/usr/bin/env bash

set -xeu
cmake -B build
make -C build -j "$(nproc)"
