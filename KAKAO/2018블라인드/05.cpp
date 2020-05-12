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
#include <regex>
#include <math.h>
#define MAX 11
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;


int solution1(vector<string> lines) {
    int answer = 0;

    vector<pair<double, double>> v1;
    regex re("[0-9 -]{11}(\\d{2}):(\\d{2}):(\\d{2}.\\d{3}) (\\d[0-9.]*)s");
    smatch match;
    for(int i = 0; i < lines.size(); i++)
    {
        if(regex_match(lines[i], match, re))
        {
            double time = 0;
            for(int j = 1, g = 2; j <= 3; j++, g--)
            {
                time += pow(60, g)*stod(match[j].str().c_str());
            }
            v1.push_back({time - stod(match[4]) + 0.001, time});
        }
    }
    
    queue<double> q;
    for(int i = 0; i < v1.size(); i++)
    {
        double s = v1[i].first;
        double e = v1[i].second;
        
        while(!q.empty() && s - q.front() >= 1)
        {
            q.pop();
        }
        q.push(e);
        if(q.size() > answer) answer = q.size();
    }
    
    return answer;
}

int solution2(vector<string> lines) {
    int answer = 0;
    
    vector<pair<double, double>> v1;
    regex re("[0-9 -]{11}(\\d{2}):(\\d{2}):(\\d{2}.\\d{3}) (\\d[0-9.]*)s");
    smatch match;
    for(int i = 0; i < lines.size(); i++)
    {
        if(regex_match(lines[i], match, re))
        {
            double time = 0;
            for(int j = 1, g = 2; j <= 3; j++, g--)
            {
                time += pow(60, g)*stod(match[j].str().c_str());
            }
            v1.push_back({time - stod(match[4]) + 0.001, time});
        }
    }
    
    int n = 1;
    int s = 0;
    int e = 0;
    
    while (1)
    {
        if(n > answer) answer = n;
        e++; n++;
        if(e == v1.size()) break;
        double st = v1[e].first;
        while (st - v1[s].second >= 1)
        {
            s++; n--;
        }
    }
    
    return answer;
}


int solution(vector<string> lines) {
    int answer = 0;
    vector<pair<int, int>> v1;
    
    /*
    int end=0;
    int elapsed_time;
    int y, m, d, hh, mm, ss, zzz;
    double elapsed_double;
    sscanf(lines[i].c_str(), "%d-%d-%d %d:%d:%d.%d %lfs", &y, &m, &d, &hh, &mm,&ss, &zzz, &elapsed_double);
    elapsed_time = (int)(elapsed_double * 1000);
    */
    
    regex re("[0-9 -]{11}(\\d{2}):(\\d{2}):(\\d{2}.\\d{3}) (\\d[0-9.]*)s");
    smatch match;
    for(int i = 0; i < lines.size(); i++)
    {
        if(regex_match(lines[i], match, re))
        {
            int time = 0;
            for(int j = 1, g = 2; j <= 3; j++, g--)
            {
                time += pow(60, g)*stod(match[j].str().c_str())*1000;
            }
            
            v1.push_back({time - stod(match[4])*1000 + 1, time});
        }
    }
    
    for(int i = 0; i < v1.size(); i++)
    {
        int n = 1;
        int s = v1[i].second;
        int e = s + 999;
        
        for(int j = i+1; j < v1.size(); j++)
        {
            if(v1[j].first <= e && v1[j].second >= s) n++;
        }
        if(answer < n) answer = n;
    }
    
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
//    solution({"2016-09-15 00:00:00.000 2.3s", "2016-09-15 23:59:59.999 0.1s"});
    solution({
        "2016-09-15 20:59:57.421 0.351s",
        "2016-09-15 20:59:58.233 1.181s",
        "2016-09-15 20:59:58.299 0.8s",
        "2016-09-15 20:59:58.688 1.041s",
        "2016-09-15 20:59:59.591 1.412s",
        "2016-09-15 21:00:00.464 1.466s",
        "2016-09-15 21:00:00.741 1.581s",
        "2016-09-15 21:00:00.748 2.31s",
        "2016-09-15 21:00:00.966 0.381s",
        "2016-09-15 21:00:02.066 2.62s"});
    
    return 0;
}
