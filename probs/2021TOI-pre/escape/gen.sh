#!/bin/bash

rm tests/*
g++ src/gen.cpp -o gen -std=c++17 -Wall -Wextra && ./gen 7122 -o tests/

cat src/sample-1.in >tests/00.in
cat src/sample-1.in >tests/10.in
cat src/sample-2.in >tests/20.in
cat src/sample-2.in >tests/30.in
cat src/sample-3.in >tests/21.in
cat src/sample-3.in >tests/31.in

cat src/hack1.txt >tests/22.in
cat src/hack2.txt >tests/23.in
cat src/hack1.txt >tests/32.in
cat src/hack2.txt >tests/33.in

g++ src/sol.cpp -o sol -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast
g++ src/valid.cpp -o valid -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast

for i in $(seq -w 0 69); do
    ./valid <tests/$i.in
done

for i in $(seq -w 0 69); do
    echo "testcase" $i
    ./sol <tests/$i.in >>tests/$i.out
done

# g++ src/8e7.cpp -o 8e7 -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast
# g++ src/checker.cpp -o checker -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast
# for i in $(seq -w 0 69); do
#     ./8e7 <tests/$i.in >tmp.out
#     ./checker tmp.out tests/$i.in tests/$i.out
#     rm tmp.out
# done

rm gen
rm sol
rm valid
