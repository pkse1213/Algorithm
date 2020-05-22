/*
 1953. 탈주범 검거 다시풀기
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

int T, N, M, R, C, L, board[50][50], cnt = 0;
bool visited[50][50];
bool dir[4];
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};

bool movable(int dir, int t)
{
    if(dir == 0 && (t == 1 || t == 2 || t == 5 || t == 6)) return true;
    if(dir == 1 && (t == 1 || t == 3 || t == 6 || t == 7)) return true;
    if(dir == 2 && (t == 1 || t == 2 || t == 4 || t == 7)) return true;
    if(dir == 3 && (t == 1 || t == 3 || t == 4 || t == 5)) return true;
    return false;
}

void make_direction(int t)
{
    memset(dir, false, sizeof(dir));
    if(t == 2)
    {
        dir[0] = true; dir[2] = true;
    }
    if(t == 3)
    {
        dir[1] = true; dir[3] = true;
    }
    if(t == 4)
    {
        dir[0] = true; dir[1] = true;
    }
    if(t == 5)
    {
        dir[1] = true; dir[2] = true;
    }
    if(t == 6)
    {
        dir[3] = true; dir[2] = true;
    }
    if(t == 7)
    {
        dir[0] = true; dir[3] = true;
    }
}

void bfs()
{
    queue<pii> q;
    q.push(make_pair(R, C));
    visited[R][C] = true;
    cnt = 1;
    int t = 1;
    
    while(!q.empty())
    {
        if(t == L) return;
        
        int size = q.size();
        for(int i = 0; i < size; i++)
        {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            if(r == 2 && c == 4)
                cout << "dfd";
            int type = board[r][c];
            if(type == 1) memset(dir, true, sizeof(dir));
            else make_direction(type);
            
            for(int i = 0; i < 4; i++)
            {
                if(!dir[i]) continue;
                
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if(nr < 0 || nr > N-1 || nc < 0 || nc > M-1 || visited[nr][nc] || board[nr][nc] == 0) continue;
                
                if(movable(i, board[nr][nc]))
                {
                    visited[nr][nc] = true;
                    q.push(make_pair(nr, nc));
                    cnt++;
                }
            }
        }
        t++;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        cin >> N >> M >> R >> C >> L;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++)
                cin >> board[i][j];
        
        memset(visited, false, sizeof(visited));
        bfs();
            
        cout << endl;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++)
                cout << visited[i][j] << ' ';
            cout << endl;
        }
        printf("#%d %d", t, cnt);
    }
    
    return 0;
}
