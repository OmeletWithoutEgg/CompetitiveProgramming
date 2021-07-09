#!/bin/bash

problem=biscuits
grader_name=grader

# g++ -std=gnu++17 -O2 -Wall -pipe -static -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
g++ -std=gnu++17 -Ofast -Dlocal -Wall -Wextra -Wfatal-errors -fsanitize=undefined -fsanitize=address  -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
