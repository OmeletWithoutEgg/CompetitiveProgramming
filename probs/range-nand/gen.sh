#!/bin/bash

rm tests/*
# g++ src/gen.cpp -o gen -std=c++17 -Wall -Wextra && ./gen 7122 -o tests/

g++ src/gen_full.cpp -o gen_full -std=c++17 -Wall -Wextra

for i in $(seq 0 4); do
    ./gen_full 100000 $i 30 >tests/$i.in
done

# cat src/sample-1.in >tests/10.in
# cat src/sample-2.in >tests/01.in
# cat src/sample-3.in >tests/02.in

g++ src/sol.cpp -o sol -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast
g++ src/val.cpp -o val -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast

g++ src/naive.cpp -o naive -std=c++17 -Wall -Wextra -Ofast
for i in $(seq 0 4); do
    ./val <tests/$i.in
    echo "return code" $?
done

for i in $(seq 0 4); do
    ./sol <tests/$i.in >tests/$i.out
done

for i in $(seq 0 4); do
    ./naive <tests/$i.in | diff tests/$i.out -
done
