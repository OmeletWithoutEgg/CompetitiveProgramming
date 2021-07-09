#!/bin/bash
g++ -Wall -Wextra -Ofast -Wfatal-errors -Dlocal -o eastereggs -O2 eggs.cpp grader.cpp -std=c++17 && ./eastereggs
