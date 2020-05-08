#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <regex>
using namespace std;
bool comp(pair<string, vector<int>> A, pair<string, vector<int>> B)
{

    if(A.second.size() == B.second.size() && A.second[0] == B.second[0])
    {
        return A.first < B.first;
    }
    if(A.second.size() == B.second.size())
    {
        return A.second[0] < B.second[0];
    }
    else
    {
        return A.second.size() < B.second.size();
    }
}

vector<string> solution(vector<string> rooms, int target){
    vector<string> answer;
    regex re(".([0-9]*).");
    smatch match;
    
    map<string, int> list;
    map<string, vector<int>> m;
    for(int i = 0; i < rooms.size(); i++)
    {
        string name = "";
        int num = 0;
        if(regex_search(rooms[i], match, re))
        {
            num = atoi(match[1].str().c_str());
            name = match.suffix();
        }
        stringstream ss(name);
        string res;
        while (getline(ss, res, ',')) {
            if(num == target) list[res] = 9;
            if(list.find(res) == list.end()) m[res].push_back(abs(num-target));
        }
    }

    map<string, vector<int>>::iterator it;
    vector<pair<string, vector<int>>> v;
    
    for(it = m.begin(); it != m.end(); it++)
    {
        v.push_back({it->first, it->second});
    }
    
    for(int i = 0; i < v.size(); i++)
    {
        sort(v[i].second.begin(), v[i].second.end());
    }
    sort(v.begin(), v.end(), comp);
    for(int i = 0; i < v.size(); i++)
    {
        if(list.find(v[i].first) == list.end() )
        answer.push_back(v[i].first);
    }
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<string> v = solution({"[101]Azad,Guard", "[202]Guard", "[303]Guard,Dzaz"},   202
                                );
    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
    return 0;
}
