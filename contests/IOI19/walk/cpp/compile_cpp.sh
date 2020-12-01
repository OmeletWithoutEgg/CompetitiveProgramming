#!/bin/bash

problem=walk

g++ -std=gnu++17 -O2 -Wall -Wshadow -Wextra -fsanitize=undefined -fsanitize=address -Dlocal -o "${problem}" "grader.cpp" "${problem}.cpp"
