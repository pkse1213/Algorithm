/*
 9095. 1,2,3 더하기
 
 DP[i] = DP[i-1] + DP[i-2] + DP[i-3]가 되는 이유
 DP[i-1]의 경우들에서 +1씩만 해주면 된다
 DP[i-2]의 경우들에서 +2씩만 해주면 된다
 DP[i-3]의 경우들에서 +3씩만 해주면 된다
 
 1,2,3으로만 이루어져 있기 때문에, +1, +2, +3 가능
 만약 1,2로만 이루어져 있다면 DP[i] = DP[i-1] + DP[i-2]
*/
#include <iostream>
using namespace std;

int T, N, DP[12] = {0, };

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    DP[1] = 1;
    DP[2] = 2;
    DP[3] = 4;

    for(int i = 4; i <= 11; i++)
    {
        DP[i] = DP[i-1] + DP[i-2] + DP[i-3];
    }
    
    cin >> T;
    for(int i = 0; i < T; i++)
    {
        cin >> N;
        cout << DP[N] << endl;
    }
    return 0;
}
