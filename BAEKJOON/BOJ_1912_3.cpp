/*
 1912. 연속합 (Prefix sum)으로 풀기
 O(N^2)
 */
#include <iostream>
#include <algorithm>
#define MAX 100005
#define INF 987654321
using namespace std;

int Number[MAX];
int DP[MAX];
int main()
{
    int N;
    cin >> N;
    DP[0] = 0;
    for(int i = 1; i <= N; i++)
    {
        cin >> Number[i];
        DP[i] = DP[i-1] + Number[i];
    }
    
    int Max = -INF;
    
    for(int s = 1; s <= N; s++)
    {
        for(int e = s + 1; e <= N; e++)
        {
            Max = max(Max, DP[e] - DP[s-1]);
        }
    }
        
    cout << Max;
    return 0;
}
