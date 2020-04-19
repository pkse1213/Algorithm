/*
 1912. 연속합
 
 과연 이 문제를 보고 DP문제라고 생각할 수 있을까? 흠..
 
 DP[i]를 i번째 항을 마지막으로 포함하여 더할 때 최댓값
 DP[i] = max(DP[i-1], 0) + Num[i]는
 
 i−1번째 항을 마지막으로 하는 수열의 합 중 최댓값이 0보다 크면
 그 수열에 A[i]를 붙이면 되고,
 0 이하이면 그냥 A[i-1]을 쓰지말고 A[i]만으로 수열을 만들면 됨
 
 왜 기준이 0이지?? 라고 생각했다. 그 이유는
 0보다 작다면, 지금 i번째 값에 굳이 더해줄 필요가 없기 때문이다.
 우린 최댓값을 구하는 거니깐.
 0으로 선택했다면? 0 + Num[i]가 DP[i]가 된다.
 즉, i번째부터 새롭게 시작한다는 걸 의미
 
 DP[1] to DP[n]중에 최댓값의 주소를 반환하는 함수
 *max_element(DP+1, DP+N+1)
 iterator를 반환하기 때문에 앞에 *를 붙혀줘야 함.
*/

#include <iostream>
#include <algorithm>
#define MAX 100005
using namespace std;

int Num[MAX], DP[MAX];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int N;
    cin >> N;
    
    for(int i = 1; i <= N; i++)
    {
        cin >> Num[i];
    }
    
    DP[1] = Num[1];
    
    for(int i = 2; i <= N; i++)
    {
        DP[i] = max(DP[i-1], 0) + Num[i];
    }
    
    cout << *max_element(DP+1, DP+N+1);
    
    return 0;
}
