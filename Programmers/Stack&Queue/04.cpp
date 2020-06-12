//
//  04.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/12.
//  Copyright © 2020 박세은. All rights reserved.
//

// 프린터
#include <string>
#include <vector>
#include <queue>

using namespace std;

queue<pair<int, int>> pq;

int solution(vector<int> p, int ll) {
    int answer = 0;
    int num[10] = {0};
    for(int i = 0; i < p.size(); i++)
    {
        pq.push({p[i], i});
        num[p[i]]++;
    }
    
    
    int n = 0;
    while(!pq.empty())
    {
        n++;
        
        while(1)
        {
            bool flag = true;
            pair<int, int> tmp = pq.front();
            for(int i = tmp.first + 1; i <= 9; i++)
            {
                if(num[i] > 0)
                {
                    flag = false;
                    break;
                }
            }
            if(flag) break;
            else
            {
                pq.push(pq.front());
                pq.pop();
            }
        }
        
        if(pq.front().second == ll)
        {
            answer = n;
            break;
        }
        num[pq.front().first]--;
        pq.pop();
    }
    return answer;
}
