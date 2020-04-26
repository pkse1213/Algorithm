/*
 해시. 위장
 */
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    
    map<string, int> m;
    for(int i = 0; i < clothes.size(); i++)
    {
        m[clothes[i][1]]++;
    }
    
    map<string, int>::iterator it;
    for(it = m.begin(); it != m.end(); it++)
    {
        answer *= (it->second+1);
    }
    
    return answer-1;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cout << solution({{"yellow_hat", "headgear"}, {"blue_sunglasses", "eyewear"}, {"green_turban", "headgear"}});
    return 0;
}
