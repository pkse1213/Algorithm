#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;


int solution(string road, int n) {
    int answer = -1;
    
    vector<int> new_road;
    vector<int> zero_idx;
    
    int one_cnt = 0;
    for(int i = 0; i < road.size(); i++)
    {
        if(road[i] == '1')
        {
            one_cnt++;
        }
        else if(road[i] == '0')
        {
            if(one_cnt > 0) new_road.push_back(one_cnt);
            new_road.push_back(0);
            zero_idx.push_back((int)new_road.size() - 1);
            one_cnt = 0;
        }
    }
    if(one_cnt > 0) new_road.push_back(one_cnt);
    
    if(n > zero_idx.size())
    {
        n = (int)zero_idx.size();
    }
    
    for(int i = 0; i < zero_idx.size() - (n - 1); i++)
    {
        int cnt = 0;
        int left = zero_idx[i];
        int right = zero_idx[i + n - 1];
        
        if(left > 0) left--;
        if(right < new_road.size() - 1) right++;
        
        for(int j = left; j <= right; j++)
        {
            cnt += new_road[j];
        }
        answer = max(answer, cnt + n);
    }

    return answer;
}

int main()
{
    cout << solution("001100", 5);
    return 0;
}
