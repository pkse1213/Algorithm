/*
 BAEKJOON
 17135. 캐슬 디펜스
 
 DFS (궁수 선택) + BFS (적 선택)

 적을 선택하는 방법을 우선순위를 왼, 위, 오른으로 두고 BFS 탐색으로 찾아냈다.
 2번 방법보다 속도가 6배나 빨라졌다!! 뿌듯 ㅎㅅㅎ
 
 **놓쳤던 부분**

 궁수가 N+1 행에만 위치한다는 말인데, N+1에도 존재할 수 있다고 이해했다.
 문제가 짧지만, 문제를 잘 읽읍시다..^^

 **주의할 부분**

 **같은 적이 여러 궁수에게 공격당할 수 있다.**
 각 궁수가 적을 찾았을 때, 바로 죽이면 안된다. 죽일 수 있는 적을 찾으면 먼저 kill_enemy 배열에 적 위치를 저장해 두었다.
 그리고 모든 궁수가 적을 찾은 후에 아래와 같이 한 명씩 죽이되, 이미 죽였던 적은 카운팅하지 않아야 한다.
 
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#define MAX 16
using namespace std;

int N, M, D, Answer = 0;
vector<pair<int, int>> goongsu;
pair<int, int> kill_enemy[3];
int map[MAX][MAX];
int c_map[MAX][MAX];
bool visited[MAX][MAX];
int dr[4] = {0, -1, 0};
int dc[4] = {-1, 0, 1};
int sr = 0;

void input()
{
    bool find = false;
    cin >> N >> M >> D;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cin >> map[i][j];
            if(map[i][j] == 1 && find == false)
            {
                sr = i; find = true;
            }
        }
    }
}

int distance(int r, int c, int rr, int cc)
{
    return abs(r - rr) + abs(c - cc);
}

void copy_map()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            c_map[i][j] = map[i][j];
        }
    }
}

// 적 선택 (BFS)
int catch_enemy()
{
    int kill = 0;
    
    for(int g = 0; g < goongsu.size(); g++)
    {
        memset(visited, false, sizeof(visited));
        
        int gr = goongsu[g].first;
        int gc = goongsu[g].second;
        bool find = false;
        
        queue<pair<int, int>> q;
        q.push(goongsu[g]);
        
        while(!q.empty())
        {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            
            if(distance(gr, gc, r, c) == D) break;
            
            for(int i = 0; i < 3; i++)
            {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if(nr < 1 || nr > N || nc < 1 || nc > M || visited[nr][nc] == true) continue;
                
                if(c_map[nr][nc] == 1)
                {
                    kill_enemy[g] = make_pair(nr, nc);
                    find = true; break;
                }
                else
                {
                    q.push(make_pair(nr, nc));
                    visited[nr][nc] = true;
                }
            }
            
            if(find) break;
        }
        
        if(find == false)
        {
            kill_enemy[g] = make_pair(-1, -1);
        }
    }
    
    for(int i = 0; i < goongsu.size(); i++)
    {
        if(kill_enemy[i].first == -1 && kill_enemy[i].second == -1) continue;
        
        if(c_map[kill_enemy[i].first][kill_enemy[i].second] == 1)
        {
            c_map[kill_enemy[i].first][kill_enemy[i].second] = 0;
            kill += 1;
        }
    }
    
    return kill;
}

void move_enemy()
{
    for(int i = N; i >= 1; i--)
    {
        for(int j = 1; j <= M; j++)
        {
            c_map[i][j] = c_map[i-1][j];
        }
    }
}

void start_game()
{
    int sum = 0;
    copy_map();
    
    for(int t = 1; t <= N - sr + 1; t++)
    {
        sum += catch_enemy();
        if(t == N - sr + 1)
        {
            Answer = max(Answer, sum);
            return;
        }
        move_enemy();
    }
}

// 궁수 선택 (DFS)
void DFS(int cnt, int c)
{
    if(cnt == 3)
    {
        start_game();
        return;
    }
    
    if(c == M+1)
    {
        return;
    }
    
    goongsu.push_back(make_pair(N+1, c));
    DFS(cnt + 1, c + 1);
    
    goongsu.pop_back();
    DFS(cnt, c + 1);
}

void solve()
{
    DFS(0, 1);
    cout << Answer;
}

int main()
{
    input();
    solve();
    return 0;
}
