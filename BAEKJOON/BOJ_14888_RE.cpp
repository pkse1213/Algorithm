#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, n, o[4];
vector<int> num;
vector<int> opr; // +, -, *, /
vector<int> res;

int operate(int n1, int n2, int c)
{
    if(c == 0) return n1 + n2;
    else if(c == 1) return n1 - n2;
    else if(c == 2) return n1 * n2;
    else return n1 / n2;
}

void calculate()
{
    int sum = operate(num[0], num[1], opr[0]);
    for(int i = 1; i < opr.size(); i++)
    {
        sum = operate(sum, num[i+1], opr[i]);
    }
    res.push_back(sum);
}

void choose(int cnt)
{
    if(cnt == N-1)
    {
        calculate();
        return;
    }
    
    for(int i = 0; i < 4; i++)
    {
        if(o[i] > 0)
        {
            o[i]--;
            opr.push_back(i);
            choose(cnt + 1);
            
            o[i]++;
            opr.pop_back();
        }
    }
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> n;
        num.push_back(n);
    }
    
    for(int i = 0; i < 4; i++)
        cin >> o[i];
    
    choose(0);
    sort(res.begin(), res.end());
    cout << res.back() << '\n' << res.front();
    
    return 0;
}
