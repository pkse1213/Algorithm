/*
 17143. 낚시왕
 30분
 
 <예전에 풀었을 때 작성한 풀이>
 처음에 테스트케이스는 맞지만 시간초과가 났다.
 상어의 속력의 범위는 0 ≤ s ≤ 1000이다.
 상어 수가 많아질 수록, 속력 수 만큼 한 칸씩 while문으로 이동한다면 1초 안에 해결할 수 없다.
 
 따라서, 현재 위치(제자리)로 돌아오는 때를 무시하고 그 이후의 거리만 while문으로 이동해야 한다.
 
 이동 방향이 위, 아래일 때는 (R-1)*2만큼 이동할 때마다 제자리로 돌아온다.
 이동 방향이 왼, 오른쪽일 때는 (C-1)*2만큼 이동할 때마다 제자리로 돌아온다.
 
 따라서, 방향에 맞게 속력을 (R-1)*2 or (C-1)*2을 나눈 나머지값 만큼만 이동시켰다.
 그럼 아무리 많이 이동해도 최대 (R-1)*2-1 or (C-1)*2-1 만큼 밖에 이동하지 않기 때문에 시간초과를 해결할 수 있다.
 */
#include <iostream>
#include <vector>
#include <cstring>
#define MAX 101
using namespace std;

struct Fish_Info
{
    int r, c, speed, dir, size;
    bool alive = true;
};
int R, C, M, Catch = 0;
vector<int> MAP[MAX][MAX];
vector<int> C_MAP[MAX][MAX];
vector<Fish_Info> Fishes;
int Dr[5] = {0, -1, 1, 0, 0};
int Dc[5] = {0, 0, 0, 1, -1};

void Input()
{
    cin >> R >> C >> M;
    for(int i = 0; i < M; i++)
    {
        Fish_Info Fish;
        cin >> Fish.r >> Fish.c >> Fish.speed >> Fish.dir >> Fish.size;
        
        Fishes.push_back(Fish);
        MAP[Fish.r][Fish.c].push_back(i);
    }
}

void Copy_Map()
{
    for(int i = 1; i <= R; i++)
    {
        for(int j = 1; j <= C; j++)
        {
            MAP[i][j] = C_MAP[i][j];
        }
    }
}

void Remove_All_Fishes()
{
    for(int i = 1; i <= R; i++)
    {
        for(int j = 1; j <= C; j++)
        {
            C_MAP[i][j].clear();
        }
    }
}

void Catch_Fish(int c)
{
    for(int r = 1; r <= R; r++)
    {
        if(MAP[r][c].empty() == false)
        {
            int Idx = MAP[r][c].front();
            Fishes[Idx].alive = false;
            Catch += Fishes[Idx].size;
            return;
        }
    }
}

int Reverse_Dir(int Dir)
{
    if(Dir == 1) return 2;
    else if(Dir == 2) return 1;
    else if(Dir == 3) return 4;
    else return 3;
}

void Move_Fish(int Idx)
{
    int Dir = Fishes[Idx].dir;
    int Move_Num = 0;
    
    if(Dir == 1 || Dir == 2)
    {
        Move_Num = Fishes[Idx].speed % (R * 2 - 2);
    }
    else if(Dir == 3 || Dir == 4)
    {
        Move_Num = Fishes[Idx].speed % (C * 2 - 2);
    }
    
    int Fr = Fishes[Idx].r;
    int Fc = Fishes[Idx].c;
    
    for(int i = 0; i < Move_Num; i++)
    {
        Dir = Fishes[Idx].dir;
        Fr += Dr[Dir];
        Fc += Dc[Dir];
        
        if(Fr < 1 || Fr > R || Fc < 1 || Fc > C)
        {
            Dir = Reverse_Dir(Dir);
            Fishes[Idx].dir = Dir;
            Fr += (Dr[Dir] * 2);
            Fc += (Dc[Dir] * 2);
        }
    }
    
    Fishes[Idx].r = Fr;
    Fishes[Idx].c = Fc;
    
    if(C_MAP[Fr][Fc].empty() == true)
    {
        C_MAP[Fr][Fc].push_back(Idx);
    }
    else
    {
        if(Fishes[C_MAP[Fr][Fc].front()].size < Fishes[Idx].size)
        {
            Fishes[C_MAP[Fr][Fc].front()].alive = false;
            C_MAP[Fr][Fc].pop_back();
            C_MAP[Fr][Fc].push_back(Idx);
        }
        else
        {
            Fishes[Idx].alive = false;
        }
    }
}

void Solve()
{
    for(int T = 1; T <= C; T++)
    {
        Catch_Fish(T);
        
        if(T == C)
        {
            break;
        }
        Remove_All_Fishes();
        for(int i = 0; i < Fishes.size(); i++)
        {
            if(Fishes[i].alive == true)
            {
                Move_Fish(i);
            }
        }
        Copy_Map();
    }
}

int main()
{
    Input();
    Solve();
    cout << Catch << endl;
    
    return 0;
}
