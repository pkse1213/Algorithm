/*
 1017. 소수 쌍
 
 이분 매칭

 http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220617618294
 */
#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>
using namespace std;

int N, A, First, Pair;
int OMax = 0, EMax = 0;
vector<int> Arr[2];
vector<int> Adj[25];
int Left[25];
int Right[25];
bool Visited[25];
bool Sosu[2000];

vector<int> Answer;


void Input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> A;
        if(i == 0) First = (A % 2);
        if(A % 2 == 0)
        {
            Arr[0].push_back(A);
            if(EMax < A) EMax = A;
        }
        else
        {
            Arr[1].push_back(A);
            if(OMax < A) OMax = A;
        }
        
    }
}

void Check_Sosu()
{
    int Tmp[4] = {2, 3, 4, 5};
    for(int k : Tmp)
    {
        for(int i = k * k; i <= OMax + EMax; i += k)
        {
            Sosu[i] = true;
        }
    }
}

void Check_Adj()
{
    for(int i = 0; i < Arr[First].size(); i++)
    {
        for(int j = 0; j < Arr[!First].size(); j++)
        {
            if(!Sosu[Arr[First][i] + Arr[!First][j]])
            {
                Adj[i].push_back(j);
            }
        }
    }
}

bool DFS(int j)
{
    if(Visited[j]) return false;
    Visited[j] = true;
    for(int i = 0; i < Adj[j].size(); i++)
    {
        int Pair_Idx = Adj[j][i];
        if(Right[Pair_Idx] == -1 || DFS(Right[Pair_Idx]))
        {
            Right[Pair_Idx] = j;
            Left[j] = Pair_Idx;
            return true;
        }
    }
    return false;
}

void Solve()
{
    for(int k = 0; k < Adj[0].size(); k++)
    {
        int Pair_Idx = Adj[0][k];
        memset(Left, -1, sizeof(Left));
        memset(Right, -1, sizeof(Right));
        
        Left[0] = Pair_Idx;
        Right[Pair_Idx] = 0;
        
        int Cnt = 1;
        for(int j = 1; j < N / 2; j++)
        {
            memset(Visited, 0, sizeof(Visited));
            Visited[0] = true;
            
            if(DFS(j)) Cnt++;
        }
        if(Cnt == N / 2) Answer.push_back(Arr[!First][Pair_Idx]);
    }
    
    if(Answer.size() > 0)
    {
        sort(Answer.begin(), Answer.end());
        for(int i = 0; i < Answer.size(); i++)
        {
            cout << Answer[i] << ' ' ;
        }
    }
    else
    {
        cout << "-1" << endl;
    }
    
    
}

int main()
{
    Input();
    
    if(Arr[0].size() != Arr[1].size())
    {
        cout << "-1" << endl;
        return 0;
    }
    
    Check_Sosu();
    Check_Adj();
    Solve();
    
    return 0;
}

