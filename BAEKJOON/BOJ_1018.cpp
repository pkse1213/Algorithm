/*
 1018. 체스판 다시 칠하기
 시뮬레이션
 
 8*8체스판을 체크할 때, 한번에 BWBW, WBWB 규칙을 체크해야 함
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#define MAX 50
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;

int N, M, Answer = INF;
char Board[MAX][MAX];
char Color[2] = {'W', 'B'};

void Input()
{
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        string Str;
        cin >> Str;
        for(int j = 0; j < M; j++)
        {
            Board[i][j] = Str[j];
        }
    }
}

void Check(int Sr, int Sc)
{
    int Cnt1 = 0;
    int Cnt2 = 0;
    int Flag1 = true;
    int Flag2 = false;
    
    for(int i = Sr; i < Sr + 8; i++)
    {
        for(int j = Sc; j < Sc + 8; j++)
        {
            if(Board[i][j] != Color[Flag1]) Cnt1++;
            if(Board[i][j] != Color[Flag2]) Cnt2++;
            
            Flag1 = !Flag1;
            Flag2 = !Flag2;
        }
        Flag1 = !Flag1;
        Flag2 = !Flag2;
    }
    
    Answer = min(Answer, Cnt1);
    Answer = min(Answer, Cnt2);
}

void Solve()
{
    for(int i = 0; i <= N - 8; i++)
    {
        for(int j = 0; j <= M - 8; j++)
        {
            Check(i, j);
        }
    }
}

int main()
{
    Input();
    Solve();
    cout << Answer << endl;
    return 0;
}
