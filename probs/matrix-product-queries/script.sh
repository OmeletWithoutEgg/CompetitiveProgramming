#!/bin/bash
g++ -std=c++17 gen.cpp -o gen
g++ -std=c++17 sol.cpp -o sol
echo "files compiled successfully"

for i in $(seq 1 3); do
	./gen 10 10 3 > $i.in
done

for i in $(seq 4 6); do
	./gen 10 10 1000 > $i.in
done

for i in $(seq 7 10); do
	./gen 1000 1000 100000 > $i.in
done

for i in $(seq 11 20); do
	./gen 10000 10000 10000000 > $i.in
done

for i in $(seq 21 30); do
	./gen 200000 200000 10000000 > $i.in
done

echo "generated successfully"

for i in $(seq 1 30); do
	./sol < $i.in > $i.out
done
echo "solution files outputed"