#!/bin/bash

g++ -std=gnu++17 -Dlocal -Wall -Wextra -Wfatal-errors -fsanitize=undefined -fsanitize=address -O3 -o grader grader.cpp monster.cpp

./grader <sample-01-in.txt
