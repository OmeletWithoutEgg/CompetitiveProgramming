#!/bin/bash

rm main
g++ main.cpp -o main -std=c++17 -Ofast -Wfatal-errors -fsanitize=undefined -fsanitize=address -Dlocal
g++ gen.cpp -o gen

./main <sample-01-in.txt
./main <sample-02-in.txt

./gen | ./main
