/*
 7579. 앱
 
 DP[i][j]는 i번 째 앱까지 사용했을 때 j의 비용을 들여서 얻는 최대의 메모리 양
 

 현재 i번째 앱 비용이 j보다 작다면 먼저 i-1번째 앱까지 포함해서
 j-Cost[i]비용일 때의 메모리에서 + i번째 메모리를 추가한다
 if(j - Cost[i] >= 0)
 {
     DP[i][j] = DP[i-1][j-Cost[i]] + Memory[i];
 }
 
 현재 i번째 앱 비용이 j보다 클 때는 현재 i번째 앱 포함 X
 i-1번째 앱까지만 포함하여 j비용일 때 얻는 메모리 양
 DP[i][j] = max(DP[i][j], DP[i-1][j]);
 */
#include <iostream>
#include <algorithm>
#define INF 987654321
using namespace std;

int Memory[101], Cost[101], DP[101][10001], N, M, Sum, Answer = INF;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        cin >> Memory[i];
    }
    for(int i = 0; i < N; i++)
    {
        cin >> Cost[i];
        Sum += Cost[i];
    }
    
//    for(int j = Cost[0]; j < Sum; j++)
//    {
        DP[0][Cost[0]] = Memory[0];
//    }
    
    for(int i = 1; i < N; i++)
    {
        for(int j = 0; j < Sum; j++)
        {
            if(j - Cost[i] >= 0)
            {
                DP[i][j] = DP[i-1][j-Cost[i]] + Memory[i];
            }
            DP[i][j] = max(DP[i][j], DP[i-1][j]);
            
            if(DP[i][j] >= M) Answer = min(Answer, j);
        }
    }
    
    cout << Answer;
    
    return 0;
}
