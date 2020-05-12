/*
 3190. 뱀
 
 */

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
int N, K, A, B, L;
char C;
int board[101][101];
queue<pair<int, char>> dir;
int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};

int change_dir(char ld, int d)
{
    if(ld == 'L')
    {
        if(d == 0) return 3;
        else return d-1;
    }
    else
    {
        return (d+1)%4;
    }
}

void print()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }

    cout << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> N >> K;
    for(int i = 0; i < K; i++)
    {
        cin >> A >> B;
        board[A-1][B-1] = 1;
    }
    cin >> L;
    for(int i = 0; i < L; i++)
    {
        cin >> A >> C;
        dir.push({A, C});
    }
    
    int t = 0;
    int d = 0;
    int r = 0;
    int c = 0;
    
    queue<pii> q;
    q.push({0,0});
    board[0][0] = 2;
    while (1)
    {
        t++;
//        cout << t <<endl;
        
        int nr = r + dr[d];
        int nc = c + dc[d];
        if(nr < 0 || nr > N-1 || nc < 0 || nc > N-1 || board[nr][nc] == 2)
            break;
        
        if(board[nr][nc] == 0)
        {
            board[q.front().first][q.front().second] = 0;
            q.pop();
        }
        r = nr; c = nc;
        q.push({nr, nc});
        board[nr][nc] = 2;
        
        if(dir.front().first == t)
        {
            d = change_dir(dir.front().second, d);
            dir.pop();
        }
//        print();
    }
    cout << t << '\n';

    return 0;
}
