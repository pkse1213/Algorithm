/*
 BAEKJOON
 14499. 주사위 굴리기
 
 */
#include <iostream>
#include <vector>
#define MAX 21
using namespace std;

int N, M, x, y, K, D;
int map[MAX][MAX];
int dice[4][4] = {0};
int bottom = 0;
vector<int> direction;
// 동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4로 주어진다.
int dr[5] = {0, 0, 0, -1, 1};
int dc[5] = {0, 1, -1, 0, 0};

void input()
{
    cin >> N >> M >> x >> y >> K;
    for(int r = 0; r < N; r++)
    {
        for(int c = 0; c < M; c++)
        {
            cin >> map[r][c];
        }
    }
    
    for(int i = 0; i < K; i++)
    {
        cin >> D;
        direction.push_back(D);
    }
}

void move(int dir)
{
    if(dir == 1) // 우
    {
        int temp = dice[2][3];
        for(int c = 3; c >= 1; c--)
        {
            if(c == 1)
            {
                dice[2][c] = bottom;
                bottom = temp;
                break;
            }
            dice[2][c] = dice[2][c-1];
        }
    }
    else if(dir == 2) // 좌
    {
        int temp = dice[2][1];
        for(int c = 1; c <= 3; c++)
        {
            if(c == 3)
            {
                dice[2][c] = bottom;
                bottom = temp;
                break;
            }
            dice[2][c] = dice[2][c+1];
        }
    }
    else if(dir == 3) // 상
    {
        int temp = dice[1][2];
        for(int r = 1; r <= 3; r++)
        {
            if(r == 3)
            {
                dice[r][2] = bottom;
                bottom = temp;
                break;
            }
            dice[r][2] = dice[r+1][2];
        }
    }
    else if(dir == 4) // 하
    {
        int temp = dice[3][2];
        for(int r = 3; r >= 1; r--)
        {
            if(r == 1)
            {
                dice[r][2] = bottom;
                bottom = temp;
                break;
            }
            dice[r][2] = dice[r-1][2];
        }
    }
}

void check()
{
    if(map[x][y] == 0)
    {
        map[x][y] = bottom;
    }
    else
    {
        bottom = map[x][y];
        map[x][y] = 0;
    }
}

void solve()
{
    for(int i = 0; i < K; i++)
    {
        int nx = x + dr[direction[i]];
        int ny = y + dc[direction[i]];
        
        if(nx < 0 || nx > N-1 || ny < 0 || ny > M-1) continue;
        
        x = nx; y = ny;
        
        move(direction[i]);
        check();
        
        cout << dice[2][2] << endl;
    }
}

int main()
{
    input();
    solve();
    return 0;
}
