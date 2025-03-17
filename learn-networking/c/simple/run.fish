#!/usr/bin/fish
cmake --build build
build/simple $argv[1] $argv[2] $argv[3]
