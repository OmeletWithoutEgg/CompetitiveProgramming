#!/bin/bash

problem=paint

g++ -std=c++17 -Wall -Wextra -Wfatal-errors -O2 -fsanitize=undefined -fsanitize=address -Dlocal -o $problem grader.cpp $problem.cpp
./$problem
