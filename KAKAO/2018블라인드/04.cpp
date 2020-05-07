/*
 [3차] 방금그곡
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int cal_time(string time)
{
    int clock = atoi(time.substr(0,2).c_str());
    int minute = atoi(time.substr(3,2).c_str());
    
    return clock*60 + minute;
}

/*
 조건이 일치하는 음악이 여러 개일 때에는 라디오에서 재생된 시간이 제일 긴 음악 제목을 반환한다.
 재생된 시간도 같을 경우 먼저 입력된 음악 제목을 반환한다.
 */
bool comp(pair<pair<string, int>,int> A, pair<pair<string, int>,int> B)
{
    if(A.first.second == B.first.second) return A.second < B.second;
    else return A.first.second > B.first.second;
}

string solution(string m, vector<string> musicinfos)
{
    vector<pair<pair<string, int>,int>> answer;
    string melody = "";
    for(int i = 0; i < m.length(); i++)
    {
        if(m[i] == '#') melody.back() += 32;
        else melody += m[i];
    }
    
    for(int k = 0; k < musicinfos.size(); k++)
    {
        stringstream ss(musicinfos[k]);
        string res;
        string info[4];
        int str_idx = 0;
        while (getline(ss, res, ','))
        {
            info[str_idx++] = res;
        }
        
        string music = "";
        
        for(int i = 0; i < info[3].length(); i++)
        {
            if(info[3][i] == '#') music.back() += 32;
            else music += info[3][i];
        }
        
        int time = cal_time(info[1]) - cal_time(info[0]);
        
        int idx_melody = 0, idx_music = 0;
        for(int t = 0; t < time; t++)
        {
            if(idx_music == music.length()) idx_music = 0;
            if(melody[idx_melody++] != music[idx_music++]) idx_melody = 0;
            
            if(idx_melody == melody.length())
            {
                answer.push_back({{info[2], time}, k});
                break;
            }
            
        }
    }
    if(answer.size() == 0) return "(None)";
    else if(answer.size() == 1) return answer[0].first.first;
    else
    {
        stable_sort(answer.begin(), answer.end(), comp);
        return answer[0].first.first;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cout << solution(    "ABC", {"12:00,12:14,HELLO,C#DEFGAB", "13:00,13:05,WOdfRLD,ABCDEF", "13:00,13:05,WORLD,ABCDEF"});
    return 0;
}
