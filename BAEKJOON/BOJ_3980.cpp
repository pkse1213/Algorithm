/*
 https://www.acmicpc.net/problem/3980
 BOJ 3980. 선발 명단
 */

#include <iostream>
#include <cstring>
#define MAX 12
using namespace std;

int C, Answer;
int MAP[MAX][MAX];
bool Selected[MAX];


void Initialize()
{
    memset(Selected, false, sizeof(Selected));
    Answer = 0;
}

void Input()
{
    for(int i = 1 ; i <= 11; i++)
    {
        for(int j = 1 ; j <= 11; j++)
        {
            cin >> MAP[i][j];
        }
    }
}

void Choice(int Pos, int Sum)
{
    if(Pos > 11)
    {
        Answer = max(Answer, Sum);
        return;
    }
    
    for(int r = 1 ; r <= 11; r++)
    {
        if(MAP[r][Pos] == 0 || Selected[r] == true) continue;
        
        Selected[r] = true;
        Choice(Pos + 1, Sum + MAP[r][Pos]);
        Selected[r] = false;
    }
}

void Solve()
{
    Choice(1, 0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    for(int i = 1; i <= C; i++)
    {
        Initialize();
        Input();
        Solve();
        cout << Answer << endl;
    }
    return 0;
}
