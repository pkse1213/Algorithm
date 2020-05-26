/*
 5656. [모의 SW 역량테스트] 벽돌 깨기
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
#include <deque>
#include <stack>
#include <map>
#include <sstream>
#include <regex>
#include <math.h>
#define MAX 11
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;


int T, N, W, H, answer, zero;
bool blank;
int origin[15][12];
int board[15][12];
vector<int> selected;
int dr[4] = {0,0,-1,1};
int dc[4] = {1,-1,0,0};

void print(int a[15][12])
{
    cout << endl;
    for(int i = 0; i < H ; i++)
    {
        for(int j = 0; j < W; j++)
        {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}



void copy_map()
{
    for(int i = 0; i < H ; i++)
    {
        for(int j = 0; j < W; j++)
        {
            board[i][j] = origin[i][j];
        }
    }
}

void dfs(int r, int c)
{
    int s = board[r][c];
    
    for(int i = 0; i < 4; i++)
    {
        for(int k = 1; k < s; k++)
        {
            int nr = r + dr[i] * k;
            int nc = c + dc[i] * k;
            
            if(nr < 0 || nr >= H || nc < 0 || nc >= W || board[nr][nc] == 0)
            {
                continue;
            }
            if(board[nr][nc] > 1)
            {
                dfs(nr, nc);
            }
            board[nr][nc] = 0;
        }
    }
}

int game()
{
    copy_map();
    
    int brick = 0;
    for(int n = 0; n < N; n++)
    {
        int cc = selected[n];
        bool flag = false;
        for(int rr = 0; rr < H; rr++)
        {
            if(board[rr][cc] != 0)
            {
                dfs(rr, cc);
                board[rr][cc] = 0;
                flag = true; break;
            }
        }
        if(!flag) continue;
        
//        if(rr >= H) continue;
        
//        queue<pair<pii, int>> q;
//        q.push(make_pair(make_pair(rr, cc), board[rr][cc]));
//        board[rr][cc] = 0;
//        cnt++;
//        while(!q.empty())
//        {
//            int r = q.front().first.first;
//            int c = q.front().first.second;
//            int s = q.front().second-1;
//            q.pop();
//
//            for(int d = 0; d < 4; d++)
//            {
//                int nr = r;
//                int nc = c;
//                for(int i = 0; i < s; i++)
//                {
//                    nr += dr[d];
//                    nc += dc[d];
//                    if(nr < 0 || nr > H-1 || nc < 0 || nc > W-1) break;
//                    if(board[nr][nc] == 0) continue;
//                    if(board[nr][nc] > 1) q.push(make_pair(make_pair(nr,nc), board[nr][nc]));
//                    board[nr][nc] = 0; cnt++;
//                }
//            }
//        }
        for(int i = 0; i < H ; i++)
        {
            for(int j = 0; j < W; j++)
            {
                if(board[i][j] > 0) brick++;
            }
        }
        
        if(brick == 0)
        {
            blank = true;
            break;
        }
        
        for(int c = 0; c < W; c++)
        {
            vector<int> v;
            for(int r = H-1; r >= 0; r--)
            {
                if(board[r][c] > 0)
                {
                    v.push_back(board[r][c]);
                    board[r][c] = 0;
                }
               
            }
            for(int i = 0; i < v.size(); i++)
            {
                board[H-1-i][c] = v[i];
            }
        }
    }
    
//    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
    return brick;
}

void select(int cnt)
{
    if(cnt == N)
    {
        int score = game();
        if(score < answer) answer = score;
        return;
    }
    
    for(int i = 0; i < W; i++)
    {
        selected.push_back(i);
        select(cnt + 1);
        if(blank) return;
        selected.pop_back();
    }
    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        answer = 987654321;
        zero = 0;
        blank = false;
        cin >> N >> W >> H;
        for(int i = 0; i < H ; i++)
        {
            for(int j = 0; j < W; j++)
            {
                cin >> origin[i][j];
                if(origin[i][j] == 0) zero++;
            }
        }
        select(0);
        printf("#%d %d\n", t, answer);
    }
    
    
    
    return 0;
}
