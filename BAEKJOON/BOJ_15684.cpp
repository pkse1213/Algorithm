/*
 BAEKJOON
 15684. 사다리 조작
 
 완전탐색
 
 dfs함수의 for(int r=x; r<=n; r++)에서
 r=1부터 했더니 시간이 7배나 더걸렸음
 주의하기!
*/

#include <iostream>
#include <algorithm>
using namespace std;
// pair의 first는 왼쪽과 연결된 것, second는 오른쪽
pair<int, int> map[31][11] = {make_pair(0, 0)};
int cnt_add = 0;
bool flag = false;
int n, m, h, a, b;
int answer = -1;

void input()
{
    cin >> m >> h >> n;
    for(int i=0; i<h; i++)
    {
        cin >> a >> b;
        map[a][b].second = 1;
        map[a][b+1].first = 1;
    }
}

void check()
{
    bool same = true;
    for(int c=1; c<=m; c++)
    {
        int nc = c;
        for(int r=1; r<=n; r++)
        {
            if(map[r][nc].first == 0 && map[r][nc].second == 0) continue;
            if(map[r][nc].first == 1) nc--;
            else if(map[r][nc].second == 1) nc++;
        }
        if(nc != c)
        {
            same = false;
            break;
        }
    }
    if(same) {
        answer = cnt_add;
        flag = true;
    }
}

void dfs(int cnt, int x)
{
    if(flag) return;
    if(cnt == cnt_add)
    {
        check();
        return;
    }
    
    for(int r=1; r<=n; r++)
    {
        for(int c=1; c<=m-1; c++)
        {
            // 이걸로 해도 됨
            // if(map[r][c].first == 1 || map[r][c].second == 1 || map[r][c].second == 1)
            // continue;
      
            // 이미 가로줄 추가 -> 한칸 이동
            if(map[r][c].second == 1) {
                c += 1;
                continue;
            }
            // 다음 칸에 가로줄 존재 -> 두칸 이동
            // 다음 칸에 가로줄이 존재해도 인접하기 때문에 이 좌표에 추가할 수 없으므로
            if(map[r][c+1].second == 1)
            {
                c += 2;
                continue;
            }

            // 가로줄 추가
            map[r][c].second = 1;
            map[r][c+1].first = 1;
            
            dfs(cnt+1, r);
            
            if(flag) return;
            
            // 삭제
            map[r][c].second = 0;
            map[r][c+1].first = 0;
        }
    }
}

int main(int argc, char** argv)
{
    input();
    
    for(int i=0; i<=3; i++)
    {
        cnt_add = i;
        dfs(0, 1);
        if(flag) break;
    }
        
    
    cout << answer << endl;
    
    return 0;
}
