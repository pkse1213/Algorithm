#include <iostream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

long long answer = 0;
int n, k;

void dfs(int cnt, int s, long long num)
{
    if(s > k) return;
    if(cnt == n)
    {
        if(num % 3 == 0 && s == k) answer++;
        return;
    }
    dfs(cnt + 1, s, num);
    dfs(cnt + 1, s + 1, num+ pow(2,cnt));
}

long long solution(int N, int K)
{
    n = N; k = K;
    dfs(0, 0, 0);
    
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    
    cout << solution(50 ,  5);
    
    return 0;
}
