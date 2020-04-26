/*
 해시. 완주하지 못한 선수
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

// 해시맵 사용
string solution1(vector<string> participant, vector<string> completion) {
    string answer = "";
    
    map<string, int> m;
    for(int i = 0; i < completion.size(); i++)
    {
        if(m.find(completion[i]) == m.end())
            m[completion[i]] = 1;
                                               
        else
            m[completion[i]]++;
    }
    
    for(int i = 0; i < participant.size(); i++)
    {
        if(m.find(participant[i]) == m.end()) return participant[i];
        else
        {
            if(--m[participant[i]] < 0) return participant[i];
        }
    }
    return answer;
}

// 배열 사용
string solution2(vector<string> participant, vector<string> completion) {

    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());
    for(int i = 0; i < completion.size(); i++)
    {
        if(participant[i] != completion[i]) return participant[i];
    }
    return participant.back();
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << solution2({"mislav", "stanko", "mislav", "ana"}, {"stanko", "ana", "mislav"});
    return 0;
}
