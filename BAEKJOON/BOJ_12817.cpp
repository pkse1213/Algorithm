/*
 BOJ 12817. 버스 노선
 */
 #include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAX 1000001
using namespace std;

int N, A, B;
vector<int> Info[MAX];
bool Visited[MAX] = {false,};
int Cnt[MAX] = { 0, };
int Temp[MAX];

void Input()
{
    cin >> N;
    for(int i = 0; i < N - 1; i++)
    {
        cin >> A >> B;
        Info[A].push_back(B);
        Info[B].push_back(A);
    }
}

void DFS(int BStop)
{
    int Sum = 0;
    
    for(int i = 0; i < (int)Info[BStop].size(); i++)
    {
        int NBStop = Info[BStop][i];
        
        if(Visited[NBStop] == false)
        {
            Temp[NBStop]++;
            Visited[NBStop] = true;
            DFS(NBStop);
            
            Visited[NBStop] = false;
            
            Sum += Temp[NBStop];
        }
    }
    
    Temp[BStop] = Sum + 1;
}


void Print()
{
    for(int i = 1; i <= N; i++)
    {
        cout << Cnt[i] << endl;
    }
}

void Solve()
{
    for(int i = 1; i <= N; i++)
    {
        for(int b = 1; b <= N; b++)
        {
            Temp[b] = 0;
        }
        
        Visited[i] = true;
        DFS(i);
        Visited[i] = false;
        Temp[i] = N - 1;
        
        for(int b = 1; b <= N; b++)
        {
            Cnt[b] += Temp[b];
        }
        
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    Input();
    Solve();
    Print();
    
    return 0;
}

