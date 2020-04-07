/*
 1405. 미친 로봇
 
 DFS
 
 << 소수점 자르기 >>
 오차범위를 10^-9 까지 허용하기 때문에, 10^-10 까지 출력하도록 소수점을 고정시켜 주었다.
 C++에서 cout의 소수점을 고정시켜주는 방법은
 cout.precision(10)    // 소수점 아래 10자리 까지 설정
 cout << fixed << Simple << endl; // 소수점 아래 고정 10자리 까지 출력
 
 >> 그러면 왜 4321.123456이 출력이 안되고 4321.123457이 되었을까?
 그 이유는 나머지 버리는 자리 수는 반올림이 되기 때문입니다.
 그래서 6째 자리까지 표현하고 7째 자리부터는 버려지기 때문에, 7째 자리인 "7"의 의미를 남기기 위해서 반올림이 되었습니다.
 고로, 4321.123457이 표현이 되었던 것입니다.


 "cout << fixed;"를 해제하시려면, "cout.unsetf(ios::fixed);"를 사용하시면됩니다.
 마찬가지로 "cout << fixed;"는 "cout.setf(ios::fixed);"로 표현이 가능합니다.

 참고글 https://pmoncode.tistory.com/20
 
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#define Max 29
using namespace std;

int N, P;
bool Map[Max][Max];
double Percent[4];
double Simple = 0;
int Dr[4] = { 0, 0, -1, 1 };
int Dc[4] = { -1, 1, 0, 0 };

void Input()
{
    cin >> N;
    for(int i = 0; i < 4; i ++)
    {
        cin >> P;
        Percent[i] = P / 100.0;
    }
}

void DFS(int R, int C, int Cnt, double Per)
{
    if(Cnt == N)
    {
        Simple += Per;
        return;
    }
    
    for(int i = 0; i < 4; i++)
    {
        int Nr = R + Dr[i];
        int Nc = C + Dc[i];
        
        if(Map[Nr][Nc]) continue;
        
        Map[Nr][Nc] = true;
        DFS(Nr, Nc, Cnt + 1, Per * Percent[i]);
        Map[Nr][Nc] = false;
    }
}

void Solve()
{
    for(int i = 0; i < 4; i++)
    {
        memset(Map, false, sizeof(Map));
        Map[14][14] = true;
        Map[14 + Dr[i]][14 + Dc[i]] = true;
        DFS(14 + Dr[i], 14 + Dc[i], 1, Percent[i]);
    }
    
    //소수점 자르기
    cout.precision(10);
    cout << fixed << Simple << endl;
}

int main()
{
    Input();
    Solve();
    return 0;
}

