#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <math.h>
#define MAX 1001
using namespace std;

int N, M, R, C, Cnt;
int Dr[2] = {1, 0};
int Dc[2] = {0, 1};

void Input()
{
    cin >> M >> N >> C >> R ;
}

void DFS(int r, int c)
{
    if(r > R || c > C) return;
    if(r == R && c == C)
    {
        Cnt++; return;
    }
    
    for(int i = 0; i < 2; i++)
    {
        DFS(r + Dr[i], c + Dc[i]);
    }
}

void Solution()
{
    for(int i = 0; i < 2; i++)
    {
        DFS(Dr[i], Dc[i]);
    }
}

void Solve()
{
    if(R < 0 || R > N || C < 0 || C > M)
    {
        cout << "fail" << endl;
    }
    else
    {
        Solution();
        cout << R + C << endl;
        cout << Cnt << endl;
    }
    
}

int main()
{
    Input();
    Solve();
    
    return 0;
}
