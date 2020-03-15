/*
 1753. 최단경로
 다익스트라 알고리즘
 */
#include <iostream>
#include <vector>
#include <queue>
#define MAX 20001
#define INF 987654321
using namespace std;

int V, E, Start, u, v, w;
vector<pair<int, int>> Vertex[MAX];
int Dist[MAX];

void Input()
{
    cin >> V >> E >> Start;
    for(int i = 0; i < E; i++)
    {
        cin >> u >> v >> w;
        Vertex[u].push_back({v, w});
    }
    
    for(int i = 1; i <= V; i++)
    {
        Dist[i] = INF;
    }
}

void Dijkstra()
{
    priority_queue<pair<int, int>> PQ; // 해당 정점까지의 가중치, 정점의 번호
    PQ.push({0, Start});
    Dist[Start] = 0;
    
    while(PQ.empty() == false)
    {
        int Weight = -PQ.top().first;
        int Num = PQ.top().second;
        PQ.pop();
        
        for(int i = 0; i < Vertex[Num].size(); i++)
        {
            int NWeight = Vertex[Num][i].second;
            int NNum = Vertex[Num][i].first;
            
            if(Dist[NNum] > Weight + NWeight)
            {
                Dist[NNum] = Weight + NWeight;
                PQ.push({-Dist[NNum], NNum});
            }
        }
    }
}

void Solve()
{
    Dijkstra();
    for(int i = 1; i <= V; i++)
    {
        if(Dist[i] == INF) cout << "INF" << endl;
        else cout << Dist[i] << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    Input();
    Solve();
   
    return 0;
}
