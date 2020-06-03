//
//  02.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/03.
//  Copyright © 2020 박세은. All rights reserved.
//
/*
 타일 장식물
*/

#include <string>
#include <vector>

using namespace std;

long long solution(int N) {
    long long answer = 4;

    long long DP[81];
    DP[0] = 0;
    DP[1] = 1;
    
    for(int i = 2; i <= N; i++)
    {
        DP[i] = DP[i-1] + DP[i-2];
        answer += DP[i]*2;
    }
    return answer;
}
