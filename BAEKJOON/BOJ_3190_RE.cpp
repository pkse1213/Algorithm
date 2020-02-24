/*
 다시풀기
 3190. 뱀
 
 25분 소요
 */
#include <iostream>
#include <queue>
#include <cstring>
#define MAX 101
using namespace std;

int N, K, L, Dir, Time;
int MAP[MAX][MAX];
int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};
queue<pair<int, int>> Snake;
queue<pair<int, char>> Rotation;


void Initialize()
{
    Time = 0;
    memset(MAP, 0, sizeof(MAP));
    Snake.push({ 1, 1 });
    MAP[1][1] = 1;
    Dir = 0;
}

void Input()
{
    int R, C, T;
    char D;
    
    cin >> N >> K;
    
    for(int i = 0; i < K; i++)
    {
        cin >> R >> C;
        MAP[R][C] = 4;
    }
    
    cin >> L;
    for(int i = 0; i < L; i++)
    {
        cin >> T >> D;
        Rotation.push({ T, D });
    }
}

void Change_Dir(char D)
{
    if(D == 'D')
    {
        Dir++;
        if(Dir == 4) Dir = 0;
    }
    else if(D == 'L')
    {
        Dir--;
        if(Dir == -1) Dir = 3;
    }
}

void Solve()
{
    while (1) {
        Time++;
        
        int r = Snake.back().first;
        int c = Snake.back().second;
        
        int nr = r + dr[Dir];
        int nc = c + dc[Dir];
        
        if(nr < 1 || nr > N || nc < 1 || nc > N || MAP[nr][nc] == 1)
        {
            return;
        }
        
        else
        {
            if(MAP[nr][nc] == 0)
            {
                int tr = Snake.front().first;
                int tc = Snake.front().second;
                MAP[tr][tc] = 0;
                Snake.pop();
            }
            
            Snake.push({ nr, nc });
            MAP[nr][nc] = 1;
        }
        
        if(Time == Rotation.front().first)
        {
            Change_Dir(Rotation.front().second);
            Rotation.pop();
        }
    }
}

int main()
{
    Initialize();
    Input();
    Solve();
    cout << Time << endl;
    
}
