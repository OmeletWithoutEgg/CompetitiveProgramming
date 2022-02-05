g++ src/valid.cpp -o valid -std=c++17 -Wall -Wextra -Dlocal -fsanitize=undefined -fsanitize=address -Ofast

for i in $(seq -w 0 29); do
    echo "Test #" $i
    ./valid <tests/$i.in
done
rm valid
