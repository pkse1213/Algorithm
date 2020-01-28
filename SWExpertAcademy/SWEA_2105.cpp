/*
 SW Expert Academy
 2105. [모의 SW 역량테스트] 디저트 카페
 
 복잡해 보이지만, 대각선 방향으로 DFS
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#include <cstring>
#define MAP_MAX 21
using namespace std;

struct Node {
    int r, c;
    Node() {}
    Node(int _r, int _c): r(_r), c(_c) {}
};
int MAP[MAP_MAX][MAP_MAX];
int N, answer;
vector<int> selected;
int dr[4] = {1, 1, -1, -1}; // 북 동 남 서
int dc[4] = {1, -1, -1, 1};

void input()
{
    answer = -1;
    selected.clear();
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> MAP[i][j];
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

void calculate()
{
    vector<int> tmp = selected;
    tmp.pop_back();
    sort(tmp.begin(), tmp.end());
    
    int before = -1;
    for(int i=0; i<tmp.size(); i++)
    {
        if(tmp[i] == before) return;
        before = tmp[i];
    }
        
    answer = max(answer, (int)selected.size()-1);
}

void dfs(Node start, Node current, int dir)
{
    if(dir == 4)
    {
        if(start.r == current.r && start.c == current.c)
        {
            if(selected.size() > 4)
            {
                calculate();
            }
        }
        return;
    }
    
    int nr = current.r + dr[dir];
    int nc = current.c + dc[dir];
    if(!(nr < 1 || nr > N || nc < 1 || nc > N))
    {
        selected.push_back(MAP[nr][nc]);
        dfs(start, Node(nr, nc), dir);
        selected.pop_back();
        dfs(start, current, dir+1);
    }
    else
    {
        dfs(start, current, dir+1);
    }
    
}

void solve()
{
    for(int r = 1; r <= N-2; r++)
    {
        for(int c = 2; c <= N-1; c++)
        {
            selected.clear();
            selected.push_back(MAP[r][c]);
            dfs(Node(r, c), Node(r, c), 0);
        }
    }
}

int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case)
    {
        input();
        solve();
        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}
