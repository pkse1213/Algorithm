/*
 16234. 인구 이동
 20분
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, L, R;
int board[100][100];
bool visited[100][100];
int dr[4] = {0,0,1,-1};
int dc[4] = {1,-1,0,0};
queue<pair<int, int>> q; // 큐를 전역변수로 빼주니깐 시간이 반으로 줄었다..!

int bfs(int i, int j)
{
    vector<pair<int, int>> v;
    
    q.push(make_pair(i,j));
    v.push_back(make_pair(i, j));
    int sum = board[i][j];
    visited[i][j] = true;
   
    while (!q.empty())
    {
        int r = q.front().first;
        int c = q.front().second;
        int n = board[r][c];
        q.pop();
        
        for(int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nr > N-1 || nc < 0 || nc > N-1 || visited[nr][nc]) continue;
            
            if(L <= abs(board[nr][nc] - n) && abs(board[nr][nc] - n) <= R)
            {
                visited[nr][nc] = true;
                q.push(make_pair(nr, nc));
                v.push_back(make_pair(nr, nc));
                sum += board[nr][nc];
            }
        }
    }
    
    // 연합할 곳이 있다면
    if(v.size() > 1)
    {
        int num = sum/v.size();
        for(int i = 0; i < v.size(); i++)
        {
            board[v[i].first][v[i].second] = num;
        }
        
        return (int)v.size();
    }
    else
    {
        visited[i][j] = false;
        return 0;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> N >> L >> R;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cin >> board[i][j];
    
    int cnt = 0;
    while (1)
    {
        memset(visited, false, sizeof(visited));
        int sum = 0;

        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                if(visited[i][j]) continue;
                sum += bfs(i, j);
            }
        }
        if(sum > 0) cnt++;
        else break;
    }
    
    cout << cnt;
    
    return 0;
}
