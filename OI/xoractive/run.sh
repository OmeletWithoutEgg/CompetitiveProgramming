#!/bin/bash

g++ -std=c++17 -Ofast -Dlocal -Wall -Wextra -Wfatal-errors -fsanitize=undefined -fsanitize=address -o grader grader.cpp solution.cpp
./grader
