#!/bin/bash

EXE_FILE="./a.out"

[ -f "$EXE_FILE" ] && rm "$EXE_FILE"

clang++ --std=c++17 \
    -I"$(pwd)/../leftright/include/" \
    -I"$(pwd)/../eventbus/include/" \
    main.cc -o "$EXE_FILE" && "$EXE_FILE"
