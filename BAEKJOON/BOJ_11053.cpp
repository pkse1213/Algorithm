/*
 11053. 가장 긴 증가하는 부분 수열
 
 D[i]는 i번째 항을 마지막으로 사용하는 수열 중 최대 길이
 O(N^2)

 */
#include <iostream>
#include <algorithm>
#define MAX 1005
using namespace std;

int S[MAX], DP[MAX];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        cin >> S[i];
    }
    DP[1] = 1;
    for(int i = 2; i <= N; i++)
    {
        DP[i] = 1;
        for(int j = 1; j < i; j++)
        {
            if(S[j] < S[i]) DP[i] = max(DP[j] + 1, DP[i]);
        }
    }
    cout << *max_element(DP + 1, DP + N + 1);
    return 0;
}
