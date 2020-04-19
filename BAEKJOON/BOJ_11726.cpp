/*
 11726. 2×n 타일링
 
 DP 문제라고 생각도 못할 것 같다.ㅠㅠ
 i번째 타일을 1x2로 두면, i-1개의 타일의 경우의 수와 같고
 i번째 타일을 2x1로 두면, i-2개의 타일의 경우의 수와 같다
 따라서 DP[i] = DP[i-1] + DP[i-2]
 
 계산하는 중간중간 나머지를 취하지 않고 끝나고 나누게 되면
 int overflow로 인해 오답이 발생
 
 원래 DP 타입을 long long으로 두고 계산했는데
 N이 90만 되어도 7540113804746346429이 되어버리는 매직..
 피보나치 수열의 위대함이다..ㅎ
 
 */
#include <iostream>
#define MAX 1001
using namespace std;
typedef long long ll;

ll DP[MAX];

int main()
{
    int N;
    cin >> N;
    
    DP[1] = 1;
    DP[2] = 2;
    for(int i = 3; i <= N; i++)
    {
        DP[i] = (DP[i-1] + DP[i-2]) % 10007 ;
    }
    cout << DP[N];
    return 0;
}
