#include <iostream>
#include <vector>
using namespace std;

int R, C, T;
int board[51][51];
int add[51][51] = {0};
vector<int> air;
int dr[4] = {0,0,-1,1};
int dc[4] = {-1,1,0,0};

void spread()
{

    
    for(int r = 0; r < R; r++)
    {
        for(int c = 0; c < C; c++)
        {
            int amount = board[r][c]/5;
            int cnt = 0;
            for(int i = 0; i < 4; i++)
            {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if(nr < 0 || nr > R-1 || nc < 0 || nc > C-1 || board[nr][nc] == -1) continue;
                add[nr][nc] += amount;
                add[r][c] -= amount;
                cnt++;
            }
        }
    }
    
    for(int r = 0; r < R; r++)
    {
        for(int c = 0; c < C; c++)
        {
            board[r][c] += add[r][c];
            add[r][c] = 0;
        }
    }
}

void air_condition(int rr, int r, int r1, int r2, int d[4])
{
    int dir = 0;
    int br = r;
    int bc = 0;
    
    while (dir < 4)
    {
        int nr = br + dr[d[dir]];
        int nc = bc + dc[d[dir]];
        
        if(nr < r1 || nr > r2 || nc < 0 || nc > C-1)
        {
            dir++; continue;
        }
        
        if(nr == rr && nc == 0)
        {
            board[br][bc] = 0;
            break;
        }
        if(br != rr || bc != 0)
        {
            board[br][bc] = board[nr][nc];
        }
        
        br = nr; bc = nc;
        
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> R >> C >> T;
    for(int i = 0; i < R; i++)
    {
        for(int j = 0; j < C; j++)
        {
            cin >> board[i][j];
            if(board[i][j] == -1) air.push_back(i);
        }
    }
    
    for(int i = 0; i < T; i++)
    {
        spread();
        
        int d1[4] = {2,1,3,0};
        int d2[4] = {3,1,2,0};
        air_condition(air[0], air[0]-1, 0, air[0],  d1);
        air_condition(air[1], air[1]+1, air[1], R-1, d2);
    }
    
    int cnt = 0;
    for(int i = 0; i < R; i++)
    {
        for(int j = 0; j < C; j++)
        {
            if(board[i][j] == -1) continue;
            cnt += board[i][j];
        }
    }
    printf("%d", cnt);
    
    
    return 0;
}
