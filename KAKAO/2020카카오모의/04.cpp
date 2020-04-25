#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

map<ll, ll> Map;

ll Find(ll Num)
{
    if(Map.find(Num) == Map.end())
    {
        return Num;
    }
    else
    {
        ll Parent = Map[Num];
        return Map[Num] = Find(Parent);
    }
}

vector<ll> Solution(ll K, vector<ll> Room_Number)
{
    vector<ll> Answer;
    
    for(int i = 0; i < Room_Number.size(); i++)
    {
        ll Result = Find(Room_Number[i]);
        Map[Result] = Result + 1;
        Answer.push_back(Result);
    }
    
    return Answer;
}

int main()
{
    Solution(10, {1,3,4,1,3,1});
    
    return 0;
}
