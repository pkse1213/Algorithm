/*
 SW Expert Academy
 1952. [모의 SW 역량테스트] 수영장
 
 DFS로 푸는 쉬웠던 문제
 */

#include <iostream>
#include <math.h>
using namespace std;

int answer;
int cost[4], swim[13];

void initialize()
{
    answer = 987654321;
}

void input()
{
    for(int i = 0; i < 4; i++)
    {
        cin >> cost[i];
    }
    
    for(int i = 1; i <= 12; i++)
    {
        cin >> swim[i];
    }
}

void dfs(int month, int money)
{
    if(month > 12)
    {
        answer = min(answer, money);
        return;
    }
    
    // 수영장을 이용하는 달
    if(swim[month] > 0)
    {
        for(int i = 0; i < 4; i++)
        {
            int n_month = month;
            int n_money = money;
            
            switch (i) {
                case 0:
                    n_month += 1;
                    n_money += swim[month] * cost[i];
                    break;
                case 1:
                    n_month += 1;
                    n_money += cost[i];
                    break;
                case 2:
                    n_month += 3;
                    n_money += cost[i];
                    break;
                case 3:
                    n_month += 12;
                    n_money += cost[i];
                    break;
                default:
                    break;
            }
            
            dfs(n_month, n_money);
        }
    }
    // 수영장 이용 X
    else
    {
        dfs(month + 1, money);
    }
}

int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case)
    {
        initialize();
        input();
        dfs(1, 0);
        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}
