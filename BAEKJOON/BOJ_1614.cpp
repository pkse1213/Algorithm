/*
 1614. 영식이의 손가락
 
 수가 쭉 나열되는 것은 규칙이 있는지 살펴보자.
 범위를 잘 파악하자 int -> long
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
ll N, M;
ll Answer;

int main()
{
    cin >> N >> M;
    
    Answer = N - 1;
    if(M > 0)
    {
        if(N == 1 || N == 5)
        {
            Answer += 8 * M;
        }
        else
        {
            Answer += M / 2 * 8;
            
            if(N == 2)
            {
                if(M % 2) Answer += 6;
            }
            else if(N == 3)
            {
                if(M % 2) Answer += 4;
            }
            else if(N == 4)
            {
                if(M % 2) Answer += 2;
            }
        }
    }

    cout << Answer << endl;
    return 0;
}
