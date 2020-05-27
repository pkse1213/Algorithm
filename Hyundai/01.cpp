#include <cstring>
#include <vector>
#include <sstream>

using namespace std;

vector<int> solution(vector<string> purchase) {
    vector<int> answer;
    answer.resize(5, 0);
    int money[366] = {0};
    int day[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
    for(int i = 0; i < purchase.size(); i++)
    {
        stringstream ss1(purchase[i]);
        string res;
        vector<string> v1;
        while (getline(ss1, res, ' '))
        {
            v1.push_back(res);
        }
        
        stringstream ss2(v1[0]);

        vector<int> v2;
        while (getline(ss2, res, '/'))
        {
            v2.push_back(atoi(res.c_str()));
        }
        int num = day[v2[1]-1] + v2[2];
        for(int j = num; j < num+30; j++)
        {
            money[j] += atoi(v1[1].c_str());
        }
    }
    /*
     브론즈    최근 30일간 0원 이상 10,000원 미만 구매 고객
     실버    최근 30일간 10,000원 이상 20,000원 미만 구매 고객
     골드    최근 30일간 20,000원 이상 50,000원 미만 구매 고객
     플래티넘    최근 30일간 50,000원 이상 100,000원 미만 구매 고객
     다이아몬드    최근 30일간 100,000원 이상 구매 고객
     */
    for(int i = 1; i <= 365; i++)
    {
        if(0 <=  money[i] && money[i] < 10000) answer[0]++;
        else if(10000 <=  money[i] && money[i] < 20000) answer[1]++;
        else if(20000 <=  money[i] && money[i] < 50000) answer[2]++;
        else if(50000 <=  money[i] && money[i] < 100000) answer[3]++;
        else if(100000 <=  money[i]) answer[4]++;
    }
    return answer;
}

int main()
{
    solution({"2019/01/01 5000", "2019/01/20 15000", "2019/02/09 90000"});
    return 0;
}
