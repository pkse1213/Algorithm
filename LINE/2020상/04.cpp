/*
 벡터 중복 제거
 sort(transactions.begin(), transactions.end());
 transactions.erase(unique(transactions.begin(),transactions.end()),transactions.end());
 
 */
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;

vector<vector<string>> solution(vector<vector<string>> snapshots, vector<vector<string>> transactions) {
    vector<vector<string>> answer;
    map<string, string> result;
    map<string, string>::iterator it;

    sort(transactions.begin(), transactions.end());
    transactions.erase(unique(transactions.begin(),transactions.end()),transactions.end());
    
    for(int i = 0; i < transactions.size(); i++)
    {
        int money = atoi(transactions[i][3].c_str());
        
        if(transactions[i][1] == "WITHDRAW")
        {
            money *= -1;
        }
        
        if(result.find(transactions[i][2]) == result.end())
        {
            result[transactions[i][2]] = to_string(money);
        }
        else
        {
            int temp = atoi(result[transactions[i][2]].c_str());
            result[transactions[i][2]] = to_string(temp + money);
        }
    }
    
    for(int i = 0; i < snapshots.size(); i++)
    {
        if(result.find(snapshots[i][0]) == result.end())
        {
            result[snapshots[i][0]] = snapshots[i][1];
        }
        else
        {
            int temp = atoi(result[snapshots[i][0]].c_str());
            int money = atoi(snapshots[i][1].c_str());
            result[snapshots[i][0]] = to_string(temp + money);
        }
    }
    
    for(it = result.begin(); it != result.end(); it++)
    {
        answer.push_back({ it->first , it->second });
    }
    
    return answer;
}

int main()
{
    vector<vector<string>> result = solution({{"ACCOUNT1", "100"}, {"ACCOUNT2", "150"}},
                                             {{"1", "SAVE", "ACCOUNT2", "100"},
                                                 {"2", "WITHDRAW", "ACCOUNT1", "50"},
                                                 {"1", "SAVE", "ACCOUNT2", "100"},
                                                 {"4", "SAVE", "ACCOUNT3", "500"},
                                                 {"3", "WITHDRAW", "ACCOUNT2", "30"}});
    
    for(int i = 0; i < result.size(); i++)
    {
        cout << result[i][0] << ' ' << result[i][1] << endl;
    }
    return 0;
}
