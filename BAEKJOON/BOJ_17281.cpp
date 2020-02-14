/*
 BAEKJOON
 17281. 야구
 
 DFS + 시뮬레이션
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX 51
using namespace std;

int N, Answer = 0;
int Game[MAX][10];
int Player[10];
bool Selected[10];
int Roo[4];

void Input()
{
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= 9; j++)
        {
            cin >> Game[i][j];
        }
    }
}

void Initialize()
{
    Player[4] = 1;
    memset(Selected, false, sizeof(Selected));
}

int Shoot(int Result)
{
    int Score = 0;
    
    for(int i = 3; i >= 0; i--)
    {
        if(Roo[i] > 0)
        {
            int N_Roo = i + Result;
            if(N_Roo > 3)
            {
                Score++;
            }
            else
            {
                Roo[N_Roo] = Roo[i];
            }
            Roo[i] = 0;
        }
    }
    return Score;
}

void Play()
{
    int Score = 0, Starter = 1;
    
    for(int t = 1; t <= N; t++)
    {
        memset(Roo, 0, sizeof(Roo));
        int Out = 0;
        int Shooter_Num = Starter;
        
        while(1)
        {
            if(Shooter_Num > 9)
            {
                Shooter_Num = 1;
            }
            
            int Shooter_Idx = Player[Shooter_Num];
            int Shooter_Result = Game[t][Shooter_Idx];
            
            Roo[0] = Shooter_Idx;
            
            if(Shooter_Result == 0)
            {
                Out++;
            }
            else
            {
                Score += Shoot(Shooter_Result);
            }
            
            Shooter_Num++;
            
            if(Out == 3)
            {
                Starter = Shooter_Num;
                break;
            }
        }
    }
    Answer = max(Answer, Score);
}

void DFS(int Cnt)
{
    if(Cnt == 4)
    {
        Cnt++;
    }
    
    if(Cnt > 9)
    {
        Play();
        return;
    }
    
    for(int i = 2; i <= 9; i++)
    {
        if(Selected[i] == true) continue;
        Player[Cnt] = i;
        Selected[i] = true;
        
        DFS(Cnt + 1);
        
        Selected[i] = false;
    }
}

void Solve()
{
    DFS(1);
    cout << Answer << endl;
}

int main()
{
    Initialize();
    Input();
    Solve();
    
    return 0;
}
