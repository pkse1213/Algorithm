/*
 SW Expert Academy
 1204. [S/W 문제해결 기본] 1일차 - 최빈수 구하기
 
 */

#include <iostream>
#include <algorithm>

using namespace std;

int T;

int SWEA_1204(){
    int test_case;
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case){
        
        int score[100] = {0};
        int tmp;
        int res = 0;
        int max_student = 0;
        
        cin >> tmp;
        
        for(int i=0; i<1000; i++) {
            cin >> tmp;
            score[tmp]++;
        }
        
        for(int i=0; i<100; i++) {
            if(score[i] >= max_student){
                res = i;
                max_student = score[i];
            }
        }
        
        cout << "#" << test_case << " " << res << endl ;
        
    }
    return 0;
}
