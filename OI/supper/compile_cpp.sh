#!/bin/bash

NAME=supper

/usr/bin/g++ -Dlocal -fsanitize=undefined -fsanitize=address -Wall -Wextra -Wfatal-errors -Ofast -std=c++17 -o $NAME grader.cpp assistant.cpp advisor.cpp
