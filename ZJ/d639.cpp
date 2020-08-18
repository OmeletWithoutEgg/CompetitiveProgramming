#include <iostream>
#include <iomanip>
#define MAX_SIZE (3)
#define MOD 10007
#define DEBUG

using namespace std;

struct Matrix{
    int val[MAX_SIZE][MAX_SIZE];
    Matrix& operator=(Matrix );
    Matrix operator*(Matrix &);
    inline Matrix operator*=(Matrix &);
    Matrix operator^(uint32_t);
};

inline Matrix O(void){
    Matrix m;
    for(int i = 0;i < MAX_SIZE;i++)
        for(int j = 0;j < MAX_SIZE;j++)
            m.val[i][j] = 0;
    return m;
}

inline Matrix I(void){
    Matrix m;
    for(int i = 0;i < MAX_SIZE;i++)
        for(int j = 0;j < MAX_SIZE;j++)
            m.val[i][j] = (i == j);
    return m;
}

Matrix& Matrix::operator=(Matrix f){
    for(int i = 0;i < MAX_SIZE;i++)
        for(int j = 0;j < MAX_SIZE;j++)
            val[i][j] = f.val[i][j];
    return *this;
}

Matrix Matrix::operator*(Matrix &f){
    Matrix m = O();
    for(int i = 0;i < MAX_SIZE;i++)
        for(int j = 0;j < MAX_SIZE;j++)
            for(int k = 0;k < MAX_SIZE;k++)
                m.val[i][j] += val[i][k] * f.val[k][j],m.val[i][j] %= MOD;
    return m;
}

inline Matrix Matrix::operator*=(Matrix &f){
    Matrix m = *this * f;
    return *this = m;
}

Matrix Matrix::operator^(uint32_t p){
    Matrix r = I();
    Matrix e = *this;
    while(p){
        if(p & 1)r *= e;
        e *= e;
        p >>= 1;
    }
    return r;
}

Matrix f = {.val =
                {   1,1,1,
                    1,0,0,
                    0,1,0   }
            };

int main(){
    Matrix t = O();
    #ifdef DEBUG
    for(int k = 0;k < 100;k++,cout << endl)
        for(int i = 0;i < MAX_SIZE;i++,cout << endl)
            for(int j = 0;j < MAX_SIZE;j++)
                {t = f ^ k;cout << setw(2) << t.val[i][j] << ' ';}
    #endif // DEBUG
    //for(int i = 0;i < 100;i++)t = f ^ i,cout << t.val[2][0] + t.val[2][1] + t.val[2][2] << endl;
    uint32_t n;
    cin >> n;
    t = f ^ (n - 1);
    cout << (t.val[2][0] + t.val[2][1] + t.val[2][2]) % MOD << endl;

    return 0;
}
