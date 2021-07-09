#!/bin/bash

problem=roads
grader_name=grader

g++ -std=gnu++17 -O2 -pipe -Dlocal -Wall -Wextra -Wfatal-errors -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
./roads <../samples/sample-1.in
./roads <../samples/sample-2.in
./roads <../samples/big.in
