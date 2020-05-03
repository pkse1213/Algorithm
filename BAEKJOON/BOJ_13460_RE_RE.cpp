/*
 13460. 구슬 탈출 2 다시풀기의 다시풀기
 
 */

#include <iostream>
#include <algorithm>
#define MAX 11
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

int n, m;
pii Red, Blue, Goal;
char board[MAX][MAX];
int answer = INF;
int dr[4] = {0,0,1,-1};
int dc[4] = {1,-1,0,0};

int reverse_dir(int d)
{
    if(d == 0) return 1;
    if(d == 1) return 0;
    if(d == 2) return 3;
    if(d == 3) return 2;
    
}

void move_ball(int n, int d, pii R, pii B)
{
    if(n > 10) return;
    
    int move_R = 0;
    int move_B = 0;
    while(1)
    {
        int nr = R.first + dr[d];
        int nc = R.second + dc[d];
        
        if(board[nr][nc] == '.' || board[nr][nc] == 'O')
        {
            R.first = nr;
            R.second = nc;
            move_R++;
            
            if(board[nr][nc] == 'O') break;
        }
        else break;
    }
    
    while(1)
    {
        int nr = B.first + dr[d];
        int nc = B.second + dc[d];
        
        if(board[nr][nc] == '.' || board[nr][nc] == 'O')
        {
            if(board[nr][nc] == 'O') return;
            
            B.first = nr;
            B.second = nc;
            move_B++;
        }
        else break;
    }
    
    if(R.first == Goal.first && R.second == Goal.second)
    {
        answer = min(answer, n); return;
    }
    
    if(B.first == R.first && B.second == R.second)
    {
        if(move_B < move_R)
        {
            R.first -= dr[d];
            R.second -= dc[d];
        }
        else
        {
            B.first -= dr[d];
            B.second -= dc[d];
        }
    }
    
    for(int i = 0; i < 4; i++)
    {
        if(i != d && i != reverse_dir(d))
        {
            move_ball(n + 1, i, R, B);
        }
    }
    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> board[i][j];
            if(board[i][j] == 'R')
            {
                Red = {i,j}; board[i][j] = '.';
            }
            if(board[i][j] == 'B')
            {
                Blue = {i,j}; board[i][j] = '.';
            }
            if(board[i][j] == 'O')
            {
                Goal = {i,j};
            }
        }
    }
    
    for(int i = 0; i < 4; i++)
    {
        move_ball(1, i, Red, Blue);
    }
    
    if(answer == INF) cout << -1;
    else cout << answer;
    
    return 0;
}
