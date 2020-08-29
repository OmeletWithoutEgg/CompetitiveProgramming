#!/bin/bash

problem=simurgh

g++ -std=gnu++14 -O2 -Dlocal -pipe -static -o $problem grader.cpp $problem.cpp
