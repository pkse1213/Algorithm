#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <math.h>
#define MAX 1001
using namespace std;

int N, S, Max = 0;
vector<int> Subway;

void Input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> S;
        Subway.push_back(S);
    }
}

void Solution()
{
    int Start = -1;
    int End = -1;
    
    if(Subway[0] == 0)
    {
        for(int i = 0; i < N; i++)
        {
            if(Subway[i] == 1) break;
            Start++;
        }
        Max = Start + 1;
    }
    
    if(Subway[N - 1] == 0)
    {
        for(int i = N - 1; i >= Start + 1; i--)
        {
            if(Subway[i] == 1) break;
            End++;
        }
        Max = max(Max, End + 1);
    }
    
    int Cnt = 0;
    for(int i = Start + 1; i < N - (End + 1); i++)
    {
        if(Subway[i] == 0)
        {
            Cnt++;
        }
        else
        {
            Max = max(Max, (Cnt / 2) + 1);
            Cnt = 0;
        }
    }
}

void Solve()
{
    Solution();
    cout << Max << endl;
}

int main()
{
    Input();
    Solve();
    
    return 0;
}
