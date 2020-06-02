//
//  BOJ_17142_RE.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/02.
//  Copyright © 2020 박세은. All rights reserved.
//
/*
 17142. 연구소 다시풀기2
 
 40분
 
 시간을 줄인 방법
 원래는 1초당 퍼트릴 때마다 연구소를 돌면서 0이 있는 지 확인했는데
 0개수를 미리 저장해두고, 빈칸이 감염된 수(infect)를 저장해두고
 두 수가 동일해질 때를 체크하도록 해서 시간을 엄청 줄였다
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

int N, M, answer = INF, zero = 0;
int origin[51][51];
int board[51][51];
int visited[51][51];
vector<pii> virus;
vector<int> selected;
int dr[4] = {0,0,1,-1};
int dc[4] = {1,-1,0,0};


void copy_map()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            board[i][j] = origin[i][j];
        }
    }
}

void spread_virus()
{
    memset(visited, false, sizeof(visited));
    queue<pii> q;
    int t = 0;
    int infect = 0;
    for(int i = 0; i < M; i++)
    {
        q.push(make_pair(virus[selected[i]].first, virus[selected[i]].second));
        visited[virus[selected[i]].first][virus[selected[i]].second] = true;
    }
    
    while(!q.empty())
    {
        if(++t > answer) return;
        int size = q.size();
        for(int s = 0; s < size; s++)
        {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            
            for(int i = 0; i < 4; i++)
            {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nr > N-1 || nc < 0 || nc > N-1 ||
                   visited[nr][nc] || board[nr][nc] == 1)  continue;
                
                if(board[nr][nc] == 0) infect++;
                board[nr][nc] = 2;
                visited[nr][nc] = true;
                q.push(make_pair(nr, nc));
            }
            
            if(zero == infect)
            {
                if(answer > t) answer = t;
                return;
            }
        }
    }
}


void select(int n)
{
    if(selected.size() == M)
    {
        copy_map();
        spread_virus();
        return;
    }
    
    if(n >= virus.size()) return;
    
    selected.push_back(n);
    select(n + 1);
    selected.pop_back();
    select(n + 1);
    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> N >> M;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> origin[i][j];
            if(origin[i][j] == 2)
            {
                virus.push_back(make_pair(i,j));
            }
            else if(origin[i][j] == 0) zero++;
        }
    }
    
    if(zero == 0)
    {
        cout << 0;
        return 0;
    }
    
    select(0);
    
    if(answer == INF) cout << -1;
    else cout << answer;
    return 0;
}
