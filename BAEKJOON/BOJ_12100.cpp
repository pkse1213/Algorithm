/*
 BAEKJOON
 12100. 2048 (Easy)
 
 DFS + 시뮬레이션
 
 52분 소요
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 20
using namespace std;

int N, Answer = 0;
int origin[MAX][MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> origin[i][j];
        }
    }
}

void copy_map(int board[MAX][MAX], int map[MAX][MAX])
{
    for(int r = 0; r < N; r++)
    {
        for(int c = 0; c < N; c++)
        {
            board[r][c] = map[r][c];
        }
    }
}

void calculate(int board[MAX][MAX])
{
    int num = 0;
    for(int r = 0; r < N; r++)
    {
        for(int c = 0; c < N; c++)
        {
            num = max(board[r][c], num);
        }
    }
    Answer = max(Answer, num);
}

void DFS(int map[MAX][MAX], int dir, int cnt)
{
    int board[MAX][MAX];
    
    copy_map(board, map);
    
    if(dir == 0) // 상
    {
        for(int c = 0; c < N; c++)
        {
            vector<pair<int, bool>> v;
            for(int r = 0; r < N; r++)
            {
                if(board[r][c] == 0) continue;
                
                if(v.size() == 0)
                {
                    v.push_back(make_pair(board[r][c], false));
                }
                else if(v.back().first == board[r][c] && v.back().second == false)
                {
                    v.back().first *= 2;
                    v.back().second = true;
                }
                else
                {
                    v.push_back(make_pair(board[r][c], false));
                }
                
                board[r][c] = 0;
            }
            
            for(int i = 0; i < v.size(); i++)
            {
                board[i][c] = v[i].first;
            }
        }
    }
    else if(dir == 1) // 하
    {
        for(int c = 0; c < N; c++)
        {
            vector<pair<int, bool>> v;
            for(int r = N-1; r >= 0; r--)
            {
                if(board[r][c] == 0) continue;
                
                if(v.size() == 0)
                {
                    v.push_back(make_pair(board[r][c], false));
                }
                else if(v.back().first == board[r][c] && v.back().second == false)
                {
                    v.back().first *= 2;
                    v.back().second = true;
                }
                else
                {
                    v.push_back(make_pair(board[r][c], false));
                }
                
                board[r][c] = 0;
            }
            
            for(int i = 0; i < v.size(); i++)
            {
                board[(N-1)-i][c] = v[i].first;
            }
        }
    }
    else if(dir == 2) // 좌
    {
        for(int r = 0; r < N; r++)
        {
            vector<pair<int, bool>> v;
            for(int c = 0; c < N; c++)
            {
                if(board[r][c] == 0) continue;
                
                if(v.size() == 0)
                {
                    v.push_back(make_pair(board[r][c], false));
                }
                else if(v.back().first == board[r][c] && v.back().second == false)
                {
                    v.back().first *= 2;
                    v.back().second = true;
                }
                else
                {
                    v.push_back(make_pair(board[r][c], false));
                }
                
                board[r][c] = 0;
            }
            
            for(int i = 0; i < v.size(); i++)
            {
                board[r][i] = v[i].first;
            }
        }
    }
    else if(dir == 3) // 우
    {
        for(int r = 0; r < N; r++)
        {
            vector<pair<int, bool>> v;
            for(int c = N-1; c >= 0; c--)
            {
                if(board[r][c] == 0) continue;
                
                if(v.size() == 0)
                {
                    v.push_back(make_pair(board[r][c], false));
                }
                else if(v.back().first == board[r][c] && v.back().second == false)
                {
                    v.back().first *= 2;
                    v.back().second = true;
                }
                else
                {
                    v.push_back(make_pair(board[r][c], false));
                }
                
                board[r][c] = 0;
            }
            
            for(int i = 0; i < v.size(); i++)
            {
                board[r][(N-1)-i] = v[i].first;
            }
        }
    }
    
    if(cnt == 5)
    {
        calculate(board);
        return;
    }
    
    for(int i = 0; i < 4; i++)
    {
        DFS(board, i, cnt+1);
    }
}

void solve()
{
    for(int i = 0; i < 4; i++)
    {
        DFS(origin, i, 1);
    }
    cout << Answer << endl;
}

int main()
{
    input();
    solve();
    return 0;
}
