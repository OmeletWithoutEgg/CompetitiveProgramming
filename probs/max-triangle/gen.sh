#!/bin/bash

# rm tests/* -r
# mkdir tests/pics
g++ src/gen.cpp -o gen -std=c++17 -Wall -Wextra && ./gen JIZZ -o tests/ -n 9 -c 10000

g++ src/sol.cpp -o sol -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast
g++ src/zck.cpp -o zck -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast
g++ src/eric.cpp -o eric -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast

# cat src/01.in >tests/01.in

for i in {000..999}; do
    echo "Testcase " $i
    ./sol <tests/$i.in >tests/$i.out
    # echo "ERIC"
    ./eric <tests/$i.in | diff --color=auto tests/$i.out - || echo "ERIC"
    # echo "ZCK";
    # ./zck <tests/$i.in | diff --color=auto tests/$i.out - || echo "ZCK"
done

rm gen
rm sol
rm zck
rm eric
