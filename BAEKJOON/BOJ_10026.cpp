/*
 10026. 적록색약
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#define MAX 101
using namespace std;

int N;
char Board[MAX][MAX];
bool Visited[MAX][MAX];
int Dr[4] = { 0, 0, 1, -1 };
int Dc[4] = { 1, -1, 0, 0};

int NO = 0;
int YES = 0;

void Initialize()
{
    memset(Visited, false, sizeof(Visited));
}

void Input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> Board[i][j];
        }
    }
}


void BFS(int R, int C, char Ch)
{
    queue<pair<int, int>> Q;
    Q.push({R ,C});
    
    while (Q.empty() == false) {
        R = Q.front().first;
        C = Q.front().second;
        Q.pop();
        
        for(int i = 0; i < 4; i++)
        {
            int Nr = R + Dr[i];
            int Nc = C + Dc[i];
             
            if(!(Nr < 0 || Nr > N - 1 || Nc < 0 || Nc > N - 1)
               && Visited[Nr][Nc] == false && Board[Nr][Nc] == Ch)
            {
                Visited[Nr][Nc] = true;
                Q.push({Nr, Nc});
            }
        }
    }
}

void Solve()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(Visited[i][j] == false)
            {
                BFS(i, j, Board[i][j]);
                NO++;
            }
        }
    }
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            Visited[i][j] = false;
            if(Board[i][j] == 'R') Board[i][j] = 'G';
        }
    }
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(Visited[i][j] == false)
            {
                BFS(i, j, Board[i][j]);
                YES++;
            }
        }
    }
}

int main()
{
    Input();
    Solve();
    cout << NO << ' ' << YES << endl;;
    return 0;
}
