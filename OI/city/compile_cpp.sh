#!/bin/bash

NAME=city

/usr/bin/g++ -Dlocal -std=c++17 -Wall -Wall -Wextra -Wshadow -Wfatal-errors -Ofast -fsanitize=undefined -fsanitize=address -o $NAME grader.cpp $NAME.cpp
