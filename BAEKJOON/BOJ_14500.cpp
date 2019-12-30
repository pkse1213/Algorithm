/*
 BAEKJOON
 14500. 테트로미노

 1) 처음 생각 -> 모양별로 다 for문 돌려서 완전탐색해봐야 한다고 생각.
    겁나 오래걸림. 바보 하하 -> 답이 나오긴 한다고 함
    회전이 가능한걸 생각 못함
 
 2) DFS
    - 4가지 모양은 depth=3 으로 dfs탐색 하면 다 나옴 (그림 참고:https://yabmoons.tistory.com/35)
    - ㅜ 모양은 depth=3으로는 나오지 못함 -> 따로 해줘야 함
 
 3) 놓쳤던 부분
    - if(cnt > 4) 일 때 끝내줘야 하는 것, 본인 제외 3번 더 탐색하면 되니깐 자꾸 3이라고 생각했다
    - 기준 좌표 방문 여부를 체크안해줬다
      visit[i][j] = true;
      dfs(i, j, 1, 0);
      visit[i][j] = false;
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <math.h>
#define MAX 500
using namespace std;
int map[MAX][MAX];
bool visit[MAX][MAX] = {false};

int n, m;
int dr[4] = {0, 0, 1, -1};
int dc[4] = {1, -1, 0, 0};
int res = 0;

void dfs(int r, int c, int cnt, int sum) {
    if(cnt > 4)
    {
        res = max(sum, res);
        return;
    }
    
    sum += map[r][c];
    
    for(int i=0; i<4; i++)
    {
        int nr = r+dr[i];
        int nc = c+dc[i];
        
        if(nr < 0 || nc < 0 || nr > n-1 || nc > m-1) continue;
        
        if(visit[nr][nc]) continue;
        else
        {
            visit[nr][nc] = true;
            dfs(nr, nc, cnt+1, sum);
            visit[nr][nc] = false;
        }
    }
}

void except_shape(int r, int c)
{
    // 가운데가 현재 위치
    // ㅗ (좌, 상, 우)
    if(c-1 >= 0 && r-1 >= 0 && c+1 < m)
    {
        res = max(res, map[r][c]+map[r][c-1]+map[r-1][c]+map[r][c+1]);
    }
    
    // ㅜ (좌, 하, 우)
    if(c-1 >= 0 && r+1 < n && c+1 < m)
    {
        res = max(res, map[r][c]+map[r][c-1]+map[r+1][c]+map[r][c+1]);
    }
    
    // ㅏ (상, 하, 우)
    if(r-1 >= 0 && r+1 < n && c+1 < m)
    {
        res = max(res, map[r][c]+map[r-1][c]+map[r+1][c]+map[r][c+1]);
    }
    
    // ㅓ (상, 하, 좌)
    if(r-1 >= 0 && r+1 < n && c-1 >= 0)
    {
        res = max(res, map[r][c]+map[r-1][c]+map[r+1][c]+map[r][c-1]);
    }
    
}


void input()
{
    cin >> n >> m;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin >> map[i][j];
        }
    }
}

int main(int argc, char** argv)
{
    input();
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            // 주의
            // dfs함수에서는 첫 기준이 되는 좌표의 visit을 손대지 않는다. 여기서 관리해줘야 함
            // 이동하는 좌표에 대해서만 visit값 변화
            visit[i][j] = true;
            dfs(i, j, 1, 0);
            visit[i][j] = false;
            except_shape(i, j);
        }
    }
    cout << res;
    return 0;
}
