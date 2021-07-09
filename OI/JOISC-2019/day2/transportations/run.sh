#!/bin/bash

rm trans
g++ -std=c++17 -Dlocal -Ofast -Wfatal-errors -fsanitize=undefined -fsanitize=address main.cpp grader.cpp -o trans
for i in $(seq 1 3); do
    echo "=== Testcase #"$i "==="
    echo "=== Your answer ==="
    ./trans <sample-0$i-in.txt
done
# echo "=== Real answer ==="
#    cat sample-0$i-out.txt
