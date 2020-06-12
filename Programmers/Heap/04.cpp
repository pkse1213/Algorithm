//
//  04.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/12.
//  Copyright © 2020 박세은. All rights reserved.

//  라면공장
#include <string>
#include <vector>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, less<int>> pq;

int solution(int stock, vector<int> dates, vector<int> supplies, int k) {
    int answer = 0;
    int j = 0;
    for(int i = 0; i < k; i++)
    {
        if(i == dates[j])
        {
            pq.push(supplies[j++]);
        }
        if(stock == 0)
        {
            stock += pq.top();
            pq.pop();
            answer++;
        }
        stock--;
    }

    return answer;
}
