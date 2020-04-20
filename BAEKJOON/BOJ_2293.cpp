/*
 2293. 동전 1
 
 DP
 */
#include <iostream>
using namespace std;

int N, K, Coins[105], DP[100005] = {0, };

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> K;
    for(int i = 1; i <= N; i++)
    {
        cin >> Coins[i];
    }
    DP[0] = 1;
    for(int i = 1; i <= N; i++)
    {
        for(int j = Coins[i]; j <= K; j++)
        {
            if(j - Coins[i] >= 0)
            {
                // DP[k]는 i번째 코인까지 사용했을 때 k원이 되는 경우의 수
                DP[j] += DP[j - Coins[i]];
            }
        }
    }
    cout << DP[K];
    return 0;
}
