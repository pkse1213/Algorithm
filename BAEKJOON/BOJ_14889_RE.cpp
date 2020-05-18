/*
 14889. 스타트와 링크 다시풀기
 */
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int N;
int board[21][21];
bool selected[21];
int answer = 987654321;

void calculate()
{
    int sum[2] = {0,0};
    for(int i = 0; i < N; i++)
    {
        bool flag = selected[i];
        for(int j = 0; j < N; j++)
        {
            if(i == j) continue;
            if(selected[j] == flag)
                sum[flag] += board[i][j];
        }
    }
    int diff = abs(sum[0]-sum[1]);
    if(diff < answer) answer = diff;
}

void dfs(int cnt, int idx)
{
    if(cnt == N / 2)
    {
        calculate();
        return;
    }
    
    if(idx > N) return;
    
    for(int i = idx; i < N; i++)
    {
        if(selected[i]) continue;
        
        selected[i] = true;
        dfs(cnt + 1, i + 1);
        selected[i] = false;
    }
    
}



int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> board[i][j];
        }
    }
    dfs(0,0);
    
    cout << answer;
    
    return 0;
}
