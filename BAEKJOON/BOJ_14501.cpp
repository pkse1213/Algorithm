/*
 BAEKJOON
 14501. 퇴사
 
 방법
 1) 브루트포스
 2) DFS
 3) DP
*/

#include <iostream>
#include <algorithm>
#include <math.h>
#define MAX 16
using namespace std;

int day[MAX];
int pay[MAX];

int d[MAX];
int n;
int answer = 0;

// d[i+1]는 i+1일에 i까지 일한 돈 받는 값 저장
void dp(){
    for(int i=1; i<=n; i++)
    {
        if(i + day[i] <= n+1)
        {
            // 일을 했다면 추가해서 d[i+day[i]] 값 갱신
            d[i+day[i]] = max(d[i+day[i]], d[i]+pay[i]);
            answer = max(answer, d[i+day[i]]);
        }
        // 안했다면 어제까지 번 돈으로 갱신
        d[i+1] = max(d[i+1], d[i]);
        answer = max(answer, d[i+1]);
    }
}

void dfs(int d, int sum) {
    if(d > n)
    {
        answer = max(answer, sum);
        return;
    }
    // d날 일 안하는 경우
    dfs(d+1, sum);
    
    // d날 일 한 경우
    if(d + day[d] - 1 <= n)
    {
        dfs(d + day[d], sum + pay[d]);
    }
}

// 처음 생각
void first(int d, int sum)
{
    int nd = d + day[d]; // 이 일을 다 수행한 후의 날짜
    
    // 수행을 다 마친 날이 퇴사일보다 이후이면
    if(nd-1 > n)
    {
        answer = max(answer, sum);
        return;
    }
    // 수행을 다 마친날이 퇴사일이면
    if(nd-1 == n)
    {
        answer = max(answer, sum+pay[d]);
        return;
    }
    
    for(int i = nd; i<=n; i++){
        first(i, sum+pay[d]);
    }
}

void input()
{
    cin >> n ;
    for(int i=1; i<=n; i++)
    {
        cin >> day[i] >> pay[i];
    }
}

int main(int argc, char** argv)
{
    input();
     
    // 1) 처음 생각
    for(int i=1; i<=n; i++)
    {
        first(i, 0);
    }
       
    // 2) DFS
    dfs(1,0);
    
    // DP
    dp();
    
    cout << answer;
    return 0;
}
