#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> pii;

int N, M, origin[9][9], board[9][9], answer = 0;
vector<pii> virus;
vector<pii> safe;
vector<pii> wall;
int dr[4] = {0,0,-1,1};
int dc[4] = {1,-1,0,0};

void copy_map()
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            board[i][j] = origin[i][j];
    
    for(int i = 0; i < 3; i++)
        board[wall[i].first][wall[i].second] = 1;
}

void p()
{
    cout << endl;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
            cout << board[i][j] << ' ';
        cout << endl;
    }
    
}

int safe_zone()
{
    int sum = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            if(board[i][j] == 0) sum++;
    
    return sum;
}

void spread_virus()
{
//    p();
    bool visited[9][9] = {false};
    queue<pii> q;
    for(int i = 0; i < virus.size(); i++)
    {
        q.push(make_pair(virus[i].first, virus[i].second));
        visited[virus[i].first][virus[i].second] = true;
    }
    
    while(!q.empty())
    {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if(!(nr < 0 || nr > N-1 || nc < 0 || nc > M-1)
               && board[nr][nc] == 0 && !visited[nr][nc])
            {
                board[nr][nc] = 2;
                q.push(make_pair(nr, nc));
                visited[nr][nc] = true;
            }
        }
    }
//    p();
}

void select(int n, int cnt)
{
    if(n > safe.size()) return;
    if(cnt == 3)
    {
        copy_map();
        spread_virus();
        int zone = safe_zone();
        if(zone > answer) answer = zone;
        return;
    }
    
    wall.push_back(safe[n]);
    select(n + 1, cnt + 1);
    wall.pop_back();
    select(n + 1, cnt);
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
        {
            cin >> origin[i][j];
            if(origin[i][j] == 0)
                safe.push_back(make_pair(i, j));
            
            if(origin[i][j] == 2)
                virus.push_back(make_pair(i, j));
        }
    
    select(0, 0);
    cout << answer;
    
    return 0;
}
