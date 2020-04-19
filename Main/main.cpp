/*
 1912. 연속합
 
 
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
