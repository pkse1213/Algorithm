#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

int solution(string inputString) {
    int answer = 0;
    stack<char> s1, s2, s3, s4;
    
    for(int i = 0; i < inputString.size(); i++)
    {
        char ch = inputString[i];
        
        if(ch == '(')
        {
            s1.push(ch);
        }
        else if(ch == ')')
        {
            if(!s1.empty() && s1.top() == '(')
            {
                answer++;
                s1.pop();
            }
            else
            {
                return -1;
            }
        }
        else if(ch == '{')
        {
            s2.push(ch);
        }
        else if(ch == '}')
        {
            if(!s2.empty() && s2.top() == '{')
            {
                answer++;
                s2.pop();
            }
            else
            {
                return -1;
            }
        }
        else if(ch == '<')
        {
            s3.push(ch);
        }
        else if(ch == '>')
        {
            if(!s3.empty() && s3.top() == '<')
            {
                answer++;
                s3.pop();
            }
            else
            {
                return -1;
            }
        }
        else if(ch == '[')
        {
            s4.push(ch);
        }
        else if(ch == ']')
        {
            if(!s4.empty() && s4.top() == '[')
            {
                answer++;
                s4.pop();
            }
            else
            {
                return -1;
            }
        }
    }
    
    if(!s1.empty() || !s2.empty() || !s3.empty() || !s4.empty())
    {
        return -1;
    }
    
    return answer;
}

int main()
{
    cout << solution(">_<") << endl;
    return 0;
}
