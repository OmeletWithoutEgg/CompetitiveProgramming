#!/bin/bash
g++ -std=c++17 gen.cpp -o gen
g++ -std=c++17 sol.cpp -o sol
echo "files compiled successfully"

echo "banana" > 1.in;
echo "aa" > 2.in
echo "ac" > 3.in

for i in $(seq 4 10); do
	./gen 1000 26 > $i.in;
done
for i in $(seq 11 20); do
	./gen 1000 3 > $i.in;
done

for i in $(seq 21 25); do
	./gen 100000 26 > $i.in;
done
for i in $(seq 26 30); do
	./gen 100000 5 > $i.in;
done

for i in $(seq 31 35); do
	./gen 1000000 26 > $i.in;
done
for i in $(seq 36 40); do
	./gen 1000000 2 > $i.in;
done
echo "test cases generated successfully"

for i in $(seq 1 40); do
	./sol < $i.in > $i.out;
done
echo "the judgement solution have been outputed"
