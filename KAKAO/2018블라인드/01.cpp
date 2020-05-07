/*
 [3차] 압축
 */
#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(string msg) {
    vector<int> answer;
    map<string, int> m;
    
    // "A" ~ "Z"를 map에 넣는 방법
    // char형이면 i+'A'로 쉽게 넣었을 텐데, string타입이라 이렇게 처리해야 함
    int id = 1;
    for(char a = 'A'; a <= 'Z'; a++, id++)
    {
        string tmp = "";
        tmp += a;
        m[tmp] = id;
    }
    
    for(int i = 0; i < msg.size();)
    {
        int idx = 0, cnt = 0;
        
        /*
         사전에 없는 str을 먼저 찾아내고 하는 방법도 있음!
         while (i<msg.size() && m[str]>0) {
                    str = str + msg[i];
                    i++;
         }
         */
        for(int size = 1; size <= msg.size()-i; size++)
        {
            string s = msg.substr(i, size);
            
            if(m.find(s) == m.end())
            {
                m[s] = id++;
                break;
            }
            else
            {
                cnt++; // 체크한 idx만큼 건너뛰기 위해!
                idx = m[s];
            }
        }
        i+=cnt;
        answer.push_back(idx);
    }
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    solution("TOBEORNOTTOBEORTOBEORNOT");
    return 0;
}
