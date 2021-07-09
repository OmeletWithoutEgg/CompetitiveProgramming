#!/bin/bash

TASK=doll

g++ -std=gnu++17 -Wall -Wextra -Wfatal-errors -Dlocal -fsanitize=undefined -fsanitize=address -O2 -o ${TASK} grader.cpp ${TASK}.cpp
./${TASK}
