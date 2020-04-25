#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int solution(vector<string> ip_addrs, vector<string> langs, vector<int> scores) {
    int answer = 0;
    
    string lang[4] = { "C", "Java", "JavaScript", "Python3"};
    map<string, vector<pair<string, int>>> m;
    
    for(int i = 0; i < ip_addrs.size(); i++)
    {
        if(langs[i].size() <= 3)
        {
            langs[i] = "C";
        }
        
        m[ip_addrs[i]].push_back({langs[i], scores[i]});
    }
    
    map<string, vector<pair<string, int>>>::iterator it;
    for(it = m.begin(); it != m.end(); it++)
    {
        cout << it->first << endl;
        if(it->second.size() >= 4)
        {
            answer += it->second.size();
        }
        
        else if(it->second.size() == 3)
        {
            vector<pair<string, int>> psi = it->second;
            string before_lan = psi[0].first;
            int cnt = 1;
            for(int i = 1; i < psi.size(); i++)
            {
                if(psi[i].first == before_lan) cnt++;
            }
            if(cnt == 3) answer += 3;
            
        }
        else if(it->second.size() == 2)
        {
            if(it->second[0].first == it->second[1].first
               && it->second[0].second == it->second[1].second)
            {
                answer += 2;
            }
        }
    }
    
    return ip_addrs.size() - answer;
}

int main(){
    vector<string> ip = {"7.124.10.0", "7.124.10.0", "0.0.0.0", "7.124.10.0", "0.0.0.0", "7.124.10.0"};
    
    vector<string> lan = {"C++", "Java", "C#", "C#", "C", "Python3"};
    vector<int>se = {314, 225, 45, 0, 155, 400};
    
    cout << solution(ip, lan, se) << endl;
}
