/*
 BAEKJOON
 15683. 감시

 완전탐색
*/

#include <iostream>
#include <vector>
#include <math.h>
#define MAX 9
using namespace std;
struct node {
    int r, c;
    node();
    node(int _r, int _c): r(_r), c(_c) {}
};
int map[MAX][MAX];
bool visited[MAX][MAX];
vector<node> cctv;
vector<int> angle;

int n, m;
int dr[4] = {-1, 0, 1, 0}; // 북 동 남 서
int dc[4] = {0, 1, 0, -1};
int answer = 98765654;

void input()
{
    cin >> n >> m;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin >> map[i][j];
            if(0 < map[i][j] && map[i][j] < 6)
                cctv.push_back(node(i, j));
        }
    }
}

void copy_map()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            visited[i][j] = map[i][j];
        }
    }
}
// 현재 바라보는 방향에서 몇번 회전해야 하나?
int cnt_rotate_angle(int i)
{
    switch (i) {
        case 1:
        case 2:
            return i;
        
        default:
            return i-1;
    }
}
// cctv 종류에 따라 몇가지 종류로 체크해야하나 -> 5번 같은 경우는 항상 상하좌우이니깐 case를 1번만 체크하면 됨
int cnt_check_angle(int i)
{
    switch (i) {
        case 1:
            return 4;
        case 2:
            return 2;
        case 3:
            return 4;
        case 4:
            return 4;
        case 5:
            return 1;
        default:
            return 0;
    }
}
// 사각지대 수
void cnt_square_space()
{
    int res = 0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
            if(!visited[i][j]) res ++;
    }
    answer = min(answer, res);
}

void monitor()
{
    for(int i=0; i<cctv.size(); i++)
    {
        int type = map[cctv[i].r][cctv[i].c];
        int ag = angle[i]; //현재 cctv가 바라보고 있는 방향
        for(int k=0; k<cnt_rotate_angle(type); k++)
        {
            int nr = cctv[i].r; // cctv위치
            int nc = cctv[i].c; // cctv위치
            while(1)
            {
                nr += dr[ag];
                nc += dc[ag];
                if(nr < 0 || nc < 0 || nr > n-1 || nc > m-1 || map[nr][nc] == 6)
                    break;
                visited[nr][nc] = true;
            }
            if(type == 2)
                ag = (ag+2)%4; // 2번 타입은 +2 <- ->(좌우), (상하)이므로
            else
                ag = (ag+1)%4;
        }
    }
}

void dfs(int cnt)
{
    if(cnt == cctv.size())
    {
        copy_map();
        monitor();
        cnt_square_space();
        return;
    }
    
    int type = map[cctv[cnt].r][cctv[cnt].c];
    for(int i=0; i<cnt_check_angle(type); i++)
    {
        // cctv의 바라보는 방향을 vector에 추가한다
        angle.push_back(i);
        dfs(cnt+1);
        angle.pop_back();
    }
}

int main(int argc, char** argv)
{
    input();
   
    dfs(0);
    if(answer == 98765654) cout << 0 ;
    else cout << answer;
    
    return 0;
}
