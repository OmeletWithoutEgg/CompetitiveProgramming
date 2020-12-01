#include <cstdlib>
#include <iostream>
int secret_ans,ans_max;

int Initialize(){srand(time(NULL)),ans_max = 2000000000,secret_ans = rand()%ans_max+1;}
int Guess(int q){return q >= secret_ans;}
void Report(int n){std::cout << ((n == secret_ans)?"AC":"WA") << ", ans is " << secret_ans << '\n';}
