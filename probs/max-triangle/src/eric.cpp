#include<bits/stdc++.h>
using namespace std;
struct Point
{
  long long x,y;
  Point operator +(Point B)
  {
    return {x + B.x, y + B.y};
  }
  Point operator -(Point B)
  {
    return {x - B.x, y - B.y};
  }
  long long operator *(Point B)
  {
    return x*(B.y)-y*(B.x);
  }
};
Point pts[100009];
int main()
{
  long long N,M,i,j,k,ans = 0,nea;
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> N;
  for(i = 0;i < N;i++)
  {
    cin >> pts[i].x >> pts[i].y;
  }
  i = 0;
  j = 1;
  k = 2;
  while(i < N)
  {
    Point f1,f2;
    f1 = pts[k]-pts[i];
    f2 = pts[j]-pts[i];
    nea = abs(f1*f2);
    while(true)
    {
      while(true)
      {
        long long nk = (k+1)%N;
        Point t1,t2;
        t1 = pts[nk]-pts[i];
        t2 = pts[j]-pts[i];
        if(abs(t1*t2) > nea)
        {
          k = nk;
          nea = abs(t1*t2);
        }
        else
        {
          break;
        }
      }
      long long nj = (j + 1)%N;
      Point g1 = pts[k]-pts[i];
      Point g2 = pts[nj]-pts[i];
      if(abs(g1*g2) > nea)
      {
        j = nj;
        nea = abs(g1*g2);
      }
      else
      {
        break;
      }
    }
    ans = max(ans,nea);
    i++;
    if(j == i) j = (j + 1) % N;
    if(k == j) k = (k + 1) % N;
  }
  cout << ans << '\n';
}
