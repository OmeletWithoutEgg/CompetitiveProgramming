#!/bin/bash

problem=aliens

g++ -Ofast -Dlocal -fsanitize=address -fsanitize=undefined -Wall -Wextra -Wfatal-errors -std=c++17 -o $problem grader.cpp $problem.cpp
./$problem
