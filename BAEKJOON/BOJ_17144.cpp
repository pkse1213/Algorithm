/*
 BAEKJOON
 17144. 미세먼지 안녕!
 
 주의 : 미세먼지가 "동시에" 확산된다
 완전탐색으로 확산시켰는데 동시에 이루어지기 때문에 - , +되는 미세먼지 양을 따로 정해두고 한번에 연산
 
*/

#include <iostream>
#include <algorithm>
#define MAX 50
using namespace std;

struct node {
    int r, c;
    node();
    node(int _r, int _c): r(_r), c(_c) {}
};

int origin_map[MAX][MAX];
int operator_map[MAX][MAX] = {0}; // - , +되는 미세먼지 양
int t, n, m;
int dr[4] = {0, 0, -1, 1}; // 좌, 우, 상, 하
int dc[4] = {-1, 1, 0, 0};
int answer = 0;
vector<node> machine;

void input()
{
    cin >> n >> m >> t;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin >> origin_map[i][j];
            if(origin_map[i][j] == -1)
            {
                machine.push_back(node(i, j));
            }
        }
    }
}

void output()
{
    cout << endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cout << origin_map[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

void add()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            origin_map[i][j] += operator_map[i][j];
            operator_map[i][j] = 0;
        }
    }
}

int main(int argc, char** argv)
{
    input();
    while (t--) {
        
        // 미세먼지 확산
        for(int r=0; r<n; r++)
        {
            for(int c=0; c<m; c++)
            {
                for(int i=0; i<4; i++)
                {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if(nr >= 0 && nc >= 0 && nr < n && nc < m && origin_map[nr][nc] > -1)
                    {
                        operator_map[r][c] -= origin_map[r][c]/5;
                        operator_map[nr][nc] += origin_map[r][c]/5;
                    }
                }
            }
        }
        
        add();
        
        // 좌0, 우1, 상2, 하3
        int d[2][4] = { {2, 1, 3, 0}, {3, 1, 2, 0} };
        
        // 공기청정기 바람
        for(int i=0; i<machine.size(); i++)
        {
            int r = machine[i].r;
            int c = machine[i].c;
            int j = 0;
            bool b;
            while (j < 4) {
                int nr = r + dr[d[i][j]];
                int nc = c + dc[d[i][j]];
                
                if (i==0)
                {
                    b = nr >= 0 && nr <= machine[i].r;
                }
                else
                {
                    b = nr >= machine[i].r && nr < n;
                }
                
                if(nc >= 0 && nc < m && b)
                {
                    // 공기청정기 만남
                    if(origin_map[nr][nc] == -1)
                    {
                        origin_map[r][c] = 0;
                        break;
                    }
                    // 이전 좌표가 공기청정기가 아니면 미세먼지 이동시켜줌
                    if(origin_map[r][c] >= 0)
                    {
                        origin_map[r][c] = origin_map[nr][nc];
                    }
                    r = nr;
                    c = nc;
                }
                // 벽과 부딪히면 방향 전환
                else
                {
                    j++;
                }
            }
        }
    }
    
//    output();
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            answer += origin_map[i][j];
        }
    }
    
    cout << answer+2;
    return 0;
}
