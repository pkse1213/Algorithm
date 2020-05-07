#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> v1;
    vector<int> v2;
    
    // 안정정렬
    stable_sort(v1.begin(), v1.end());
    
    // vector 복사
    v1.assign(v2.begin(), v2.end());
    copy(v2.begin(), v2.end(), v1.begin());
    
    // vector 뒤집기
    reverse(v1.begin(), v1.end());
    
    // 최대값 구하기
    int max_num = max_element(v1.begin(), v2.begin();
    /*
     // Array일 경우
     DP[1] to DP[n]중에 최댓값의 주소를 반환하는 함수
     *max_element(DP+1, DP+N+1)
     iterator를 반환하기 때문에 앞에 *를 붙혀줘야 함.
     */
                              
        
    
}
