//
//  02.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/03.
//  Copyright © 2020 박세은. All rights reserved.
//
/*
 Summer/Winter Coding(2019)
 종이접기

 */
#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n) {
   
    vector<int> answer;
    answer.push_back(0);
    
    for(int k = 1; k < n ; k++)
    {
        vector<int> v;
        for(int i = 0; i < answer.size(); i++)
        {
            if(i%2 == 0)
            {
                v.push_back(0);
                v.push_back(answer[i]);
                v.push_back(1);
            }
            else
            {
                v.push_back(answer[i]);
            }
        }
        answer = v;
    }
    
    return answer;
}
