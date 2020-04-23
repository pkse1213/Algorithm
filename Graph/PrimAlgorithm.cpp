#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
using namespace std;

using ti3 = tuple<int, int, int>;
int V, E;
vector<pair<int, int>> Adj[100005]; // { Weight, Index }
bool Check[100005];

void Prim()
{
    priority_queue<ti3, vector<ti3>, greater<ti3>> PQ;
    
    for(auto Next : Adj[1])
    {
        PQ.push({ Next.first, 1, Next.second });
    }
    Check[1] = true;
    
    int Cnt = 0;
    while(1)
    {
        int Cost, V1, V2;
        ti3(Cost, V1, V2) = PQ.top(); PQ.pop();
        if(Check[V2]) continue;
        cout << Cost << ' ' << V1 << ' ' << V2 << '\n';
        Check[V2] = true;
        Cnt++;
        
        if(Cnt == V-1) break;
        for(auto Next : Adj[V2])
        {
            if(Check[Next.second]) continue;
            PQ.push({ Next.first, V2, Next.second });
        }
    }
}
