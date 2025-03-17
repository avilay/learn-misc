#!/usr/bin/fish
cmake --build build
build/multiplex $argv[1] $argv[2] $argv[3]
