/*
 1966. 프린터 큐
 */
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <deque>
#define MAX 50
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;

int N, M, TC, Max;
int Priority[10];

int main()
{
    cin >> TC;
    for(int t = 0; t < TC; t++)
    {
        Max = 0;
        memset(Priority, 0, sizeof(Priority));
        queue<pii> Q;
        priority_queue<int> PQ;
        cin >> N >> M;
        for(int i = 0; i < N; i++)
        {
            int P;
            cin >> P;
            Q.push({P, i});
            PQ.push(P);
        }
        
        int Answer = 0;
        while (Q.empty() == false)
        {
            int P = Q.front().first;
            int Idx = Q.front().second;
            Q.pop();
            
            
            if(P < PQ.top())
            {
                Q.push({P, Idx});
            }
            else
            {
                if(Idx == M)
                {
                    cout << ++Answer << endl;
                    break;
                }
                else
                {
                    PQ.pop();
                    Answer++;
                }
            }
        }
    }
    
    return 0;
}

