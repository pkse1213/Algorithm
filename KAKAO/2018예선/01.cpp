#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <math.h>
using namespace std;
int M2017[7] = {0, 500, 300, 200, 50, 30, 10};

vector<int> Score2017;
vector<int> Score2018;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    for(int i = 1; i <= 6; i++)
    {
        Score2017.insert(Score2017.end(), i, M2017[i]);
    }
    
    int M = 1024;
    double C = 0.5;
    for(int i = 0; i < 5; i++)
    {
        M /= 2;
        C *= 2;
        Score2018.insert(Score2018.end(), C, M);
    }
    
    int T, A, B;
    cin >> T;
    for(int i = 0; i < T; i++)
    {
        int Money = 0;
        cin >> A >> B;
        
        if(0 < A && A <= 21) Money += Score2017[A-1];
        if(0 < B && B <= 31) Money += Score2018[B-1];
        printf("%d\n", Money*10000);
    }
    return 0;
}
