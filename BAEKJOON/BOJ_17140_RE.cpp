//
//  BOJ_17140_RE.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/02.
//  Copyright © 2020 박세은. All rights reserved.
//
/*
 17140. 이차원 배열과 연산 다시풀기
 40분
 */
#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> pii;

int R, C, K, r_len = 3, c_len = 3;
int board[101][101];

bool cmp(pair<int, int> A, pair<int, int> B)
{
    if(A.second == B.second) return A.first < B.first;
    else return A.second < B.second;
}

void operate_R()
{
    int len = 0;
    for(int r = 1; r <= r_len; r++)
    {
        vector<pii> v;
        v.resize(101, make_pair(0, 0));
        for(int c = 1; c <= c_len; c++)
        {
            if(board[r][c] == 0) continue;
            v[board[r][c]].first = board[r][c];
            v[board[r][c]].second++;
            board[r][c] = 0;
        }
        sort(v.begin(), v.end(), cmp);
        
        int n = 1;
        for(int i = 0; i < v.size(); i++)
        {
            if(v[i].second == 0) continue;
            if(n > 100) break;
            board[r][n++] = v[i].first;
            board[r][n++] = v[i].second;
        }
        if(len < n-1) len = n-1;
    }
    c_len = len;
}

void operate_C()
{
    int len = 0;
    for(int c = 1; c <= c_len; c++)
    {
        vector<pii> v;
        v.resize(101, make_pair(0, 0));
        for(int r = 1; r <= r_len; r++)
        {
            if(board[r][c] == 0) continue;
            v[board[r][c]].first = board[r][c];
            v[board[r][c]].second++;
            board[r][c] = 0;
        }
        sort(v.begin(), v.end(), cmp);
        
        int n = 1;
        for(int i = 0; i < v.size(); i++)
        {
            if(v[i].second == 0) continue;
            if(n > 100) break;
            board[n++][c] = v[i].first;
            board[n++][c] = v[i].second;
        }
        if(len < n-1) len = n-1;
    }
    r_len = len;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> R >> C >> K;
    for(int i = 1; i <= 3; i++)
    {
        for(int j = 1; j <= 3; j++)
        {
            cin >> board[i][j];
        }
    }
    
    int t = 0;
    while (board[R][C] != K)
    {
        if(++t > 100)
        {
            t = -1; break;
        }
        
        if(r_len >= c_len)
            operate_R();
        else
            operate_C();
    }
    
    cout << t;
    
    return 0;
}
