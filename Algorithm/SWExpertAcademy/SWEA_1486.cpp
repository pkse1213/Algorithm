/*
 SW Expert Academy
 1486. 장훈이의 높은 선반
 
 DFS 완전탐색!
 */
#include <iostream>
#include <algorithm>
#include <math.h>
#define MAX 21
using namespace std;

int T, N, B; // 테케, 사람 수, 빌딩 높이
int H[MAX]; // 사람마다 키
int res;

void dfs(int cnt, int height){
    if(height >= B){ // 다 도는 것이 아니라 높이가 B보다 커지면 종료
        if(height < res)
            res = height;
        return;
    }
    
    if(cnt == N)
        return;
    
    dfs(cnt+1, height+H[cnt]); // 현재 인덱스 사람의 키를 더할 경우
    dfs(cnt+1, height); // 현재 인덱스 사람의 키를 제외시키고 넘어갈 경우
}

int SWEA_1486() {
    cin >> T;
    
    for(int t=1; t<=T; t++){
        cin >> N >> B;
        
        res = 0;
        for(int i=0; i<N; i++){
            cin >> H[i];
            res += H[i];
        }
        
        dfs(0, 0);
        
        cout << "#" << t << " " << res - B << endl;
        
    }
    return 0;
}
