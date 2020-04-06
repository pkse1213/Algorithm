/*
 1405. 미친 로봇
 
 DFS
 
 소수점 자르기
 cout.precision(10);
 cout << fixed << Simple << endl;
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#define Max 29
using namespace std;

int N, P;
bool Map[Max][Max];
double Percent[4];
double Simple = 0;
int Dr[4] = { 0, 0, -1, 1 };
int Dc[4] = { -1, 1, 0, 0 };

void Input()
{
    cin >> N;
    for(int i = 0; i < 4; i ++)
    {
        cin >> P;
        Percent[i] = P / 100.0;
    }
}

void DFS(int R, int C, int Cnt, double Per)
{
    if(Cnt == N)
    {
        Simple += Per;
        return;
    }
    
    for(int i = 0; i < 4; i++)
    {
        int Nr = R + Dr[i];
        int Nc = C + Dc[i];
        
        if(Map[Nr][Nc]) continue;
        
        Map[Nr][Nc] = true;
        DFS(Nr, Nc, Cnt + 1, Per * Percent[i]);
        Map[Nr][Nc] = false;
    }
}

void Solve()
{
    for(int i = 0; i < 4; i++)
    {
        memset(Map, false, sizeof(Map));
        Map[14][14] = true;
        Map[14 + Dr[i]][14 + Dc[i]] = true;
        DFS(14 + Dr[i], 14 + Dc[i], 1, Percent[i]);
    }
    
    //소수점 자르기
    cout.precision(10);
    cout << fixed << Simple << endl;
}

int main()
{
    Input();
    Solve();
    return 0;
}

