#!/usr/bin/fish
cmake --build build
build/netlearn $argv[1]
