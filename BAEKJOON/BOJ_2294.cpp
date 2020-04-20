/*
 2294. 동전 2 (다음에 다시 풀어보자!)
 
 DP[j] = j값을 만들기 위해 필요한 동전 수 최솟값
 
 처음생각)
 sort(Coins, Coins+N)
 코인을 작은 값부터 정렬하고,
 
 int Cnt = j/Coins[i] + DP[j%Coins[i]];
 DP[j] = min(DP[j], Cnt);
 
 현재 코인을 최대로 사용 + 최대로 사용 후 나머지 값의 동전 사용 최솟값이라고 생각
 만약 13값을 만들기 위해 동전 3,4,6이 있을 때,
 3+4+6 = 13으로 만들 수 있지만,
 위의 식대로라면, 6*2 + 1이라서 불가능하다는 결과를 가져온다.
 
 무작정 가장 큰 수를 최대로 사용하는게 좋다고 생각 한 것이 잘못된 것이다.
 
 답)
 DP[j] = min(DP[j], DP[j-Coins[i]] + 1)
 현재 코인 값을 한번 뺀 값의 DP[j-Coins[i]] + 1(지금 더할 동전 수)로 생각하면 된다.
 
 */
#include <iostream>
#include <algorithm>
using namespace std;

int N, K, Coins[101], DP[10001];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> K;
    for(int i = 0; i < N; i++)
    {
        cin >> Coins[i];
    }
    
    for(int i = 1; i <= K; i++)
    {
        DP[i] = INF;
    }
    
    for(int i = 0; i < N; i++)
    {
        for(int j = Coins[i]; j <= K; j++)
        {
            DP[j] = min(DP[j], DP[j-Coins[i]] + 1);
        }
    }
    
    if(DP[K] == INF) cout << -1;
    else cout << DP[K];
    return 0;
}
