#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
#include <deque>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <regex>
#include <math.h>
#define MAX 11
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;


vector<int> solution(vector<string> gems) {
    vector<int> answer;
    map<string, int> m;
    set<string> se;
    
    for(int i = 0; i < gems.size(); i++)
    {
        se.insert(gems[i]);
    }
    int s = 0;
    int e = 0;
    
    pii pi = {-987654321,987654321};
    
    //"DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA"

    while (1)
    {
        if(e == gems.size()) break;
        m[gems[e]]++;
        
        while(se.size() == m.size())
        {
            if(pi.second-pi.first > e-s)
            {
                pi = {s,e};
            }
            m[gems[s]]--;
            if(m[gems[s]] == 0)
                m.erase(gems[s]);
            s++;
        }
        e++;
    }
    
    //["DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA"]
    answer.push_back(pi.first+1);
    answer.push_back(pi.second+1);
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    solution({"DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA"});
    return 0;
}
