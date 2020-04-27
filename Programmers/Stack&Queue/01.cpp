/*
 스택 큐. 탑
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

vector<int> solution(vector<int> heights) {
    vector<int> answer;
    answer.resize(heights.size(), 0);
    
    stack<int> s;
    for(int i = 0; i < heights.size(); i++)
    {
        s.push(heights[i]);
    }
    
    for(int i = (int)heights.size()-1; i >= 0 ; i--)
    {
        int target = s.top();
        s.pop();
        
        stack<int> tmp;
        while(!s.empty())
        {
            int height = s.top();
            s.pop();
            tmp.push(height);
            if(height > target)
            {
                answer[i] = (int)s.size() + 1;
                break;
            }
        }
        while(!tmp.empty())
        {
            s.push(tmp.top());
            tmp.pop();
        }
    }
    
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    solution({3,9,9,3,5,7,2});
    return 0;
}
