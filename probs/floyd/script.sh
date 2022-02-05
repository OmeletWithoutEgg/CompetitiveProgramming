#!/bin/bash
g++ -std=c++17 gen.cpp -o gen
g++ -std=c++17 sol.cpp -o sol
echo "files compiled successfully"

# for i in $(seq 1 6); do
# 	./gen 5 15 10 > $i.in
# done

# for i in $(seq 7 10); do
# 	./gen 100 900 1000 > $i.in
# done

# for i in $(seq 11 16); do
# 	./gen 200 1000 1000 > $i.in
# done

# for i in $(seq 17 25); do
# 	./gen 500 100000 1000000 > $i.in
# done
# echo "generated successfully"

for i in $(seq 1 25); do
	./sol < $i.in > $i.out
done
echo "solution files outputed"