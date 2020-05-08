#include <iostream>
#define MAX 11
using namespace std;

int n, m, t, k, answer = 0;
int arr[MAX];

void dfs(int idx, int local_sum, int total_sum)
{
    if(idx == n)
    {
        if(total_sum == m) answer++;
        return;
    }
    
    if(idx >= t)
    {
        local_sum -= arr[idx - t];
    }
    
    
    for(int i = 0; i <= k; i++)
    {
        if(local_sum + i > k || total_sum + i > m) break;
        
        arr[idx] = i;
        dfs(idx + 1, local_sum + i, total_sum + i);
    }
}


int solution(int N, int M, int T, int K)
{
    n = N; m = M; t = T; k = K;
    
    dfs(0, 0, 0);
    return answer;
    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cout << solution(4, 7, 2, 4) << "\n";
    
    return 0;
}
