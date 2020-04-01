#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <math.h>
using namespace std;

int N, M, K;
vector<int> Num;
vector<int> Result;
bool Selected[3];

void Input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> M;
        Num.push_back(M);
    }
    cin >> K;
}

void DFS(int Cnt, int Sum)
{
    if(Cnt == 3)
    {
        Result.push_back(Sum);
        return;
    }
        
    for(int i = 0; i < Num.size(); i++)
    {
        if(Selected[i] == true) continue;
        
        Selected[i] = true;
        DFS(Cnt + 1, Sum + pow(10, Cnt) * Num[i]);
        Selected[i] = false;
    }
}

void Solve()
{
    for(int i = 0; i < Num.size(); i++)
    {
        Selected[i] = true;
        DFS(1, Num[i]);
        Selected[i] = false;
    }
}

void Answer()
{
    sort(Result.begin(), Result.end());
    cout << Result[K-1] << endl;
}

int main()
{
    Input();
    Solve();
    Answer();
    return 0;
}
