/*
 BAEKJOON
 16236. 아기상어
 
 문제 이해를 못해서 계속 삽질했다. ㅠㅠ 난 진짜 바보다 ㅎㅎ
 1)
 BFS로 탐색하면서 물고기가 있는 곳을 탐색하고 그 물고기를 잡으면 된다고 생각했다.
 근데 상하좌우의 우선순위가 없는데 뭐지? 의문이 들긴 했다.
 -> 거리가 같은 물고기들을 BFS로 체크하고 가장 위쪽 + 왼쪽의 물고기를 잡아야 하는 것이었다.
 
 2)
 아기 상어는 자신의 크기와 같은 수의 물고기를 먹을 때 마다 크기가 1 증가한다. 예를 들어, 크기가 2인 아기 상어는 물고기를 2마리 먹으면 크기가 3이 된다.
 이 조건을 같은 크기의 물고기를 잡아야만 +1을 하고, 그 수가 상어 크기와 같아지면 상어 크기 +1을 해주는 것으로 착각하고 삽질을 엄청했다.
 제발 문제 좀 잘 읽자ㅠㅠ
 
 3)
 BFS탐색을 할 때, queue에서 pop한 후 상하좌우를 탐색할 때, 상어와의 거리가 1칸 더 멀어지면 탐색을 종료했다.
 -> 아직 queue에는 같은 거리의 위치들이 남아있다.
    물고기의 위치(r,c)와 상어와의 거리(d)를 저장해 vector에 추가하며 완전탐색을 한 후에, 가장 가깝고 위/왼쪽에 있는 물고기를 찾아내야 했다.
 
 4)
 물고기와 상어의 거리를 좌표값 차이로만 계산하면 된다고 생각했다.
 int distance(int r, int rr, int c, int cc)
 {
     return abs(r-rr) + abs(c-cc);
 }
 -> 상어보다 크기가 큰 물고기를 마주치면 지날 수 없다.
    따라서 돌아가서 물고기를 잡아먹을 수도 있기 때문에 좌표값으로만 계산하면 안된다.
    Fish 객체에 d 변수를 추가하고, pop한 후 상하좌우를 탐색할 때 d+1을 해서 거리를 저장해 주었다.
 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#define MAX 21
using namespace std;
struct Shark {
    int r, c, size = 2;
    Shark() {}
    Shark(int _r, int _c): r(_r), c(_c) {}
};

struct Fish {
    int r, c, d;
    Fish() {}
    Fish(int _r, int _c, int _d): r(_r), c(_c), d(_d){}
};

Shark shark;
queue<Fish> position;
vector<Fish> fish;
int map[MAX][MAX];
int n, tmp_size = 0, answer = 0;

int dr[4] = {-1, 0, 1, 0}; // 북 동 남 서
int dc[4] = {0, 1, 0, -1};

void input()
{
    cin >> n;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            cin >> map[i][j];
            if(map[i][j] == 9)
            {
                map[i][j] = 0;
                shark = Shark(i, j);
            }
        }
    }
}

void print()
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(i==shark.r && j==shark.c) cout << "(" << shark.size << ")\t";
            else cout << map[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void bfs()
{
    while(1)
    {
        bool visited[MAX][MAX] = { false };
        position.push(Fish(shark.r, shark.c, 0));
        visited[shark.r][shark.c] = true;
        int move = 0;
        while(!position.empty())
        {
            int r = position.front().r;
            int c = position.front().c;
            int d = position.front().d;
            position.pop();
            
            for(int i=0; i<4; i++)
            {
                int nr = r + dr[i];
                int nc = c + dc[i];
                int nd = d + 1;
                // 범위 체크
                if(nr < 1 || nr > n || nc < 1 || nc > n) continue;
                
                // 아기상어보다 큰 물고기이거나 이미 방문한 곳은 check X
                if(map[nr][nc] > shark.size || visited[nr][nc]) continue;
                
                // 아기상어보다 작은 물고기 잡아먹을 때
                if(0 < map[nr][nc] && map[nr][nc] < shark.size)
                {
                    fish.push_back(Fish(nr, nc, nd));
                }
                
                // 아기상어랑 같은 크기의 물고기 & 빈칸
                else
                {
                    position.push(Fish(nr, nc, nd));
                }
                visited[nr][nc] = true;
            }
        }
        
        // 잡아먹을 수 있는 물고기가 없으면
        if(fish.empty()) return;
        else
        {
            int r = MAX, c = MAX, d = MAX*MAX;
            for(int i=0; i<fish.size(); i++)
            {
                if(fish[i].d < d)
                {
                    r = fish[i].r;
                    c = fish[i].c;
                    d = fish[i].d;
                }
                else if(fish[i].d == d)
                {
                    if(fish[i].r < r)
                    {
                        r = fish[i].r;
                        c = fish[i].c;
                    }
                    else if(fish[i].r == r && fish[i].c < c)
                    {
                        r = fish[i].r;
                        c = fish[i].c;
                    }
                }
            }
            map[r][c] = 0;
            answer += d;
            shark.r = r;
            shark.c = c;
            fish.clear();
            
            if(++tmp_size == shark.size)
            {
                shark.size++;
                tmp_size = 0;
            }
            //print();
        }
    }
}

int main(int argc, char** argv)
{
    input();
    bfs();
    cout << answer;
    
    return 0;
}


/*
void bfs()
{
    while(1)
    {
        bool visited[MAX][MAX] = {false};
        position.push(node(shark.r, shark.c));
        bool find = false;
        int nr=0, nc=0;
        
        while(!position.empty() && !find)
        {
            int r = position.front().r;
            int c = position.front().c;
            visited[r][c] = true;
            
            for(int i=0; i<4; i++)
            {
                nr = r+dr[i];
                nc = c+dc[i];
                if(nr < 1 && nr > n && nc < 1 && nc > n) continue;
                
                // 아기상어보다 큰 물고기이거나 이미 방문한 곳은 check X
                if(map[nr][nc] > shark_size || visited[nr][nc]) continue;
                
                // 아기상어보다 작은 물고기 잡아먹을 때
                if(map[nr][nc] < shark_size)
                {
                    map[nr][nc] = 0;
                    find = true;
                    break;
                }
                
                // 아기상어랑 같은 크기의 물고기 & 빈칸
                else
                {
                    // 아기상어랑 같은 크기의 물고기는 지나갈 순 있음, 자신의 크기와 같은 수의 물고기를 먹을 때 마다 크기가 1 증가
                    if(map[nr][nc] == shark_size)
                    {
                        if(++tmp_size == shark_size)
                        {
                            shark_size++;
                            tmp_size = 0;
                        }
                    }
                    position.push(node(nr, nc));
                    visited[nr][nc] = true;
                    
                }
                
            }
        }
        
        if(find)
        {
            int distance = abs(shark.r-nr) + abs(shark.c-nc);
            answer += distance;
            shark.r = nr;
            shark.c = nc;
        }
        else
        {
            return;
        }
    }
    
    
}
 */
