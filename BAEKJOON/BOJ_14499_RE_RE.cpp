/*
 14499. 주사위 굴리기
 */
#include <iostream>
#include <vector>
using namespace std;

int N, M, r, c, K, D;
int board[20][20];
int dr[5] = {0,0,0,-1,1};
int dc[5] = {0,1,-1,0,0};
vector<int> dir;
int dice[4][4];

void move(int d)
{
    if(d == 1)
    {
        int e = dice[1][3];
        for(int i = 2; i >= 0; i--)
            dice[1][i+1] = dice[1][i];
        dice[1][0] = e;
        dice[3][1] = dice[1][3];
    }
    else if(d == 2)
    {
        int s = dice[1][0];
        for(int i = 1; i <= 3; i++)
            dice[1][i-1] = dice[1][i];
        dice[1][3] = s;
        dice[3][1] = dice[1][3];
    }
    else if(d == 3)
    {
        int s = dice[0][1];
        for(int i = 1; i <= 3; i++)
            dice[i-1][1] = dice[i][1];
        dice[3][1] = s;
        dice[1][3] = dice[3][1];
    }
    else if(d == 4)
    {
        int e = dice[3][1];
        for(int i = 2; i >= 0; i--)
            dice[i+1][1] = dice[i][1];
        dice[0][1] = e;
        dice[1][3] = dice[3][1];
    }
}

void p()
{
    cout << endl;
    for(int i = 0; i < 4; i++)
    {
    for(int j = 0; j < 4; j++)
    {
        cout << dice[i][j];
    }
        cout << endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> N >> M >> r >> c >> K;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            cin >> board[i][j];
    for(int i = 0; i < K; i++)
    {
        cin >> D; dir.push_back(D);
    }
    for(int i = 0; i < K; i++)
    {
        int nr = r + dr[dir[i]];
        int nc = c + dc[dir[i]];
        if(nr < 0 || nr > N-1 || nc < 0 || nc > M-1) continue;
        
        r = nr; c = nc;
        move(dir[i]);

        if(board[r][c] == 0)
            board[r][c] = dice[1][3];
        else
        {
            dice[1][3] = board[r][c];
            dice[3][1] = board[r][c];
            board[r][c] = 0;
        }
//        p();
        cout << dice[1][1] << '\n';
    }
    
    return 0;
}
