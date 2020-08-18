g++ -std=c++17 gen.cpp -o gen
g++ -std=c++17 sol.cpp -o sol
echo "files compiled successfully"

for i in $(seq 1 10); do
	./gen 9 > $i.in;
done

for i in $(seq 11 20); do
	./gen 100 > $i.in;
done

for i in $(seq 21 30); do
	./gen 4000 > $i.in;
done

for i in $(seq 31 40); do
	./gen 200000 > $i.in;
done
echo "test cases generated successfully"

for i in $(seq 1 40); do
	./sol < $i.in > $i.out;
done
echo "the judgement solution have been outputed"