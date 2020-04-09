/*
 1261. 알고스팟
 
 다익스트라 알고리즘
 빈칸(0), 벽(1)이 가중치가 된다.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#define MAX 100
#define INF 99999999
using namespace std;
typedef pair<int, int> pii;

int n, m;
string tmp;
int miro[MAX][MAX];
int dist[MAX][MAX];
priority_queue<pair<pii, int>> pq;
int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

int main() {
    cin >> m >> n;
    for(int i = 0; i < n; i++) {
        cin >> tmp;
        for(int j = 0; j < m; j++)
        {
            char ch = tmp[j];
            miro[i][j] = atoi(&ch);
            dist[i][j] = INF;
        }
    }
    pq.push({{0, 0}, 0});
    dist[0][0] = 0;
    
    while (!pq.empty()) {
        int r = pq.top().first.first;
        int c = pq.top().first.second;
        int cost = -pq.top().second;
        pq.pop();
        if(cost > dist[r][c]) continue;
        
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if(nr < 0 || nr > n - 1 || nc < 0 || nc > m - 1) continue;
            
            int ncost = cost + miro[nr][nc];
            if(dist[nr][nc] > ncost) {
                dist[nr][nc] = ncost;
                pq.push({{nr, nc}, -dist[nr][nc]});
            }
        }
    }
    cout << dist[n - 1][m - 1] << endl;
    return 0;
}
