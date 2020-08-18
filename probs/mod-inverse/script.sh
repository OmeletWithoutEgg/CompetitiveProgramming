g++ -std=c++17 prime_gen.cpp -o prime_gen
g++ -std=c++17 gen.cpp -o gen
g++ -std=c++17 sol.cpp -o sol
echo "files compiled successfully"

for i in $(seq 1 5); do
	./prime_gen 10000 100 > $i.in
done

for i in $(seq 6 10); do
	./prime_gen 10000000 100000 > $i.in
done

for i in $(seq 11 21); do
	./gen 1000 1000 > $i.in
done

for i in $(seq 22 30); do
	./gen 1000000 100000 > $i.in
done

for i in $(seq 31 40); do
	./gen 1000000000 100000 > $i.in
done

echo "test cases generated successfully"

for i in $(seq 1 41); do
	./sol < $i.in > $i.out;
done
echo "the judgement solution have been outputed"