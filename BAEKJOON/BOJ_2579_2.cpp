/*
 2579. 계단 오르기
 
 다른 방법으로 풀어보자.
 DP[i] 테이블을 i번째 계단을 포함하여, 선택하지 않은 계단의 합의 최솟값이라고 하자.
 
 i번째 계단을 선택하지 않았다는 것은 i-1번째 계단은 꼭 선택했다는 것을 의미한다.
 따라서, i-2번째 계단을 선택하지 않았을 때의 최솟값과
 i-2번째 계단을 선택하지 않았을 때의 최솟값 중 더 작은 값 + i번째 계단의 점수
 
 -> DP[i] = min(DP[i-2], DP[i-3]) + S[i]
 
 답은 총 계단 점수 합에서, N번째 계단은 꼭 포함해야 하므로
 N-1을 포함해서 선택하지 않았을 때와 N-2를 선택하지 않았을 때의 값중
 더 작은 값을 빼준다
 -> Sum - min(DP[N-1], DP[N-2])
*/

#include <iostream>
#include <algorithm>
#define MAX 301
using namespace std;

int S[MAX], DP[MAX], Sum = 0;

int main()
{
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        cin >> S[i];
        Sum += S[i];
    }
    
    if(N <= 2)
    {
        cout << Sum;
        return 0;
    }
    
    for(int i = 1; i <= N-1; i++)
    {
        if(i <= 3) DP[i] = S[i];
        else
        {
            DP[i] = min(DP[i-2], DP[i-3]) + S[i];
        }
    }
    cout << Sum - min(DP[N-1], DP[N-2]);
    
    return 0;
}
