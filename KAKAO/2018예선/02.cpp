#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

vector<double> V;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    double N, K, T;
    cin >> N >> K;
    for(int i = 0; i < N; i++)
    {
        cin >> T;
        V.push_back(T);
    }
 
    double Answer = 987654321;
    
    for(int i = 0; i < N - K + 1; i++)
    {
        for(int k = K; k < N - i + 1; k++)
        {
            double Sum = 0;
            for(int j = i; j < i + k; j++)
            {
                Sum += V[j];
            }
            
            double Avg = Sum / k;
            
            double Sum2 = 0;
            for(int j = i; j < i + k; j++)
            {
                Sum2 += (V[j] - Avg)*(V[j] - Avg);
            }
            Answer = min(Answer, sqrt(Sum2 / k));
        }
    }
    
    printf("%.11lf\n", Answer);
    
    return 0;
}
