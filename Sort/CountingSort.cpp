/*
 백준 15688. 수 정렬하기 5 문제
 
 계수 정렬인데 범위가 -1000000 ~ 1000000 이라서
 음수를 없애주기 위해 입력 받을 때 +1000000을 해줬다.
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
