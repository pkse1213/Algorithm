#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
typedef pair<int, int> pii;

bool compare(pair<string, int> A, pair<string, int> B)
{
    return A.second > B.second;
}

bool compare2(pii A, pii B)
{
    return A.first > B.first;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    map<string, int> gm;
    map<string, vector<pii>> pm;
    
    for(int i = 0; i < genres.size(); i++)
    {
        gm[genres[i]] += plays[i];
        pm[genres[i]].push_back({plays[i],i});
    }
    vector<pair<string, int>> v;
    map<string, int>::iterator it;
    for(it = gm.begin(); it != gm.end(); it++)
    {
        v.push_back({it->first, it->second});
    }
    
    sort(v.begin(), v.end(), compare);
    
    for(int i = 0; i < v.size(); i++)
    {
        string genre = v[i].first;
        sort(pm[genre].begin(), pm[genre].end(), compare2);
        
        int size = (int)pm[genre].size();
        answer.push_back(pm[genre][0].second);
        if(size >= 2) answer.push_back(pm[genre][1].second);
    }
    
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    solution({"classic", "pop", "classic", "classic", "pop"}, {500, 600, 150, 800, 2500});
    return 0;
}
