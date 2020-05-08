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


int solution(vector<vector<int>> rates, vector<vector<int>> customers)
{
    int ans = 0;
    for(int i = 0; i < customers.size(); i++)
    {
        int m = 987654321;
        for(int r = 0; r < rates.size(); r++)
        {
            int money = 0;
            money += rates[r][0];
            int call = rates[r][1] - customers[i][0];
            int msg = rates[r][3] - customers[i][1];
            int data = rates[r][5] - customers[i][2];
            
            if(call < 0 && rates[r][1] != -1) money += -1*call*60*rates[r][2];
            if(msg < 0&& rates[r][3] != -1) money += -1*msg*rates[r][4];
            if(data < 0&& rates[r][4] != -1) money += -1*data*rates[r][6];
            
            if(money < m) m = money;
        }
        ans += m;
    }
    
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cout << solution({{19800, 40, 5, 100, 30, 1200, 22}, {27500, 60, 4, 150, 20, 2000, 25}, {39600, 200, 3, 100, 40, 6000, 21}, {50000, 200, 3, -1, 0, 6000, 21}}, {{70, 165, 2020}, {42, 110, 1205}, {100, 120, 6100}, {100, 999, 6100}, {80, 130, 3500}});
    return 0;
}
