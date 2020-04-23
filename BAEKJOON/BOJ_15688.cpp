/*
 15688. 수 정렬하기 5
 
 계수 정렬
 */
#include <iostream>
#include <algorithm>
using namespace std;

int Count[2000001];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N, Max = -1;
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int Tmp;
        cin >> Tmp;
        Count[Tmp + 1'000'000]++;
        Max = max(Max, Tmp + 1'000'000);
    }
    for(int i = 0; i <= Max; i++)
    {
        for(int j = 0; j < Count[i]; j++)
        {
            cout << i-1'000'000 << '\n';
        }
    }
    return 0;
}
