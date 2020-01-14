/*
 BAEKJOON
 16234. 인구 이동
 bfs
*/

#include <iostream>
#include <vector>
#include <queue>
#define MAX 51
using namespace std;
struct node {
    int r, c;
    node();
    node(int _r, int _c): r(_r), c(_c) {}
};

int map[MAX][MAX];
queue<node> q; // bfs용
int n, L, R;
int dr[4] = {-1, 0, 1, 0}; // 북 동 남 서
int dc[4] = {0, 1, 0, -1};
int answer = 0;

void input()
{
    cin >> n >> L >> R;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            cin >> map[i][j];
        }
    }
}

void print()
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void bfs()
{
    bool check = true;
    while(check)
    {
        check = false;
        bool visited[MAX][MAX] = { false };
        
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(visited[i][j]) continue;
                
                visited[i][j] = true; // 현재 시작 위치 방문 체크
                vector<node> combination; // 연합을 위한 벡터
                int sum = map[i][j]; // 연합의 합을 구할 변수
                
                q.push(node(i,j)); // bfs탐색을 위해 현재 위치 queue에 push
                combination.push_back(node(i,j)); // 연합 벡터에 현재 위치 push
                
                while (!q.empty())
                {
                    int r = q.front().r;
                    int c = q.front().c;
                    q.pop();
                    
                    for(int k=0; k<4; k++)
                    {
                        int nr = r + dr[k];
                        int nc = c + dc[k];
                        
                        if(!(1 <= nr && nr <= n && 1 <= nc && nc <= n)) continue;
                        if(visited[nr][nc]) continue;
                        
                        int diff = abs(map[nr][nc] - map[r][c]);
                        if(L<=diff && diff<=R)
                        {
                            check = true;
                            visited[nr][nc] = true;
                            sum += map[nr][nc];
                            combination.push_back(node(nr,nc));
                            q.push(node(nr,nc));
                        }
                    }
                }
                
                for(int k=0; k<combination.size(); k++)
                {
                    int r = combination[k].r;
                    int c = combination[k].c;
                    int a = sum/combination.size();
                    map[r][c] = a;
                }
            }
        }
        if(check) answer++;
//        print();
    }
}

int main(int argc, char** argv)
{
    input();
    bfs();
    cout << answer;
    return 0;
}
