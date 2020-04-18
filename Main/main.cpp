#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#define MAX 1000001
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

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
