/*
 2933. 미네랄 실패
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#define MAX 101
using namespace std;

int INF = 987654321;
int R, C, N, H;
string S;
char map[MAX][MAX];
bool visited[MAX][MAX];
vector<pair<int, int>> cluster;
vector<char> height;
pair<int, int> mineral;

int dr[4] = {0, 0, -1, 1};
int dc[4] = {1, -1, 0, 0};

void input()
{
    cin >> R >> C;
    for(int i = 1; i <= R; i++)
    {
        cin >> S;
        for(int j = 1; j <= C; j++)
        {
            map[i][j] = S[j-1];
        }
    }
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> H;
        height.push_back(H);
    }
}

void print()
{
    for(int i = 1; i <= R; i++)
    {
        for(int j = 1; j <= C; j++)
        {
            cout << map[i][j];
        }
        cout << endl;
    }
}



bool find_mineral(int i, int H)
{
    if(i % 2 == 0) // 홀수, 왼->오
    {
        for(int n = 1; n <= C; n++)
        {
            if(map[H][n] == 'x')
            {
                map[H][n] = '.';
                mineral = make_pair(H, n);
                return true;
            }
        }
    }
    else if(i % 2 == 1) // 짝수, 오->왼
    {
        for(int n = C; n >= 1; n--)
        {
            if(map[H][n] == 'x')
            {
                map[H][n] = '.';
                mineral = make_pair(H, n);
                return true;
            }
        }
    }
    return false;
}

bool BFS(int sr, int sc)
{
    cluster.clear();
    
    queue<pair<int, int>> Q;
    Q.push(make_pair(sr, sc));
    cluster.push_back(make_pair(sr, sc));
    visited[sr][sc] = true;
    
    while(Q.empty() == false)
    {
        int r = Q.front().first;
        int c = Q.front().second;
        Q.pop();
        
        for(int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if(nr < 1 || nr > R || nc < 1 || nc > C || visited[nr][nc] == true)
            {
                continue;
            }
            
            if(map[nr][nc] == 'x')
            {
                if(nr == R)
                {
                    return true;
                }
                else
                {
                    Q.push(make_pair(nr, nc));
                    cluster.push_back(make_pair(nr, nc));
                    visited[nr][nc] = true;
                }
            }
        }
    }
    return false;
}

void down_cluster()
{
    for(int i = 0; i < cluster.size(); i++)
    {
        map[cluster[i].first][cluster[i].second] = '.';
    }
    
    while (1) {
        int flag = true;
        
        for(int i = 0; i < cluster.size(); i++)
        {
            int r = cluster[i].first + 1;
            int c = cluster[i].second;
            
            if(map[r][c] == 'x')
            {
                flag = false; break;
            }
        }
        
        if(flag == true)
        {
            for(int i = 0; i < cluster.size(); i++)
            {
                map[cluster[i].first][cluster[i].second] = '.';
            }
            
            for(int i = 0; i < cluster.size(); i++)
            {
                cluster[i].first++;
                map[cluster[i].first][cluster[i].second] = 'x';
            }
        }
        else
        {
            break;
        }
        
    }
}

void fight()
{
    for(int h = 0; h < height.size(); h++)
    {
        H = R - height[h] + 1;
        
        if(find_mineral(h, H) == false) continue;
        
        memset(visited, false, sizeof(visited));
        
        for(int i = 0; i < 4; i++)
        {
            int sr = mineral.first + dr[i];
            int sc = mineral.second + dc[i];
            
            if(sr < 1 || sr > R || sc < 1 || sc > C || visited[sr][sc] == true)
            {
                continue;
            }
            
            if(map[sr][sc] == 'x')
            {
                if(BFS(sr, sc) == false)
                {
                    down_cluster();
                    break;
                }
            }
        }
    }
}

void solve()
{
    fight();
    print();
}

int main()
{
    input();
    solve();
    return 0;
}

