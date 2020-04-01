#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <math.h>
#define MAX 1001
using namespace std;

int N, s, e;
vector<pair<int, int>> Time;
vector<int> Toilet;

bool Standard(pair<int, int> A, pair<int, int> B)
{
    return A.first < B.first;
}

void Input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> s >> e;
        pair<int, int> Temp = {s, e};
        Time.push_back(Temp);
    }
    
    sort(Time.begin(), Time.end(), Standard);
}

void Solve()
{
    for(int i = 0; i < N; i++)
    {
        bool Find = false;
        for(int t = 0; t < Toilet.size(); t++)
        {
            if(Toilet[t] <= Time[i].first)
            {
                Toilet[t] = Time[i].second;
                Find = true; break;
            }
        }

        if(Find == false)
        {
            Toilet.push_back(Time[i].second);
        }
    }
    
}

int main()
{
    Input();
    Solve();
    cout << Toilet.size() << endl;
    return 0;
}
