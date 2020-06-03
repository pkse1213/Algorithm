//
//  01.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/03.
//  Copyright © 2020 박세은. All rights reserved.
//
/*
 2 x n 타일링

*/


#include <string>
#include <vector>

using namespace std;

int DP[60002];
int solution(int n)
{
    DP[1] = 1;
    DP[2] = 2;
    
    for(int i = 3; i <= n; i++)
    {
        DP[i] = (DP[i-1] + DP[i-2]) % 1000000007;
    }
    
    int answer = DP[n];
    return answer;
}
