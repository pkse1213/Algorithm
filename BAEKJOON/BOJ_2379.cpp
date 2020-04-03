/*
 2379. 트리 탐색하기
 
(참고)
 https://viruz.tistory.com/entry/2379-%ED%8A%B8%EB%A6%AC-%ED%83%90%EC%83%89%ED%95%98%EA%B8%B0
 
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstring>
#include <stack>
using namespace std;

int T;
string Route_01, Route_02;
vector<int> Result_01;
vector<int> Result_02;

stack<int> ST;

void Initialize()
{
    Result_01.clear();
    Result_02.clear();
}

void Input()
{
    cin >> Route_01 >> Route_02;
}

void Solve()
{
    for(int i = 0; i < Route_01.size(); i++)
    {
        if(Route_01[i] == '0')
        {
            ST.push(i);
        }
        else
        {
            // top에 있는 점으로 돌아오는 것인데, 그 때까지 몇번이 걸렸나
            Result_01.push_back(i - ST.top());
            ST.pop();
        }
    }
    
    for(int i = 0; i < Route_02.size(); i++)
    {
        if(Route_02[i] == '0')
        {
            ST.push(i);
        }
        else
        {
            Result_02.push_back(i - ST.top());
            ST.pop();
        }
    }
}

int Check()
{
    sort(Result_01.begin(), Result_01.end());
    sort(Result_02.begin(), Result_02.end());
    
    return Result_01 == Result_02;
}

int main()
{
    cin >> T;
    for(int i = 0; i < T; i++)
    {
        Initialize();
        Input();
        Solve();
        
        cout << Check() << endl;
    }
    
    return 0;
}

