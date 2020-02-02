/*
 BAEKJOON
 17070. 파이프 옮기기 1
 
 현재 위치에서 가능한 방향으로 BFS탐색 후,
 이동한 위치가 (N,N)일 때, answer + 1 해주었다
 */

#include <iostream>
#include <vector>
#include <queue>
#define MAP_MAX 17
using namespace std;

struct Pipe
{
    int r, c, dir; // 가로 1, 대각선 2, 세로 3
    Pipe() {}
    Pipe(int rr, int cc, int d)
    {
        r = rr; c = cc; dir = d;
    }
};
queue<Pipe> q;
vector<int> dir;
int map[MAP_MAX][MAP_MAX];
int N, answer;
int dr[4] = {0, 0, 1, 1}; // 가로, 대각선, 세로
int dc[4] = {0, 1, 1, 0};


void initialize()
{
    answer = 0;
}

void input()
{
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> map[i][j];
        }
    }
}

// dir => 이동하려는 방향, 현재 위치에서 이동 가능한지 체크하기
bool check(int r, int c, int dir)
{
    // 대각선
    if(dir == 2)
    {
        for(int i = 1; i <= 3; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if(!(1 <= nr && nr <= N && 1 <= nc && nc <= N && map[nr][nc] == 0))
            {
                return false;
            }
        }
        return true;
    }
    // 가로, 세로
    else
    {
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        
        if(1 <= nr && nr <= N && 1 <= nc && nc <= N && map[nr][nc] == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void select_dir(int d)
{
    dir.clear();
    if(d == 1)
    {
        dir.push_back(1); dir.push_back(2);
    }
    else if(d == 2)
    {
        dir.push_back(1); dir.push_back(2); dir.push_back(3);
    }
    else if(d == 3)
    {
        dir.push_back(3); dir.push_back(2);
    }
}

void BFS()
{
    while(!q.empty())
    {
        int r = q.front().r;
        int c = q.front().c;
        int d = q.front().dir; select_dir(d);
        q.pop();
        
        for(int i = 0; i < dir.size(); i++)
        {
            int nd = dir[i];
            
            // 현재 끝 점에서 nd 방향으로 이동 가능한지 체크
            if(check(r, c, nd))
            {
                int rr = r + dr[nd];
                int cc = c + dc[nd];
                
                // 이동하는 좌표가 (N,N)이면 push하지 않기
                if(rr == N && cc == N)
                {
                    answer++;
                }
                else
                {
                    q.push(Pipe(rr, cc, nd));
                }
            }
        }
    }
}

void solution()
{
    q.push(Pipe(1, 2, 1));
    BFS();
    cout << answer << endl;
}

void solve()
{
    initialize();
    input();
    solution();
}

int main(int argc, char** argv)
{
    solve();
    
    return 0;
}
