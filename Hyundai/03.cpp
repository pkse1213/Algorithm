#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
#include <deque>
#include <vector>
#include <regex>

#define MAX 1005
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

//97, 122
    
//    regex reg1("^([a-z]{3})([a-z]{0,3})([1-9]{1}[0-9]{0,5})*$");

//    if(regex_match(registered_list[i], reg1))
//    {
//
//    }
string solution(vector<string> registered_list, string new_id) {
    string answer = new_id;
    while (1)
    {
        bool find = true;
        for(int i = 0; i < registered_list.size(); i++)
        {
            if(registered_list[i] == answer)
            {
                find = false; break;
            }
        }
        
        if(find == false)
        {
            int i;
            string num = "";
            for(i = 0; i < answer.size(); i++)
            {
                if(48 <= answer[i] && answer[i] <= 57)
                {
                    num = answer.substr(i, answer.size()-1);
                    break;
                }
            }
            if(num == "")
            {
                answer += '1';
            }
            else
            {
                int tmp = atoi(num.c_str()) + 1;
                string str = to_string(tmp);
                answer.replace(i, i+str.size(), str);
            }
            
            
            cout << answer << endl;
        }
        else
        {
            break;
        }
    }
    
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    solution({"bird99", "bird98", "bird101", "gotoxy"}, "bird98");
    return 0;
}
