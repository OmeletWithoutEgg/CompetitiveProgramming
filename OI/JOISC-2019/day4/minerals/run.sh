#!/bin/bash

rm grader
g++ -std=c++17 -Ofast -fsanitize=undefined -fsanitize=address -Wfatal-errors -o grader grader.cpp minerals.cpp
g++ gen.cpp -o gen

# for i in $(seq 1 1); do
# ./grader <sample-0$i-in.txt
# #cat sample-0$i-out.txt
# done

./gen | ./grader
