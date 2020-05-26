#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <regex>
using namespace std;


bool comp(pair<string, vector<int>> A, pair<string, vector<int>> B)
{
    if(A.second.size() == B.second.size())
    {
        if(A.second[0] == B.second[0])
        {
            return A.first < B.first;
        }
        else
            return A.second[0] < B.second[0];
    }
    else
        return A.second.size() < B.second.size();
}

///["[403]James", "[404]Azad,Louis,Andy", "[101]Azad,Guard"]
vector<string> solution(vector<string> rooms, int target)
{
    vector<string> answer;
    
    regex re("\\[([0-9]*)\\]");
    smatch match;
    
    map<string, int> list; // target방에 있는 사람들 리스트
    map<string, vector<int>> m;
    map<string, vector<int>>::iterator it;
    
    for(int i = 0; i < rooms.size(); i++)
    {
        int num = 0;
        string name_list = "";
        
        if(regex_search(rooms[i], match, re))
        {
            num = atoi(match[1].str().c_str());
            name_list = match.suffix();
        }
        
        stringstream ss(name_list);
        string name;
        
        while (getline(ss, name, ','))
        {
            if(num == target) list[name] = 0;
            m[name].push_back(abs(target-num));
        }
    }
    
    vector<pair<string, vector<int>>> v;
    for(it = m.begin(); it != m.end(); it++)
    {
        if(list.find(it->first) == list.end())
            v.push_back(make_pair(it->first, it->second));
    }
    
    for(int i = 0; i < v.size(); i++)
    {
        sort(v[i].second.begin(), v[i].second.end());
    }
    sort(v.begin(), v.end(), comp);
    
    for(int i = 0; i < v.size(); i++)
    {
         answer.push_back(v[i].first);
    }
    
    return answer;
}

int main()
{
    vector<string> v = solution({"[101]Azad,Guard", "[202]Guard", "[303]Guard,Dzaz"},   202
                                );
    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
    return 0;
}
