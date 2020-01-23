/*
 BAEKJOON
 17142. 연구소3
 
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#include <cstring>
#define MAP_MAX 51
#define VIRUS_MAX 10
using namespace std;

struct Node {
    int r, c;
    Node() {}
    Node(int _r, int _c): r(_r), c(_c) {}
};
int MAP[MAP_MAX][MAP_MAX];
int TIME[MAP_MAX][MAP_MAX];
vector<Node> virus;
queue<Node> active;
bool selected[VIRUS_MAX] = { false };
int blank = 0;
int N, M;
int dr[4] = {-1, 0, 1, 0}; // 북 동 남 서
int dc[4] = {0, 1, 0, -1};
int answer = MAP_MAX*MAP_MAX;

void input()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> MAP[i][j];
            if(MAP[i][j] == 2) virus.push_back(Node(i, j));
            else if(MAP[i][j] == 0) blank++;
        }
    }
}

void print()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cout << MAP[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void spread()
{
    memset(TIME, -1, sizeof(TIME));
    
    for(int i = 0; i < VIRUS_MAX; i++)
        if(selected[i])
        {
            active.push(virus[i]);
            TIME[virus[i].r][virus[i].c] = 0;
        }
    
    int total_time = 0;
    int infect = 0;
    while(!active.empty())
    {
        int r = active.front().r;
        int c = active.front().c;
        active.pop();
        
        for(int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 1 || nr > N || nc < 1 || nc > N) continue;
            
            if(MAP[nr][nc] != 1 && TIME[nr][nc] == -1)
            {
                TIME[nr][nc] = TIME[r][c] + 1;
                if(MAP[nr][nc] == 0)
                {
                    total_time = TIME[nr][nc];
                    infect++;
                }
                active.push(Node(nr, nc));
            }
        }
    }
    if(infect == blank) answer = min(answer, total_time);
}

void dfs(int idx, int cnt)
{
    if(cnt == M)
    {
        spread();
        return;
    }
    
    for(int i = idx; i < virus.size(); i++)
    {
        if(selected[i]) continue;
        selected[i] = true;
        dfs(i + 1, cnt + 1);
        selected[i] = false;
    }
}

int main(int argc, char** argv)
{
    input();
    if(blank == 0)
    {
        cout << 0 << endl;
        return 0;
    }
    dfs(0, 0);
    
    if(answer == MAP_MAX*MAP_MAX) cout << -1 << endl;
    else cout << answer << endl;
    
    return 0;
}
