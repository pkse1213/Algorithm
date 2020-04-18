#include <iostream>
#include <algorithm>
#define MAX 1005
using namespace std;

int DP[MAX][3];
int Price[MAX][3];
int Answer;

int main()
{
    int N;
    cin >> N;
    
    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cin >> Price[i][j];
        }
    }
    
    DP[1][0] = Price[1][0];
    DP[1][1] = Price[1][1];
    DP[1][2] = Price[1][2];
    
    for(int i = 2; i <= N; i++)
    {
        DP[i][0] = min(DP[i-1][1],DP[i-1][2]) + Price[i][0];
        DP[i][1] = min(DP[i-1][0],DP[i-1][2]) + Price[i][1];
        DP[i][2] = min(DP[i-1][0],DP[i-1][1]) + Price[i][2];
    }
    
    Answer = min(DP[N][0], DP[N][1]);
    cout << min(Answer, DP[N][2]);
    
    return 0;
}
