//
//  01.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/04.
//  Copyright © 2020 박세은. All rights reserved.
//
//  디스크 컨트롤러

#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 우선순위큐 정렬
struct cmp
{
    bool operator()(vector<int> a, vector<int> b)
    {
        return a[1] > b[1];
    }
};

priority_queue<vector<int>, vector<vector<int>>, cmp> pq;

int solution(vector<vector<int>> jobs)
{
    int answer = 0;
    sort(jobs.begin(), jobs.end());
    int n = 0;
    int time = 0;
    while(n < jobs.size() || !pq.empty())
    {
        while(n < jobs.size() && jobs[n][0] <= time)
        {
            pq.push(jobs[n]);
            n++;
        }
        if(!pq.empty())
        {
            time += pq.top()[1];
            answer += (time - pq.top()[0]);
            pq.pop();
        }
        else
        {
            // 우선순위 큐에 아무것도 없으면 현재 가장 먼저 들어온 작업의 시작시간으로 Time 변경
            time = jobs[n][0];
        }
    }
    
    answer /= jobs.size();
    return answer;
}
