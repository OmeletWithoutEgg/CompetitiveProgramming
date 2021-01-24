#!/bin/bash

rm tests/*
g++ src/gen.cpp -o gen -std=c++17 -Wall -Wextra && ./gen 9487 -o tests/

cat src/sample-1.in >tests/01.in
cat src/sample-2.in >tests/03.in

cat src/handmade/01.in >tests/06.in
cat src/handmade/02.in >tests/08.in
cat src/handmade/03.in >tests/09.in

cat src/handmade/04.in >tests/25.in

g++ src/sol.cpp -o sol -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast

for i in $(seq -w 0 29); do
    ./sol <tests/$i.in >tests/$i.out
done

rm gen
rm sol
