/*
 BAEKJOON
 14503. 로봇청소기
 
 BFS
*/

#include <iostream>
#include <queue>
#include <math.h>
#define MAX 51
using namespace std;

struct robot {
    int r, c, d;
    robot();
    robot(int _r, int _c, int _d): r(_r), c(_c), d(_d) {}
};
int map[MAX][MAX];
int n, m;
int r,c,d;
queue<robot> q;

// d가 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 2인 경우에는 남쪽을, 3인 경우에는 서쪽
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
int answer = 0;

void input()
{
    cin >> n >> m;
    cin >> r >> c >> d;
    q.push(robot(r, c, d));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin >> map[i][j];
        }
    }
}

int rotate_dir(int dir)
{
    switch (dir) {
        case 0:
            return 3;
        default:
            return dir-1;
    }
}

int reverse_dir(int dir)
{
    switch (dir) {
        case 0:
            return 2;
        case 1:
            return 3;
        case 2:
            return 0;
        case 3:
            return 1;
        default:
            return -1;
    }
}

void bfs_clear()
{
    while(!q.empty())
    {
        bool move = false;
        // 먼저 로봇 위치 청소
        robot rb = q.front();
        q.pop();
        map[rb.r][rb.c] = 2;
        
        int nd = rb.d;
        int nr = rb.r;
        int nc = rb.c;
        
        for(int i=0; i<4; i++)
        {
            // 1. 방향 바꿈
            nd = rotate_dir(nd);
            int nr = rb.r + dr[nd];
            int nc = rb.c + dc[nd];
            // 이동하기 전 체크
            if(nr < 0 || nc < 0 || nr > n-1 || nc > m-1) continue;
            
            // 빈곳이면 이동
            if(map[nr][nc] == 0)
            {
                q.push(robot(nr, nc, nd));
                move = true;
                answer++;
                break;
            }
        }
        
        if(!move)
        {
            nr += dr[reverse_dir(nd)];
            nc += dc[reverse_dir(nd)];
            if(nr < 0 || nc < 0 || nr > n-1 || nc > m-1) break;
            if(map[nr][nc] != 1)
            {
                q.push(robot(nr, nc, nd));
            }
        }
    }
}


int main(int argc, char** argv)
{
    input();
    bfs_clear();
    
    cout << answer+1 << endl;
    
    return 0;
}
