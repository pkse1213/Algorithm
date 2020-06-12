//
//  03.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/12.
//  Copyright © 2020 박세은. All rights reserved.

// 기능개발
#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> p, vector<int> s) {
    vector<int> answer;
    stack<pair<int, int>> st;
    for(int i = 0; i < p.size(); i++)
    {
        double dd = (100-p[i])/double(s[i]);
        int day = dd;
        if(dd-day > 0) day++;
        
        if(st.empty())
        {
            st.push({day,1});
        }
        else
        {
            if(st.top().first >= day)
            {
                st.top().second++;
            }
            else
            {
                answer.push_back(st.top().second);
                st.pop();
                st.push({day, 1});
            }
        }
    }
    if(!st.empty())
        answer.push_back(st.top().second);
    
    return answer;
}
