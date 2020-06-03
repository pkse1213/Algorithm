//
//  BOJ_17779_RE.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/03.
//  Copyright © 2020 박세은. All rights reserved.
//
/*
 17779. 게리맨더링 다시풀기2
 */
#include <iostream>
#include <cstring>
#define INF 987654321
using namespace std;

int N, people[21][21], answer = INF;
int board[21][21], v[5];


void caculate(int x, int y, int d1, int d2)
{
    memset(board, 0, sizeof(board));
    memset(v, 0, sizeof(v));
    for(int i = 0; i <= d1; i++)
    {
        if(board[x+i][y-i] != 5)
        {
            board[x+i][y-i] = 5;
            v[4] += people[x+i][y-i];
        }
        
        if(board[x+d2+i][y+d2-i] != 5)
        {
            board[x+d2+i][y+d2-i] = 5;
            v[4] += people[x+d2+i][y+d2-i];
        }
    }
    
    for(int i = 0; i <= d2; i++)
    {
        if(board[x+i][y+i] != 5)
        {
            board[x+i][y+i] = 5;
            v[4] += people[x+i][y+i];
        }
        if(board[x+d1+i][y-d1+i] != 5)
        {
            board[x+d1+i][y-d1+i] = 5;
            v[4] += people[x+d1+i][y-d1+i];
        }
    }
    
    
    for(int r = 1; r <= N; r++)
    {
        bool flag = false;
        for(int c = 1; c <= N; c++)
        {
            if(x < r && r < x+d1+d2 && board[r][c] == 5)
            {
                flag = !flag; continue;
            }
            if(board[r][c] == 5) continue;
            
            if(flag)
            {
                board[r][c] = 5;
                v[4] += people[r][c];
                continue;
            }
            int idx = 6;
            if(1 <= r && r < x + d1 && 1 <= c && c <= y) idx = 0;
            else if(1 <= r && r <= x + d2 && y < c && c <= N) idx = 1;
            else if(x + d1 <= r && r <= N && 1 <= c && c < y - d1 + d2) idx = 2;
            else if(x + d2 < r && r <= N && y - d1 + d2 <= c && c <= N) idx = 3;
            
            v[idx] += people[r][c];
            board[r][c] = idx+1;
        }
    }
    
    int min_cnt = INF;
    int max_cnt = -1;
    for(int i = 0; i < 5; i++)
    {
        if(min_cnt > v[i]) min_cnt = v[i];
        if(max_cnt < v[i]) max_cnt = v[i];
    }
    
    
    if(answer > max_cnt-min_cnt)
        answer = max_cnt-min_cnt;
    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> N;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++)
            cin >> people[i][j];
    
    
    for(int x = 1; x <= N; x++)
        for(int y = 1; y <= N; y++)
            for(int d1 = 1; d1 <= y-1; d1++)
                for(int d2 = 1; d2 <= N-y; d2++)
                    if(x+d1+d2 <= N)
                        caculate(x, y, d1, d2);
                    
        
    cout << answer;
    
    return 0;
}
