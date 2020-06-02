//
//  BOJ_17143_RE_RE_RE.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/02.
//  Copyright © 2020 박세은. All rights reserved.
//
/*
 2020.06.02
 
 17143. 낚시왕 다시풀기3
 40분
 
 */


#include <iostream>
#include <vector>
using namespace std;

struct fish_info
{
    int r, c, speed, dir, size;
    bool alive = true;
    fish_info(){}
    fish_info(int rr, int cc, int sp, int dd, int ss)
    {
        r = rr; c = cc; speed = sp; dir = dd; size = ss;
    }
};

int R, C, M, rr, cc, s, d, z, score = 0;
vector<fish_info> fish_list;
vector<int> origin[101][101];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,1,-1};

void catch_fish(int c)
{
    for(int i = 1; i <= R; i++)
    {
        if(!origin[i][c].empty())
        {
            fish_list[origin[i][c][0]].alive = false;
            origin[i][c].pop_back();
            score += fish_list[origin[i][c][0]].size;
            return;
        }
    }
}

int reverse_dir(int d)
{
    //d가 1인 경우는 위, 2인 경우는 아래, 3인 경우는 오른쪽, 4인 경우는 왼쪽을 의미한다.
    if(d == 0) return 1;
    if(d == 1) return 0;
    if(d == 2) return 3;
    if(d == 3) return 2;
    return -1;
}

void move_fish()
{
    vector<int> board[101][101];
    
    for(int f = 0; f < fish_list.size(); f++)
    {
        if(!fish_list[f].alive) continue;
        int dir = fish_list[f].dir;
        int r = fish_list[f].r;
        int c = fish_list[f].c;
        int speed = 0;
        if(dir == 0 || dir == 1) speed = fish_list[f].speed % (R*2-2);
        else if(dir == 2 || dir == 3) speed = fish_list[f].speed % (C*2-2);
        
        int size = fish_list[f].size;
        
        for(int i = 0; i < speed; i++)
        {
            dir = fish_list[f].dir;
            r += dr[dir];
            c += dc[dir];
            if(r < 1 || r > R || c < 1 || c > C)
            {
                r -= dr[dir];
                c -= dc[dir];

                int new_dir = reverse_dir(dir);
                fish_list[f].dir = new_dir;
                i--; continue;
            }
        }
        
        if(!board[r][c].empty())
        {
            int ss = fish_list[board[r][c][0]].size;
            if(ss > size)
            {
                fish_list[f].alive = false;
            }
            else
            {
                fish_list[board[r][c][0]].alive = false;
                board[r][c].pop_back();
                board[r][c].push_back(f);
                
                fish_list[f].r = r;
                fish_list[f].c = c;
            }
        }
        else
        {
            board[r][c].push_back(f);
            
            fish_list[f].r = r;
            fish_list[f].c = c;
        }
    }
    
    for(int r = 1; r <= R; r++)
    {
        for(int c = 1; c <= C; c++)
        {
            origin[r][c] = board[r][c];
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> R >> C >> M;
    for(int i = 0; i < M ;i++)
    {
        cin >> rr >> cc >> s >> d >> z;
        fish_info tmp = fish_info(rr, cc, s, d-1, z);
        fish_list.push_back(tmp);
        origin[rr][cc].push_back(i);
    }
    
    for(int c = 1; c <= C; c++)
    {
        // 물고기 잡기
        catch_fish(c);
        // 물고기 이동
        if(c != C) move_fish();
    }
    
    cout << score;
    
    return 0;
}
