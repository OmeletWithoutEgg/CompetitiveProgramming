#include <bits/stdc++.h>
#define cnv(C) ((C == 'O')?1:(C == 'X')?-1:0)
#define acnv(X) ((X == 1)?'O':(X == -1)?'X':'-')
using namespace std;

int Owin = 0,Xwin = 0,Tie = 0;
int board[9] = {};
int line[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
set<int> Ends;


int check(int O,int X,int turn){
    /*
    cout << acnv(board[0]) << acnv(board[1]) << acnv(board[2]) << endl;
    cout << acnv(board[3]) << acnv(board[4]) << acnv(board[5]) << endl;
    cout << acnv(board[6]) << acnv(board[7]) << acnv(board[8]) << endl;
    cout << "O = " << O << " X = " << X << " Owin = " << Owin << " Xwin = " << Xwin << endl;
    */
    for(int i = 0;i < 8;i++){
        int t = board[line[i][0]] + board[line[i][1]] + board[line[i][2]];
        if(t == 3){
            int stat = 0,p = 1;
            for(int i = 0;i < 9;i++)stat += board[i] * p,p *= 3;
            if(Ends.count(stat) == 0)Owin++,Ends.insert(stat);
            return 1;
        }
        else if (t == -3){
            int stat = 0,p = 1;
            for(int i = 0;i < 9;i++)stat += board[i] * p,p *= 3;
            if(Ends.count(stat) == 0)Xwin++,Ends.insert(stat);
            return -1;
        }
    }
    if(O + X == 9){
        int stat = 0,p = 1;
        for(int i = 0;i < 9;i++)stat += board[i] * p,p *= 3;
        if(Ends.count(stat) == 0)Tie++,Ends.insert(stat);
        return 0;
    }
    for(int i = 0;i < 9;i++){
        if(!board[i]){
            if(turn){
                board[i] = 1;
                check(O + 1,X,turn ^ 1);
                board[i] = 0;
            }
            else{
                board[i] = -1;
                check(O,X + 1,turn ^ 1);
                board[i] = 0;
            }
        }
    }
    return 0;
}

int main(){
    char c;
    for(int i = 0;i < 9;i++)cin >> c,board[i] = cnv(c);
    /*
    cout << endl;
    cout << acnv(board[0]) << acnv(board[1]) << acnv(board[2]) << endl;
    cout << acnv(board[3]) << acnv(board[4]) << acnv(board[5]) << endl;
    cout << acnv(board[6]) << acnv(board[7]) << acnv(board[8]) << endl;
    */
    int o = 0,x = 0;
    for(int i = 0;i < 9;i++)if(board[i] == 1)o++; else if(board[i] == -1)x++;
    //cout << "O = " << o << " X = " << x << endl;
    if(x >= o)check(o,x,1);
    else check(o,x,0);
    cout << Owin + Xwin + Tie << ' ' << Owin << ' ' << Xwin << ' ' << Tie << endl;
    return 0;
}
