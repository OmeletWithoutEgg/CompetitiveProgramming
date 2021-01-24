#!/bin/bash

g++ src/gen.cpp -o gen -std=c++17 -Wall -Wextra && ./gen 7122 -o tests/

cat src/sample-1.in >tests/01.in
cat src/sample-2.in >tests/06.in

g++ src/sol.cpp -o sol -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast

for i in $(seq -w 0 39); do
    ./sol <tests/$i.in >tests/$i.out
done

rm gen
rm sol
