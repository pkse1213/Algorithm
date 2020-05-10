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

map<char, int> m;
vector<int> num;
vector<char> op;
vector<char> v;
bool selected[3];

ll answer = 0;

long long cal(ll a, ll b, char c)
{
    if(c == '-') return a - b;
    if(c == '+') return a + b;
    else return a * b;
    
}

//"100-200*300-500+20"
void calculate()
{
    stack<ll> s;
    stack<char> o;
    
    s.push(num[0]);
    for(int i = 0; i < op.size(); i++)
    {

        while(!o.empty() && m[o.top()] >= m[op[i]])
        {
            ll n = s.top(); s.pop();
            char opera = o.top(); o.pop();
            s.top() = cal(s.top(), n, opera);
        }
            
        
        if(i == op.size()-1)
        {
            s.top() = cal(s.top(), num[i+1], op[i]);
            break;
        }
        
        
        if(m[op[i]] < m[op[i+1]])
        {
            o.push(op[i]);
            s.push(num[i+1]);
        }
        else if(m[op[i]] >= m[op[i+1]])
        {
            s.top() = cal(s.top(), num[i+1], op[i]);
        }
    }
    
    if(answer < abs(s.top())) answer = abs(s.top());
    
}

void dfs(int cnt)
{
    if(cnt == v.size())
    {
        calculate();
        return;
    }
    for(int i = 0; i < v.size(); i++)
    {
        if(selected[i] == true) continue;
        m[v[cnt]] = i;
        selected[i] = true;
        dfs(cnt+1);
        
        selected[i] = false;
    }
}

long long solution(string expression) {
    long long answer = 0;
   
    int p = 0;
    int m = 0;
    int g = 0;
    string s = "";
    for(int e = 0; e < expression.size(); e++)
    {
        if(expression[e] >= '0' && expression[e] <= '9') s+= expression[e];
        else
        {
            switch (expression[e]) {
                case '+':
                p++;
                break;case '-':
                m++;
                break;case '*':
                g++;
                break;
                default:
                    break;
            }
            op.push_back(expression[e]);
            num.push_back(atoi(s.c_str()));
            s = "";
        }
    }
    if(p > 0) v.push_back('+');
    if(m > 0) v.push_back('-');
    if(g > 0) v.push_back('*');
    
    dfs(0);
    
    
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    solution("100-200*300-500+20");
    return 0;
}
