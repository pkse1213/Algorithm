//
//  BOJ_17822_RE_RE.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/03.
//  Copyright © 2020 박세은. All rights reserved.
//
/*
 17822. 원판돌리기 다시풀기3
 bfs
 00:55
 */
#include <iostream>
#include <vector>
#include <queue>
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;

struct rotation_info
{
    int x, d, k;
    rotation_info(){}
    rotation_info(int xx, int dd, int kk)
    {
        x = xx; d = dd; k = kk;
    }
};
int N, M, T,  xx, dd, kk, answer = 0;
double board[51][51];
vector<rotation_info> v;
bool alreadyFinish = false;
queue<pii> q;
int dr[4] = {0,0,-1,1};
int dc[4] = {-1,1,0,0};

void rotate(int x, int d, int k)
{
    for(int r = 0; r < N; r++)
    {
        if((r+1) % x != 0) continue;
        for(int i = 0; i < k; i++)
        {
            if(d == 0)
            {
                int last = board[r][M-1];
                for(int c = M-1; c > 0; c--)
                {
                    board[r][c] = board[r][c-1];
                }
                board[r][0] = last;
            }
            else
            {
                int first = board[r][0];
                for(int c = 0; c < M-1; c++)
                {
                    board[r][c] = board[r][c+1];
                }
                board[r][M-1] = first;
            }
        }
        
    }
}

bool findNum()
{
    bool flag = false;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(board[i][j] == 0) continue;
            
            int num = board[i][j];
            q.push(make_pair(i,j));
            
            while(!q.empty())
            {
                int r = q.front().first;
                int c = q.front().second;
                q.pop();
                
                for(int d = 0; d < 4; d++)
                {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if(nc == M) nc = 0;
                    if(nc == -1) nc = M-1;
                    if(nr < 0 || nr > N-1 || board[nr][nc] == INF || board[nr][nc] != num) continue;
                    
                    board[r][c] = INF;
                    board[nr][nc] = INF;
                    q.push(make_pair(nr,nc));
                    flag = true;
                }
            }
        }
    }
    return flag;
}


void caculateRest()
{
    double sum = 0;
    double cnt = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(board[i][j] != INF)
            {
                cnt++;
                sum += board[i][j];
            }
        }
    }
    
    if(cnt == 0)
    {
        alreadyFinish = true;
        return;
    }
    
    double avg = sum/cnt;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(board[i][j] != INF)
            {
                if(board[i][j] > avg) board[i][j]--;
                else if(board[i][j] < avg) board[i][j]++;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M >> T;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cin >> board[i][j];
        }
    }
    for(int i = 0; i < T; i++)
    {
        cin >> xx >> dd >> kk;
        v.push_back(rotation_info(xx,dd,kk));
    }
    
    for(int i = 0; i < T; i++)
    {
        rotate(v[i].x, v[i].d, v[i].k);
        if(findNum() == false)
            caculateRest();
        
        if(alreadyFinish) break;
    }
    
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(board[i][j] != INF)
            {
                answer += board[i][j];
            }
        }
    }
    cout << answer;
    
    
    
    return 0;
}
