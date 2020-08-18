g++ -std=c++17 gen.cpp -o gen
g++ -std=c++17 sol.cpp -o sol
g++ -std=c++17 subtask.cpp -o subtask
echo "files compiled successfully"

# for i in $(seq 1 5); do
# 	./gen 5 10 > $i.in
# done
# for i in $(seq 6 10); do
# 	./gen 10 45 > $i.in
# done
# for i in $(seq 11 15); do
# 	./gen 15 105 > $i.in
# done
# for i in $(seq 16 30); do
#  	./gen 18 153 > $i.in
#  done
# echo "test cases generated successfully"

for i in $(seq 1 30); do
	./sol < $i.in > $i.out
	echo $i OK
done
echo "the judgement solution have been outputed"

for i in $(seq 1 30); do
	./subtask < $i.in > tmp-$i.out
	echo $i OK
done
echo "the n*3^n solution have been outputed"

