/*
 BAEKJOON
 13458. 시험감독
 
 1) 정수 변수의 범위 -> long long
 첫째 줄에 시험장의 개수 N(1 ≤ N ≤ 1,000,000)이 주어진다.
 둘째 줄에는 각 시험장에 있는 응시자의 수 Ai (1 ≤ Ai ≤ 1,000,000)가 주어진다.
 셋째 줄에는 B와 C가 주어진다. (1 ≤ B, C ≤ 1,000,000)
 
 2) double과 int로 연산할 때 int로 결과가 나오는 쉬운 것을 간과함..^^
 */

#include <iostream>
#include <math.h>
#define MAX 1000001
using namespace std;

double n, b, c;
long long res = 0;
int a[MAX];

int main(int argc, char** argv)
{
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    
    cin >> b >> c;
    res += n;
    
    for(int i=0; i<n; i++){
        if(a[i]-b > 0){
            double k = (a[i]-b)/c;
            res += k;
            if(k-(int)k > 0) res++;
        }
        
        
    }
    
    cout << res;
    
    
    return 0;
}
