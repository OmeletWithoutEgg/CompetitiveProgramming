#!/bin/bash

problem=sorting

g++ -O2 -std=c++17 -Wall -Wextra -Wfatal-errors -fsanitize=undefined -fsanitize=address -Dlocal -o $problem grader.cpp $problem.cpp
./$problem <sorting.in
cat sorting.out
# ./$problem
