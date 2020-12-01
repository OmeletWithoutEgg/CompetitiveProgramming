#!/bin/bash

problem=vision

g++ -std=gnu++17 -O2 -Wall -fsanitize=undefined -fsanitize=address -Dlocal -o "${problem}" "grader.cpp" "${problem}.cpp"
