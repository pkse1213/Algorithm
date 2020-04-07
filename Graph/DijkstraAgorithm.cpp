/*
 <다익스트라 알고리즘>
 
 그래프 / 최단 경로 탐색
 하나의 정점에서 다른 모든 정점까지의 최단 경로를 구하는 문제 (1:N)
 https://pparksean.tistory.com/63
 */

#include <iostream>
#include <queue>
#define MAX 500
#define INF 99999999
using namespace std;

int Start, Dist[MAX];
vector<pair<int, int>> Adj[MAX];

void Dijkstra()
{
    priority_queue<pair<int, int>> PQ;
    PQ.push({ Start, 0 }); // { 정점 idx, 해당 정점까지의 최단거리 }
    Dist[Start] = 0;
    
    while (!PQ.empty())
    {
        int Cur = PQ.top().first;
        int Cost = -PQ.top().second;
        PQ.pop();
        
        // 이미 현재 Cost보다 Cur의 더 짧은 경로를 찾았다면 무시
        if(Dist[Cur] < Cost) continue;
        
        // 인접한 정점을 모두 검사
        for(int i = 0; i < Adj[Cur].size(); i++)
        {
            int Next = Adj[Cur][i].first;
            int NCost = Adj[Cur][i].second;
            // 인접한 접점까지 가는 더 짧은 경로를 찾은 경우 값을 갱신하고 우선순위 큐에 넣음
            if(Dist[Next] > NCost + Cost)
            {
                Dist[Next] = NCost + Cost;
                PQ.push({ Next, -Dist[Next] });
            }
        }
    }
}
