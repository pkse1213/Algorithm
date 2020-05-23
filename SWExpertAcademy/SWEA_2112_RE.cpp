/*
 2112. [모의 SW 역량테스트] 보호 필름 다시풀기
 
 선택된 막의 값을 다 바꿔줄 필요 없이
 bool selected[20]; // 선택 여부
 int medicine[20]; // A인지 B인지
 로 저장해서
 해당 막이 선택된 막이면 medicine에서 값을 가져다가 체크함
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define INF 987654321
using namespace std;

int T, D, W, K, answer;
int board[13][20];
bool selected[20];
int medicine[20];

bool check()
{
    for(int j = 0; j < W; j++)
    {
        int k = 1;
        int before = board[0][j];
        if(selected[0]) before = medicine[0];
        bool flag = false;
        
        for(int i = 1; i < D; i++)
        {
            int cur = board[i][j];
            if(selected[i]) cur = medicine[i];
            
            if(before == cur) k++;
            else k = 1;
            if(k == K)
            {
                flag = true; break;
            }
            before = cur;
        }
        if(!flag) return false;
    }
    return true;
}

void dfs(int n, int cnt, int m)
{
    if(cnt == m)
    {
        if(check()) answer = cnt;
        return;
    }
    
    if(n >= D) return;
    
    selected[n] = true;
    medicine[n] = 1;
    dfs(n + 1, cnt + 1, m);
    medicine[n] = 0;
    dfs(n + 1, cnt + 1, m);
    
    selected[n] = false;
    dfs(n + 1, cnt, m);
}

int main()
{
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        cin >> D >> W >> K;
        
        for(int i = 0; i < D; i++)
            for(int j = 0; j < W; j++)
                cin >> board[i][j];
        
        answer = INF;
        memset(selected, false, sizeof(selected));
        for(int i = 0; i <= D; i++)
        {
            dfs(0, 0, i);
            if(answer != INF) break;
        }
        printf("#%d %d\n", t, answer);
    }
    return 0;
}
