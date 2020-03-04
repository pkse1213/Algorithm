/*
 다시풀기
 17838. 새로운 게임 2
 
 1시간 20분
 
 시뮬레이션
 */
#include <iostream>
#include <vector>
#define MAX 13
using namespace std;

struct Horse_Info
{
    int r, c, dir;
};

int N, K;
int Board[MAX][MAX];
vector<int> Horse_Status[MAX][MAX];
vector<Horse_Info> Horse;

//1부터 순서대로 →, ←, ↑, ↓
int Dr[5] = { 0, 0, 0, -1 ,1 };
int Dc[5] = { 0, 1, -1, 0, 0 };

void Input()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> Board[i][j];
        }
    }
    for(int i = 0; i < K; i++)
    {
        Horse_Info H;
        cin >> H.r >> H.c >> H.dir;
        Horse.push_back(H);
        Horse_Status[H.r][H.c].push_back(i);
    }
}

int Find_Pos(int r, int c, int idx)
{
    for(int i = 0; i < Horse_Status[r][c].size(); i++)
    {
        if(Horse_Status[r][c][i] == idx) return i;
    }
    return -1;
}

int Reverse_Dir(int d)
{
    if(d == 1) return 2;
    else if(d == 2) return 1;
    else if(d == 3) return 4;
    else if(d == 4) return 3;
    else return -1;
}

void Move_Origin_Horse(int r, int c, int idx, int nr, int nc)
{
    for(int i = idx; i < Horse_Status[r][c].size(); i++)
    {
        Horse[Horse_Status[r][c][i]].r = nr;
        Horse[Horse_Status[r][c][i]].c = nc;
        
        Horse_Status[nr][nc].push_back(Horse_Status[r][c][i]);
    }
}

void Move_Reverse_Horse(int r, int c, int idx, int nr, int nc)
{
    for(int i = (int)Horse_Status[r][c].size() - 1; i >= idx; i--)
    {
        Horse[Horse_Status[r][c][i]].r = nr;
        Horse[Horse_Status[r][c][i]].c = nc;
        
        Horse_Status[nr][nc].push_back(Horse_Status[r][c][i]);
    }
}

void Remove_Horse(int r, int c, int idx)
{
    for(int i = (int)Horse_Status[r][c].size() - 1; i >= idx; i--)
    {
        Horse_Status[r][c].pop_back();
    }
}

int Move_Chess(int i, int r, int c, int d, int nr, int nc, int type)
{
    /*
     파란색인 경우에는 A번 말의 이동 방향을 반대로 하고 한 칸 이동한다.
     방향을 반대로 한 후에 이동하려는 칸이 파란색인 경우에는 이동하지 않고 방향만 반대로 바꾼다.
     체스판을 벗어나는 경우에는 파란색과 같은 경우이다.
     */
    if(type == 2)
    {
        int nd = Reverse_Dir(d);
        nr = r + Dr[nd];
        nc = c + Dc[nd];
        
        Horse[i].dir = nd;
        
        if(!(nr < 1 || nr > N || nc < 1 || nc > N || Board[nr][nc] == 2))
        {
            return Move_Chess(i, r, c, nd, nr, nc, Board[nr][nc]);
        }
        else
        {
            return (int)Horse_Status[r][c].size();
        }
    }
    /*
     흰색인 경우에는 그 칸으로 이동한다. 이동하려는 칸에 말이 이미 있는 경우에는 가장 위에 A번 말을 올려놓는다.
     A번 말의 위에 다른 말이 있는 경우에는 A번 말과 위에 있는 모든 말이 이동한다.
     예를 들어, A, B, C로 쌓여있고, 이동하려는 칸에 D, E가 있는 경우에는 A번 말이 이동한 후에는 D, E, A, B, C가 된다.
     */
    else if(type == 0)
    {
        if(Horse_Status[r][c].size() > 1)
        {
            int idx = Find_Pos(r, c, i);
            Move_Origin_Horse(r, c, idx, nr, nc);
            Remove_Horse(r, c, idx);
        }
        else
        {
            Move_Origin_Horse(r, c, 0, nr, nc);
            Remove_Horse(r, c, 0);
        }
    }
    /*
     빨간색인 경우에는 이동한 후에 A번 말과 그 위에 있는 모든 말의 쌓여있는 순서를 반대로 바꾼다.
     A, B, C가 이동하고, 이동하려는 칸에 말이 없는 경우에는 C, B, A가 된다.
     A, D, F, G가 이동하고, 이동하려는 칸에 말이 E, C, B로 있는 경우에는 E, C, B, G, F, D, A가 된다.
     */
    else if(type == 1)
    {
        if(Horse_Status[r][c].size() > 1)
        {
            int idx = Find_Pos(r, c, i);
            Move_Reverse_Horse(r, c, idx, nr, nc);
            Remove_Horse(r, c, idx);
        }
        else
        {
            Move_Reverse_Horse(r, c, 0, nr, nc);
            Remove_Horse(r, c, 0);
        }
    }
    return (int)Horse_Status[nr][nc].size();
}

int Solve()
{
    for(int Turn = 1; Turn <= 1000; Turn++)
    {
        for(int i = 0; i < Horse.size(); i++)
        {
            int r = Horse[i].r;
            int c = Horse[i].c;
            int d = Horse[i].dir;
            
            int nr = r + Dr[d];
            int nc = c + Dc[d];
            
            int Size = 0;
            
            if(nr < 1 || nr > N || nc < 1 || nc > N)
            {
                Size = Move_Chess(i, r, c, d, nr, nc, 2);
            }
            else
            {
                Size = Move_Chess(i, r, c, d, nr, nc, Board[nr][nc]);
            }
            
            if(Size >= 4) return Turn;
        }
    }
    
    return -1;
}

int main()
{
    Input();
    cout << Solve() << endl;
    return 0;
}
