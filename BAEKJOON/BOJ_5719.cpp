/*
 5719. 거의 최단 경로
 
 먼저 다익스트라 알고리즘으로 최단경로 찾음
 최단 경로의 경로 삭제 -> BFS로 역추적
 다시 다익스트라 알고리즘으로 최단경로 찾음
 
 거의 최단 경로란 최단 경로에 포함되지 않는 도로로만 이루어진 경로 중 가장 짧은 것을 말한다.
 U에서 V로 가는 도로와 V에서 U로 가는 도로는 다른 도로이다. -> 방향성 그래프
 
 <벡터값 한번에 초기화>
 vector<int> Dist(Size, 값);
 
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#define MAX 500
#define INF 999999999
using namespace std;
typedef pair<int, int> pii;

int V, E, Start, End, A, B, C;
vector<pii> Adj[MAX];
vector<int> Trace[MAX]; // 추적하기 위해 해당 정점으로 오는 최단 경로의 정점을 저장(최단 경로가 1개 이상일 수 있으므로 1개 이상일 수 있다)

int Dijkstra()
{
    vector<int> Dist(V, INF);
    
    priority_queue<pii> PQ;
    PQ.push({ Start, 0 });
    Dist[Start] = 0;
    
    while (!PQ.empty())
    {
        int Cur = PQ.top().first;
        int Cost = -PQ.top().second;
        PQ.pop();
        
        for(int i = 0; i < Adj[Cur].size(); i++)
        {
            int Next = Adj[Cur][i].first;
            int nCost = Adj[Cur][i].second;
            
            // 삭제된 정점은 건너뜀
            if(nCost == -1) continue;
            
            if(Dist[Next] > nCost + Cost)
            {
                Dist[Next] = nCost + Cost;
                PQ.push({ Next, -Dist[Next] });
                
                // 해당 정점으로 오기 위한 최단 경로인 정점으로 초기화
                Trace[Next].clear();
                Trace[Next].push_back(Cur);
            }
            // 최단 경로인 정점이 2개 이상일 수 있다.
            if(Dist[Next] == nCost + Cost)
            {
                Trace[Next].push_back(Cur);
            }
        }
    }
    
    return Dist[End];
}

// 역추적
void BFS()
{
    queue<int> Q;
    Q.push(End);
    
    while (!Q.empty())
    {
        int Cur = Q.front();
        Q.pop();
        
        for(int i = 0; i < Trace[Cur].size(); i++)
        {
            int Before = Trace[Cur][i];
            
            for(int j = 0; j < Adj[Before].size(); j++)
            {
                if(Adj[Before][j].first == Cur)
                {
                    Adj[Before][j].second = -1;
                    break;
                }
            }
            
            Q.push(Before);
        }
    }
}

int main()
{
    while (1) {
        cin >> V >> E;
        if(V == 0 && E == 0) break;
        
        for(int i = 0; i < V; i++)
        {
            Adj[i].clear();
            Trace[i].clear();
        }
        
        cin >> Start >> End;
        for(int i = 0; i < E; i++)
        {
            cin >> A >> B >> C;
            Adj[A].push_back({ B, C });
        }
        
        // 최단 경로 탐색
        Dijkstra();
        // 최단 경로 정점 삭제
        BFS();
        // 다시 최단 경로 탐색
        int Second = Dijkstra();
        
        if(Second == INF) cout << "-1" << endl;
        else cout << Second << endl;
        
    }
    return 0;
}
