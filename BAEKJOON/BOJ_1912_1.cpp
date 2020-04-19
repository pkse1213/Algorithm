/*
 1912. 연속합
 
 쉽게 생각할 수 있는 3중 for문으로 푸는 방법.
 O(N^3)이기 때문에, 100000개의 데이터는 시간효율성 똥
 */
#include <iostream>
#include <algorithm>
#define MAX 100005
#define INF 987654321
using namespace std;

int Number[MAX];
int main()
{
    int N;
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> Number[i];
    }
    
    int Max = -INF;
    
    for(int s = 0; s < N; s++)
    {
        for(int e = s + 1; e < N; e++)
        {
            int Sum = 0;
            for(int i = s; i <= e; i++)
            {
                Sum += Number[i];
            }
            Max = max(Max, Sum);
        }
    }
        
    cout << Max;
    return 0;
}
