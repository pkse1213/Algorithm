#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;


int solution(string road, int n) {
    int answer = -1;
    
    int zero_cnt = 0;
    int road_length = 0;
    
    int start = 0;
    
    
    if(road[start] == '1')
    {
        road_length++;
    }
    else
    {
        if(n < 1)
        {
            for(int i = 1; i < road.size(); i++)
            {
                start++;
                if(road[i] == '1')
                {
                    road_length++; break;
                }
            }
        }
        else
        {
            zero_cnt++; road_length++;
        }
    }
    
    int end = start;
    
    while (++end < road.size()) {
        if(road[end] == '0')
        {
            if(++zero_cnt > n)
            {
                answer = max(answer, road_length);
                
                for(int i = start; i < end; i++)
                {
                    road_length--; start++;
                    
                    if(road[i] == '0') break;
                }
            }
        }
        road_length++;
    }
    
    return answer = max(answer, road_length);;
}

int main()
{
    cout << solution("010010111110111", 2);
    return 0;
}
