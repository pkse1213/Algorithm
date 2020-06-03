//
//  SWEA_5648_RE.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/03.
//  Copyright © 2020 박세은. All rights reserved.
//
/*
 5648. [모의 SW 역량테스트] 원자 소멸 시뮬레이션 다시풀기2
 
 
 int array[4001][4001] 정도 크기의 리스트를 전역변수로 선언하면 안된다...
 memset으로 초기화도 while문에서 시켜줬더니 시간초과난다.
 
 그래서 전역변수로 처음부터 가지고 수를 줄였다 키웠다 해야했다.
 
 1. map의 범위를 4001으로 한 이유
 atom.r = (r + 1000) * 2;
 atom.c = (c + 1000) * 2;
 
 */
#include <iostream>
#include <vector>
using namespace std;

struct atomInfo
{
    int x, y, d, k;
    bool alive = true;
    atomInfo(){}
    atomInfo(int xx, int yy, int dd, int kk)
    {
        x = xx; y = yy; d = dd; k = kk;
    }
};
int T, N, xx, yy, dd, kk, answer;
vector<atomInfo> atom;
int board[4001][4001];
int dy[4] = {1,-1,0,0};
int dx[4] = {0,0,-1,1};

void input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> xx >> yy >> dd >> kk;
        board[(xx + 1000) * 2][(yy + 1000) * 2] = 1;
        atom.push_back(atomInfo((xx + 1000) * 2,(yy + 1000) * 2, dd, kk));
    }
}

bool allDie()
{
    for(int i = 0; i < N; i++)
    {
        if(atom[i].alive) return false;
    }
    return true;
}

void solve()
{
    int t = 0;
    while (1)
    {
        t++;
        if(allDie())
        {
            break;
        }
        for(int a = 0; a < atom.size(); a++)
        {
            if(!atom[a].alive) continue;
            int d = atom[a].d;
            int nr = atom[a].x + dx[d];
            int nc = atom[a].y + dy[d];
            
            if(nr < 0 || nr > 4000 || nc < 0 || nc > 4000)
            {
                atom[a].alive = false;
                board[atom[a].x][atom[a].y]--;
                continue;
            }
            else
            {
                board[atom[a].x][atom[a].y]--;
                board[nr][nc]++;
                atom[a].x = nr;
                atom[a].y = nc;
            }
        }
        
        for(int a = 0; a < atom.size(); a++)
        {
            if(!atom[a].alive) continue;
            
            // 살아있는데 0이다? 이미 2마리 이상이라서 다 죽은상태!
            if(board[atom[a].x][atom[a].y] > 1 || board[atom[a].x][atom[a].y] == 0)
            {
                board[atom[a].x][atom[a].y] = 0;
                answer += atom[a].k;
                atom[a].alive = false;
            }
        }
        
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        answer = 0;
        memset(board, 0, sizeof(board));
        atom.clear();
        input();
        solve();
        printf("#%d %d\n", t, answer);
    }
    
    return 0;
}
