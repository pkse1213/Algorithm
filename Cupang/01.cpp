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
    /*
     a는 기본 요금입니다.(1 ≤ a ≤ 100,000)
     b는 무료 통화량(분)입니다. (-1 ≤ b ≤ 1,000) 단, b = -1 인 경우는 무료 통화량이 무제한이라는 뜻입니다.
     c는 초과 통화 요금(원/초)입니다.(0 ≤ c ≤ 100) 단, b = -1 라면, 반드시 c = 0입니다.
     d는 무료 문자 개수입니다.(-1 ≤ d ≤ 1,000) 단, d = -1 인 경우는 무료 문자 개수가 무제한이라는 뜻입니다.
     e는 초과 문자 요금(원/개)입니다.(0 ≤ e ≤ 100) 단, d = -1 라면, 반드시 e = 0입니다.
     f는 무료 데이터 용량(메가)입니다.(-1 ≤ f ≤ 10,000) 단, f = -1 인 경우는 무료 데이터 용량이 무제한이라는 뜻입니다.
     g는 초과 데이터 요금(원/메가)입니다.(0 ≤ g ≤ 100) 단, f = -1 라면, 반드시 g = 0입니다.

     */
    /*
     a는 통화량(분)입니다. (0 ≤ a ≤ 1,000)
     b는 문자 사용량(개수)입니다. (0 ≤ b ≤ 1,000)
     c는 데이터 사용량(메가)입니다. (0 ≤ c ≤ 10,000)
     */
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
            
            if(call > 0 && rates[r][1] != -1) money += -1*call*60*rates[r][2];
            if(msg > 0&& rates[r][3] != -1) money += -1*msg*rates[r][4];
            if(data > 0&& rates[r][4] != -1) money += -1*data*rates[r][6];
            
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
