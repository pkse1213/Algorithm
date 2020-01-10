/*
 SW Expert Academy
 3074. 입국심사
 left:최소 = 0
 rignt:최대(최악) = 사람수 * 검색대의 가장 긴 시간
 
 사람수(P) = 시간 / 검색대 시간[1] + 시간 / 검색대 시간[2] + ... + 시간 / 검색대 시간[k]
 
 P가 사람수보다 크거나 같을 때까지! 이분탐색!!!!
 사람 수보다 큰 경우
 -> 시간 & right = (left+right)/2
 사람 수보다 작은 경우
 -> 시간 & left = (left+right)/2
 */

#include <iostream>
using namespace std;
int t,n,m; // n=심사대 갯수, m=사람수
int tk[100001];

int SWE_3974() {
    scanf("%d", &t);
    
    for(int j=0; j<t; j++){
        scanf("%d %d", &n, &m);
        long long MAX = 0;
        
        for(int k=1; k<=n; k++){
            scanf("%d", &tk[k]);
            if(tk[k]>MAX) MAX = tk[k];
        }
        
        long long left = 0;
        long long right = m * MAX;
        long long mid;
        
        long long min = right; // 결과(최소시간)
        
        // 질문????? 왜 left<right는 안되나?!
        // left=6 , right=9 , mid=7 인 경우에 m보다 커서
        // -> right=6(mid-1), min = 7(mid)가 되었다.
        // (left<right)만 했을 경우 min = 7 인채로 종료된다.
        // 하지만 (left<=right)인경우
        // mid = 6((left + right)/2)이 되고
        // 검사할 사람수와 같거나 클 경우
        // min = 6인 값을 얻을 수 있다.
        while (left<=right) {
            mid = (left + right) / 2; // 가운데 값부터 시작
            
            long long cnt = 0;
            for(int k=1; k<=n; k++){
                cnt += (mid / tk[k]);
            }
            
            // 계산한 총 사람 수가 실제 사람 수보다 적은 경우,
            // 이 시간은 부족한 시간임. 현재 기준 시간보다 더 긴 시간이 필요함
            // 그래서 최소 시간(min)의 변동이 없음.
            if(cnt < m){
                left = mid + 1;
            }
            
            // 계산한 총 사람 수가 실제 사람 수보다 많거나 같은 경우,
            // 일단 그 시간은 사람을 다 검사할 수 있는 시간이므로
            // 최소 시간(min)으로 될 수 있음.
            else {
                if(min > mid) {
                    min = mid;
                }
                right = mid - 1;
            }
        }
        
        printf("#%d %lld\n", j+1, min);
        
    }
    return 0;
}
