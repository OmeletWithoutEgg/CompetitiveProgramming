#!/bin/bash

problem=jumps
grader_name=stub

g++ -std=gnu++17 -O2 -pipe -Dlocal -Wall -Wextra -Wfatal-errors -fsanitize=undefined -fsanitize=address -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
./jumps <../samples/sample-1.in
./jumps <../samples/sample-2.in
# echo "naive"
# ./naive <../samples/sample-2.in
