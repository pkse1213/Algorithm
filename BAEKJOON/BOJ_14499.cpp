/*
 BAEKJOON
 14499. 주사위 굴리기
 
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <math.h>
#define MAX 21
using namespace std;

struct node {
    int r, c;
    node();
    node(int _r, int _c): r(_r), c(_c) {}
};
int n,m,x,y,k,d,c;
int cm[1000];
int dice[7] = {0};
int map[MAX][MAX] = {0} ; //
int dx[5] = {0, 0, 0, 1, -1}; // 좌, 우, 상, 하
int dy[5] = {0, -1, 1, 0, 0};

void roll(int d)
{
    int d1, d2, d3, d4, d5, d6;
    d1 = dice[1];
    d2 = dice[2];
    d3 = dice[3];
    d4 = dice[4];
    d5 = dice[5];
    d6 = dice[6];
 
    if (d == 0)
    {
        dice[1] = d4;
        dice[4] = d6;
        dice[6] = d3;
        dice[3] = d1;
    }
    else if (d == 1)
    {
        dice[4] = d1;
        dice[6] = d4;
        dice[3] = d6;
        dice[1] = d3;
    }
    else if (d == 2)
    {
        dice[1] = d5;
        dice[2] = d1;
        dice[6] = d2;
        dice[5] = d6;
    }
    else if (d == 3)
    {
        dice[5] = d1;
        dice[1] = d2;
        dice[2] = d6;
        dice[6] = d5;
    }
}
void solve()
{
    for (int i = 0; i < k; i++)
    {
        int nx = x + dx[cm[i]];
        int ny = y + dy[cm[i]];
        int d = cm[i];
 
        if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
        
        roll(d);
        if (map[nx][ny] == 0) map[nx][ny] = dice[6];
        else
        {
            dice[6] = map[nx][ny];
            map[nx][ny] = 0;
        }
 
        cout << dice[1] << endl;
 
        x = nx;
        y = ny;
    }
}

int main(int argc, char** argv)
{
    cin >> n >> m >> x >> y >> k;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> d;
            map[i][j] = d;
        }
    }
    for(int i=0; i<k; i++){
        cin >> c;
        cm[i] = c;
        
    }
    
    solve();
    
    
    return 0;
}
