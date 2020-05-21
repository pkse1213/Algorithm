#include <iostream>
using namespace std;
typedef pair<bool, bool> pbb;

int N, M, R, r1, r2;
pbb board[31][11];

bool check()
{
    for(int c = 1; c <= M; c++)
    {
        int nc = c;
        for(int r = 1; r <= N; r ++)
        {
            if(board[r][nc].first) nc--;
            else if(board[r][nc].second) nc++;
        }
        if(c != nc) return false;
    }
    return true;
}

void dfs(int r, int c, int cnt, int n)
{
    if(cnt == n)
    {
        if(check())
        {
            cout << n;
            exit(0);
        }
        
        return;
    }
    
    if(c >= M)
    {
        c = 1;
        r++;
    }
    
    if(r > N) return;
    
    if(board[r][c].second == false &&
       ((c+1 < M && board[r][c+1].second == false) || (c+1 == M)))
    {
        board[r][c].second = true;
        board[r][c+1].first = true;
        dfs(r, c+2, cnt + 1, n);
        board[r][c].second = false;
        board[r][c+1].first = false;
    }
    dfs(r, c+1, cnt, n);
}


int main()
{
    cin >> M >> R >> N;
                
    for(int i = 0; i < R; i++)
    {
        cin >> r1 >> r2;
        board[r1][r2].second = true;
        board[r1][r2+1].first = true;
    }
    for(int i = 0; i <= 3; i++)
    {
        dfs(1, 1, 0, i);
    }
    
    cout << -1;
    
    return 0;
}
