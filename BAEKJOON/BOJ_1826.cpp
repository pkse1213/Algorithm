/*
 1826. 연료 채우기
 
 그리드(탐욕) 알고리즘
 힙
 
 연료가 거리보다 작을 때 계속 반복
 1) 주유소 정보에서 거리순으로 정렬
 2) 현재 연료(=주행가능한 거리) 보다 짧은 거리의 주유소 탐색
 3) 그 주요소 탐색 후 우선순위 큐에 주유가능한 연료 넣기
 4) 가장 앞에 있는 연료 추가, pop, cnt++
 5) 만약 주유 가능한 연료가 없으면(큐 비어있으면) 도착 실패
 
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 101
using namespace std;

int N, a, b, L, P, Cnt = 0;
vector<pair<int, int>> Oil;
priority_queue<int> PQ;

void Sort()
{
    sort(Oil.begin(), Oil.end());
}

void Input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> a >> b;
        Oil.push_back({ a, b });
    }
    cin >> L >> P;
}

void Solution()
{
    int Start = -1;
    while (P < L)
    {
        for(int i = Start + 1; i < Oil.size(); i++)
        {
            if(Oil[i].first > P) break;
            
            PQ.push(Oil[i].second);
            Start = i;
        }
        
        if(PQ.empty() == false)
        {
            P += PQ.top();
            PQ.pop();
            Cnt++;
        }
        else
        {
            break;
        }
    }
}

void Solve()
{
    Solution();
    
    if(P >= L) cout << Cnt << endl;
    else cout << "-1" << endl;
}

int main()
{
    Input();
    Sort();
    Solve();
    
    return 0;
}
