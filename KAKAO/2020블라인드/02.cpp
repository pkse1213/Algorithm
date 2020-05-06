/*
 문자열 압축
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

int solution(string s) {
    int answer = s.length();
    
    for(int size = 1; size < s.length()/2; size++)
    {
        string res = "";
        for(int i = 0; i < s.length();)
        {
            int cnt = 0;
            string target = s.substr(i, size);
            for(int j = i+size; j < s.length(); j += size)
            {
                string comp = s.substr(j, size);
                if(comp == target) cnt++;
                else break;
            }
            if(cnt > 0)
            {
                res += to_string(cnt+1) + target;
                i += (cnt+1)*size;
            }
            else
            {
                res += target;
                i += size;
            }
        }
        if(res.length() < answer) answer = res.length();
    }
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solution("aabbaccc");
    
    return 0;
}
