/*
 해시. 전화번호 목록
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

bool compare(string A, string B)
{
    return A.size() < B.size();
}

// 해시맵 사용
bool solution1(vector<string> phone_book)
{
    bool answer = true;
    sort(phone_book.begin(), phone_book.end(), compare);
    map<string, int> m;
    
    for(int i = 0; i < phone_book.size(); i++)
    {
        if(!m.empty())
        {
            string str = "";
            for(int j = 0; j < phone_book[i].size(); j++)
            {
                str += phone_book[i][j];
                if(m.find(str) != m.end()) return false;
            }
            m[str] = 1;
        }
        else m[phone_book[i]] = 1;
    }
    
    return answer;
}

// 배열 사용
bool solution2(vector<string> phone_book)
{
    sort(phone_book.begin(), phone_book.end());
    for(int i = 0; i < phone_book.size() - 1; i++)
    {
        if(phone_book[i] == phone_book[i+1].substr(0,phone_book[i].size())) return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << solution1({"119", "97674223", "1195524421"});
    cout << solution2({"119", "97674223", "1195524421"});
    return 0;
}
