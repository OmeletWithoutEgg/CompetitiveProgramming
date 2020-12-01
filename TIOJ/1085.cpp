#include <bits/stdc++.h>

using namespace std;

int blocked[52][52][52] = {};
struct pos{
    int x, y, z;//previous point
    pos(int x = 0,int y = 0,int z = 0):x(x),y(y),z(z){};
} prevp[52][52][52];
int x, y, z;
int i, j, k;

int main(){
    cin >> x >> y >> z;
    for(k = 1;k <= z;k++)
        for(j = 1;j <= y;j++)
            for(i = 1;i <= x;i++){
                cin >> blocked[i][j][k];
                blocked[0][j][k] = blocked[x + 1][j][k] = 1;
                blocked[i][0][k] = blocked[i][y + 1][k] = 1;
                blocked[i][j][0] = blocked[i][j][z + 1] = 1;
            }
    if(blocked[x][y][z]){
        cout << "no route" << endl;
        return 0;
    }
    //bfs, from (x,y,z) to (1,1,1)
    queue<pos> q;
    pos cur;
    const pos adj[6] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
    q.push(pos(x,y,z));
    //blocked[1][1][1] = 1;
    while(!q.empty()){
        cur = q.front(),q.pop();
        blocked[cur.x][cur.y][cur.z] = 1;
        if(cur.x == 1 && cur.y == 1 && cur.z == 1){
            //found, output & return
            cur = pos(1,1,1);
            cout << "(1,1,1)";
            while(cur.x != x || cur.y != y || cur.z != z){
                cur = prevp[cur.x][cur.y][cur.z];
                cout << "->" << '(' << cur.x << ',' << cur.y << ',' << cur.z << ')';
            }
            cout << endl;
            return 0;
        }
        for(i = 0;i < 6;i++)
            if(!blocked[cur.x + adj[i].x][cur.y + adj[i].y][cur.z + adj[i].z]){
                prevp[cur.x + adj[i].x][cur.y + adj[i].y][cur.z + adj[i].z] = cur;
                q.push(pos(cur.x + adj[i].x,cur.y + adj[i].y,cur.z + adj[i].z));
            }
    }
    //not found
    cout << "no route" << endl;
    return 0;
}

