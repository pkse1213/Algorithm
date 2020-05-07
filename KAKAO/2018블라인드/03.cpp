/*
 [3차] 파일명 정렬

 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool comp(pair<pair<string, int>, int> A, pair<pair<string, int>, int> B)
{
    if(A.first == B.first) return A.second < B.second;
    else if(A.first.first == B.first.first) return A.first.second < B.first.second;
    else return A.first.first < B.first.first;
}

vector<string> solution(vector<string> files)
{
    vector<string> answer;
    vector<pair<pair<string, int>, int>> v;
    
    for(int i = 0; i < files.size(); i++)
    {
        int idx = 0;
        string head = "";
        
        while (!isdigit(files[i][idx]))
        {
            if('a' <= files[i][idx] && files[i][idx] <= 'z')
                head += (files[i][idx] - 32);
            else
                head+= files[i][idx];
            
            idx++;
        }
        
        string tmp = "";
        while (isdigit(files[i][idx]))
        {
            tmp += files[i][idx];
            idx++;
        }
        
        int num = atoi(tmp.c_str());
        
        v.push_back({{head, num}, i});
    }
    
    sort(v.begin(), v.end(), comp);
    for(int i = 0; i < v.size(); i++)
    {
        answer.push_back(files[v[i].second]);
    }
    
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    solution({ "B-5", "B-050", "b-50", "b-14"});
    return 0;
}
