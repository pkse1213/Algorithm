//
//  17837_RE.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/03.
//  Copyright © 2020 박세은. All rights reserved.
//
/*
 17837. 새로운 게임 다시풀기2
 */
#include <iostream>
#include <vector>
using namespace std;

struct horseInfo
{
    int r, c, dir;
    horseInfo(){}
    horseInfo(int rr, int cc, int dd)
    {
        r = rr; c = cc; dir = dd;
    }
};
int N, K, rr, cc, dd, turn = 0;
int board[13][13];
vector<int> chess[13][13];
vector<horseInfo> horse;
int dr[5] = {0,0,0,-1,1};
int dc[5] = {0,1,-1,0,0};

int reverseDir(int d)
{
    if(d == 1) return 2;
    if(d == 2) return 1;
    if(d == 3) return 4;
    else return 3;
}

bool moveHorse(int idx, int r, int c, int nr, int nc, int type)
{
    if(type == 1)
    {
        while (!chess[r][c].empty())
        {
            int h = chess[r][c].back();
            chess[nr][nc].push_back(h);
            chess[r][c].pop_back();
            
            horse[h].r = nr;
            horse[h].c = nc;
            
            if(h == idx) break;
        }
    }
    
    else if(type == 0)
    {
        vector<int> v;
        while (!chess[r][c].empty())
        {
            int h = chess[r][c].back();
            v.push_back(h);
            chess[r][c].pop_back();
            
            horse[h].r = nr;
            horse[h].c = nc;
            
            if(h == idx) break;
        }
        
        for(int j = v.size()-1; j >= 0 ; j--)
        {
            chess[nr][nc].push_back(v[j]);
        }
    }
    
    if(chess[nr][nc].size() >= 4) return true;
    else return false;
}

bool game_start()
{
    while (turn <= 1000)
    {
        turn++;
        for(int i = 0; i < K; i++)
        {
            int d = horse[i].dir;
            int nr = horse[i].r + dr[d];
            int nc = horse[i].c + dc[d];
            
            if(nr < 1 || nr > N || nc < 1 || nc > N || board[nr][nc] == 2)
            {
                // 방향 바꾸고
                d = reverseDir(d);
                horse[i].dir = d;
                
                nr += dr[d]*2;
                nc += dc[d]*2;
            }
            
            if(nr < 1 || nr > N || nc < 1 || nc > N || board[nr][nc] == 2) continue;
            
            if(moveHorse(i, horse[i].r, horse[i].c, nr, nc, board[nr][nc]))
                return true;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> K;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++)
            cin >> board[i][j];
    
    for(int i = 0; i < K; i++)
    {
        cin >> rr >> cc >> dd;
        horse.push_back(horseInfo(rr, cc, dd));
        chess[rr][cc].push_back(i);
    }
    
    if(game_start()) cout << turn;
    else  cout << -1;
    
   
    return 0;
}
