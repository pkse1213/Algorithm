//
//  02.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/04.
//  Copyright © 2020 박세은. All rights reserved.
//

// 이중우선순위큐

#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

vector<int> solution(vector<string> op) {
    vector<int> answer;
    deque<int> dq;
    for(int i = 0; i < op.size(); i++)
    {
        if(op[i][0] == 'I')
        {
            int num = atoi(op[i].substr(2,op[i].size()-2).c_str());
            dq.push_back(num);
            
            // deque 정렬
            sort(dq.begin(), dq.end(), less<int>());
        }
        else if(op[i] == "D 1")
        {
            if(!dq.empty()) dq.pop_back();
        }
        else if(op[i] == "D -1")
        {
            if(!dq.empty()) dq.pop_front();
        }
    }
    if(dq.empty()) answer = {0,0};
    else
    {
        answer.push_back(dq.back());
        answer.push_back(dq.front());
    }
    
    return answer;
}
