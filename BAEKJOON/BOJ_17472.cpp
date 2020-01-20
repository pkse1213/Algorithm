/*
 BAEKJOON
 17472. 다리 만들기2
 
 */

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#define MAX 12
using namespace std;
struct Node
{
    int r, c;
    Node() {}
    Node(int _r, int _c): r(_r), c(_c) {}
};
struct Bridge
{
    int is1, is2, length;
    Bridge() {}
    Bridge(int _is1, int _is2, int _length)
    {
        length = _length;
        is1 = min(_is1, _is2);
        is2 = max(_is1, _is2);
    }
};
int map[MAX][MAX];
int parent[7];
vector<Bridge> bridges;
int n, m;
int dr[4] = {-1, 0, 1, 0}; // 북 동 남 서
int dc[4] = {0, 1, 0, -1};
int answer = 0;
int count_island = 0;

bool asc(Bridge a, Bridge b)
{
    return a.length < b.length;
}

void print()
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            cout << map[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void input()
{
    cin >> n >> m;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            cin >> map[i][j];
            
            if(map[i][j]) map[i][j] = -1;
        }
    }
}

// 섬 그룹화
void group_map()
{
    bool visited[MAX][MAX] = { false };
    queue<Node> q;
    
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            if(visited[i][j]) continue;
            
            if(map[i][j] == -1)
            {
                q.push(Node(i, j));
                visited[i][j] = true;
                count_island++;
                
                while (!q.empty()) {
                    int r = q.front().r;
                    int c = q.front().c;
                    q.pop();
                    map[r][c] = count_island;
                    
                    for(int k=0; k<4; k++)
                    {
                        int nr = r + dr[k];
                        int nc = c + dc[k];
                        if(nr < 1 || nr > n || nc < 1 || nc > m) continue;
                        
                        if(map[nr][nc] == -1 && !visited[nr][nc])
                        {
                            q.push(Node(nr, nc));
                            visited[nr][nc] = true;
                        }
                    }
                }
            }
        }
    }
//    print();
}

int getParent(int a) {
    if (parent[a] == a) return a;
    return parent[a] = getParent(parent[a]);
}

void unionSet(int a, int b) {
    int rootA = getParent(a);
    int rootB = getParent(b);
    parent[rootA] = rootB;
}

// 크루스칼 알고리즘
void kruskal()
{
    sort(bridges.begin(), bridges.end(), asc);
    
    //부모 배열 초기화(처음 부모는 자기 자신)
    for (int i = 1; i <= count_island; i++) parent[i] = i;
    
    int sum = 0;
    int cnt = 0;
    int index = 0;
    
    int u, v, dist;
    //선택한 간선의 개수가 섬의개수 -1이 될때까지 간선을 선택한다.
    while (cnt < count_island - 1) {
        if (index == bridges.size()) {
            //모든 섬을 연결하는 것이 불가능하다
            cout << -1 << endl;
            return;
        }
        
        dist = bridges[index].length;
        u = bridges[index].is1;
        v = bridges[index].is2;
        
        index++;
        if (getParent(u) == getParent(v)) {
            //이미 연결되어 있다.
            continue;
        }
        else {
            //연결되어 있지 않다면 합친다.
            unionSet(u, v);
            
            //연결된 간선의 수 증가
            cnt++;
            
            //다리 길이에 합쳐준다.
            sum += dist;
        }
    }
    cout << sum;
}

// 다리 생성
void bridge()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            // 가로 방향
            if(map[i][j] > 0 && j+1 <= m-2 && map[i][j+1] == 0)
            {
                int r = i;
                int c = j+1;
                int cnt = 1;
                while(1)
                {
                    c++;
                    if(c > m) break;
                    
                    if(map[r][c] == 0)
                        cnt++;
                    else if(map[r][c] > 0)
                    {
                        if(cnt > 1)
                        {
                            bridges.push_back(Bridge(map[i][j], map[r][c], cnt));
                        }
                        break;
                    }
                }
            }
            
            // 세로 방향
            if(map[i][j] > 0 && i+1 <= n-2 && map[i+1][j] == 0)
            {
                int r = i+1;
                int c = j;
                int cnt = 1;
                while(1)
                {
                    r++;
                    if(r > n) break;
                    
                    if(map[r][c] == 0)
                        cnt++;
                    else if(map[r][c] > 0)
                    {
                        if(cnt > 1)
                        {
                            bridges.push_back(Bridge(map[i][j], map[r][c], cnt));
                        }
                        break;
                    }
                }
            }
        }
    }
    
//    for(int i=0; i<bridges.size(); i++)
//    {
//        cout << bridges[i].is1 << "," << bridges[i].is2 << " " << bridges[i].length << endl;
//    }
}


int main(int argc, char** argv)
{
    input();
    group_map();
    bridge();
    kruskal();
    //    print();
    return 0;
}
