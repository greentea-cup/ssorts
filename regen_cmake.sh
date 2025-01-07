#!/bin/bash
rm -r build
cmake --preset Release -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_TESTS=ON
cmake --preset Debug -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON
[ -f compile_commands.json ] && rm compile_commands.json
ln -s build/Release/compile_commands.json .
# temp directory for external sort temp files
mkdir tmp
