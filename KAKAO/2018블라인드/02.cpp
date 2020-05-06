/*
 셔틀버스
 
 */
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";
    vector<int> bus_time[10];
    vector<int> time_table;
    
    for(int i = 0; i < timetable.size(); i++)
    {
        int clock = atoi(timetable[i].substr(0,2).c_str());
        int minute = atoi(timetable[i].substr(3,2).c_str());
        
        int time = clock*60 + minute - 540;
        time_table.push_back(time);
    }
    
    sort(time_table.begin(), time_table.end());
    
    for(int i = 0; i < timetable.size(); i++)
    {
        int time = time_table[i];
        int idx = 0;
        if(time > 0)
        {
            idx = time / t;
            if(time % t > 0) idx++;
        }
        
        if(idx >= n) continue;
        
        while (bus_time[idx].size() >= m)
        {
            idx++;
            if(idx >= n) break;
        }
        
        if(idx < n) bus_time[idx].push_back(time + 540);
    }
    // 원래는 막차시간
    int time = 540 + (n-1)*t;
    
    // 막차가 꽉차있으면 맨 마지막에 탄 애 -1분
    if(bus_time[n-1].size() == m)
    {
        sort(bus_time[n-1].begin(), bus_time[n-1].end());
        time = bus_time[n-1].back()-1;
    }
    
    int clock = time/60;
    int minute = time%60;
    if(clock < 10) answer += "0";
    answer += to_string(clock);
    answer += ":";
    if(minute < 10) answer += "0";
    answer += to_string(minute);
    
    return answer;
}

int main()
{
    cout << solution(2, 10, 2, {"12:59", "09:11", "09:01"});
    return 0;
}
