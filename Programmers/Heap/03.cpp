//
//  03.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/04.
//  Copyright © 2020 박세은. All rights reserved.
//
// 더 맵게
#include <string>
#include <vector>
#include <queue>

using namespace std;
int solution(vector<int> s, int K) {
    int answer = 0;
    
    // 한번에 대입 가능

    priority_queue<int, vector<int>, greater<int>> q (s.begin(), s.end());
    /* 이렇게 대입 가능하지만
    for(int i = 0; i < s.size(); i++)
    {
        q.push(s[i]);
    }
    */
    
    while(q.size() >= 2)
    {
        answer++;
        int num = 0;
        for(int i = 1; i <= 2; i++)
        {
            num += q.top()*i;
            q.pop();
        }
        q.push(num);
        if(q.top() >= K) return answer;
    }
    return -1;
}
