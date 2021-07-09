#!/bin/bash

problem=hexagon
grader_name=grader

g++ -std=gnu++17 -O2 -pipe -Dlocal -Wall -Wextra -Wfatal-errors -fsanitize=undefined -fsanitize=address -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
./hexagon <../samples/sample-1.in
