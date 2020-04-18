/*
 1463. 1로 만들기
 
 DP의 기본적인 문제이지만 쉽게 생각하기 어려운 문제
 
 DP[i]는 i를 1로 만들기 위해 필요한 연산의 최솟값
 
 ** i = 12일 때,
 1) 3으로 나누었을 땐 (12/3 = 4)이므로,
    4를 1로 만들기 위해 필요한 연산 수 + 1
 
 2) 2으로 나누었을 땐 (12/2 = 6)이므로,
    6를 1로 만들기 위해 필요한 연산 수 + 1
 
 3) 1을 뺄 땐 (12-1 = 11)이므로
    11을 1로 만들기 위해 필요한 연산 수 + 1
 
 따라서 DP[i] = min(DP[4] + 1, DP[6] + 1, DP[11] + 1)
 
 */
#include <iostream>
#include <algorithm>
#define MAX 1000001
using namespace std;
int DP[MAX];

int main()
{
    int N;
    cin >> N;
    
    DP[1] = 0;
    
    for(int i = 2; i <= N; i++)
    {
        DP[i] = DP[i-1] + 1;
        if(i % 2 == 0) DP[i] = min(DP[i], DP[i / 2] + 1);
        if(i % 3 == 0) DP[i] = min(DP[i], DP[i / 3] + 1);
    }
    
    cout << DP[N];
    return 0;
}
