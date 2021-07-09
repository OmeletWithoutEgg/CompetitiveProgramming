#!/bin/bash
g++ -std=gnu++17 -O2 -fsigned-char -Dlocal -o grader grader.cpp escape_route.cpp

for i in $(seq 1 3); do
    echo "Testcase #"$i
    echo "==========="
    ./grader <sample-0$i-in.txt
    echo "==========="
    cat sample-0$i-out.txt
done
