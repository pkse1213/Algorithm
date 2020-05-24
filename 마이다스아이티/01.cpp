#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
#include <deque>
#include <stack>
#include <map>
#include <sstream>
#include <regex>
#include <math.h>
#define MAX 11
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

string solution(vector<string> strs)
{
    string answer = "";
    
    
    int len = 10001;
    for(int i = 0; i < strs.size(); i++)
    {
        if(strs[i].size() < len) len = strs[i].size();
    }
    
    for(int i = 0; i < len; i++)
    {
        char c = strs[0][i];
        for(int s = 1; s < strs.size(); s++)
        {
            if(strs[s][i] != c) return answer;
        }
        answer += c;
    }
    return answer;
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << solution({"a", "b", "c"});
    return 0;
}
