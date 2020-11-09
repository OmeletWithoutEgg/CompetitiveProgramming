#include<bits/stdc++.h>

extern int64_t find_k(int64_t N) ;
namespace checker {
    int64_t L, R, N;
    int64_t Limit, Cost;
    int Subtask;
    std::vector<int64_t> testdata;
    void fail(std::string errMsg) {
        std::cerr << "Fail. " << errMsg << std::endl;
        exit(0);
    }
    void init() {
        std::cin >> Subtask;
        switch(Subtask) {
            case 1:
                N = 1e12;
                break;
            case 2:
                N = 1e5;
                break;
            case 3:
            case 4:
                N = 1e14;
                break;
        }
        int tc;
        std::cin >> tc;
        testdata.resize(tc);
        for(int64_t &K: testdata) std::cin >> K;
    }
    std::function<bool(int)> Compare;
    void test(int64_t K) {
        Cost = 0;
        switch(Subtask) {
            case 1:
                Limit = 4 * N * std::__lg(N);
                break;
            case 2:
                Limit = std::max(8000, 400 + 4 * int(pow(K, 1.5)));
                break;
            case 3:
                Limit = 4 * K * (std::__lg(K) + 1) * (std::__lg(K) + 1);
                break;
            case 4:
                Limit = 4 * K * (std::__lg(K) + 1);
                break;
        }
        Compare = [&](int64_t X) -> bool {
            if(X < 1 || X > N) {
                fail("Query out of bound");
            }
            if(Cost + X > Limit) {
                fail("Too many queries");
            }
            Cost += X;
            if(X > K) {
                R = X-1;
                return true;
            } else {
                L = X;
                return false;
            }
        };
        L = 1, R = N;
        if(find_k(N) != K) {
            fail("Wrong K!");
        }
        if(L != R) {
            fail("You are just guessing blindly!");
        }
    }
    void testall() {
        for(int64_t K: testdata) {
            test(K);
        }
        std::cout << "OK no testdata failed" << std::endl;
    }

}

bool Compare(int64_t X) {
    return checker::Compare(X);
}

int main() {
    checker::init();
    checker::testall();
}
