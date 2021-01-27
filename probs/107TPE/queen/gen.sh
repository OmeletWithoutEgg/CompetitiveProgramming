#!/bin/bash

rm tests/* -r
g++ src/gen.cpp -o gen -std=c++17 -Wall -Wextra && ./gen 7122 -o tests/

cat src/sample-1.in >tests/10.in
cat src/sample-2.in >tests/11.in

g++ src/sol.cpp -o sol -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast

for i in $(seq -w 0 39); do
    ./sol <tests/$i.in >tests/$i.out
done

rm gen
rm sol

g++ src/naive.cpp -o naive -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast
for i in $(seq -w 0 39); do
    ./naive <tests/$i.in >tests/tmp.out
    diff tests/tmp.out tests/$i.out
    rm tests/tmp.out
done

# mkdir tests/images
# g++ src/visualSol.cpp -o visualSol -std=c++17 -Wall -Wextra
# for i in $(seq -w 0 39); do
#     ./visualSol <tests/$i.in -o tests/images/$i.svg
# done
# rm visualSol
