/*
 2579. 계단 오르기
 
 연속해서 세번을 오를 수 없다는 조건 때문에 일반 점화식으론 풀 수 없다.
 
 현재 계단을 포함해서 올랐을 때,
 연속해서 1번 오른 것인지, 2번 오른 것인지 체크하기 위해
 DP[MAX][2] 배열 선언
 
 지금 i번 째 계단이 1번째 올랐다는 것은, i-1 계단을 건너 뛰었다는 것을 의미
 -> i-2까지 올랐을 때의 최댓값 + i번째 계단의 점수
 -> DP[i][0] = max(DP[i-2][0], DP[i-2][1]) + S[i];
 
 지금 i번 째 계단이 2번째 올랐다는 것은,
 -> i-1 계단이 1번 째로 올랐을 때 + i번째 계단의 점수
 -> DP[i][1] = DP[i-1][0] + S[i];
 */

#include <iostream>
#include <algorithm>
#define MAX 301
using namespace std;
int S[MAX];
int DP[MAX][2];

int main()
{
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        cin >> S[i];
    }
    
    DP[1][0] = S[1];
    DP[1][1] = 0;
    
    for(int i = 2; i <= N; i++)
    {
        DP[i][0] = max(DP[i-2][0], DP[i-2][1]) + S[i];
        DP[i][1] = DP[i-1][0] + S[i];
    }
    
    cout << max(DP[N][0], DP[N][1]);
    return 0;
}
