#!/bin/bash

g++ gen.cpp -o gen -std=c++17 -Wall -Wextra && ./gen 7122

cat sample-1.in >10.in
cat sample-2.in >11.in

rm sol && g++ sol.cpp -o sol -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast

for i in $(seq -w 0 39); do
    ./sol <$i.in >$i.out
done
