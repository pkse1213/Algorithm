/*
 BAEKJOON
 16637. 괄호 추가하기 1
 
 처음에 놓친 부분)
 1. * ,-, + 연산자들의 우선순위는 없고 왼쪽부터 계산해주기만 하면 된다.
 2. 괄호 안에 연산자가 1개만 들어갈 수 있다. (맨 밑 구현 참고)
 
 DFS로 괄호 추가 했을 때와, 안 했을 때 탐색
 1. 괄호 추가 안 했을 때
 4 * 2 - 5 - 7 + 9
        \현재 연산자
 result - 다음 숫자(5)
 idx는 + 2 해줘야 함
 
 2. 괄호 추가 했을 때
 4 * 2 - ( 5 - 7 ) + 9
       \현재 연산자
 5-7을 다음 숫자라고 생각
 result - 다음 숫자(5 - 7)
 idx는 + 4 해줘야 함
 */

#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <math.h>
using namespace std;

int N;
string str;
int answer;

void initialize()
{
    answer = -212992478;
}

void input()
{
    cin >> N >> str;
}

int calculate(int a, char op, int b)
{
    if(op == '-')
    {
        return a-b;
    }
    else if(op == '+')
    {
        return a+b;
    }
    else
    {
        return a*b;
    }
}

int convert(char c)
{
    return c -'0';
}

// idx => 연산자의 index이기 때문ㅇ 1부터 +2씩 해줌
// result => 현재 idx 이전까지의 계산 결과
void dfs(int idx, int result)
{
    if(idx >= str.length())
    {
        answer = max(answer, result);
        return;
    }
    
    // 괄호가 아예 없다고 쳤을 때
    int tmp1 = calculate(result, str[idx], convert(str[idx+1]));
    dfs(idx + 2, tmp1);
    
    if(idx + 3 < str.length())
    {
        int next = calculate(convert(str[idx+1]), str[idx+2], convert(str[idx+3]));
        int tmp2 = calculate(result, str[idx], next);
        dfs(idx + 4, tmp2);
    }
}

int main(int argc, char** argv)
{
    initialize();
    input();
    dfs(1, str[0]-'0');
    cout << answer << endl;
    
    return 0;
}

/*
 괄호 안에 연산자가 1개만 들어갈 수 있는 지 모르고 구현한 dfs
 (입력)
 9
 3+8*7-9*2
 
 (결과)
 ( 3 + 8 ) * ( 7 - 9 ) * 2
 ( 3 + 8 ) * ( 7 - 9 * 2 )
 ( 3 + 8 ) * 7 - ( 9 * 2 )
 ( 3 + 8 ) * 7 - 9 * 2
 ( 3 + 8 * 7 ) - ( 9 * 2 )
 ( 3 + 8 * 7 ) - 9 * 2
 ( 3 + 8 * 7 - 9 ) * 2
 ( 3 + 8 * 7 - 9 * 2 )
 3 + ( 8 * 7 ) - ( 9 * 2 )
 3 + ( 8 * 7 ) - 9 * 2
 3 + ( 8 * 7 - 9 ) * 2
 3 + ( 8 * 7 - 9 * 2 )
 3 + 8 * ( 7 - 9 ) * 2
 3 + 8 * ( 7 - 9 * 2 )
 3 + 8 * 7 - ( 9 * 2 )
 3 + 8 * 7 - 9 * 2
 
void print(vector<char> v)
{
    for(int i = 0 ; i < v.size(); i++)
    {
        cout << v[i] << ' ';
    }
    cout << endl;
}


void dfs(vector<char> v, int idx, bool flag)
{
    if(idx == str.length())
    {
        if(flag)
        {
            print(v);
        }
        return;
    }
    
    char c = str[idx];
    
    // 연산자
    if(c == '+' || c == '-' || c == '*')
    {
        v.push_back(c);
        dfs(v, idx + 1, flag);
    }
    
    // 숫자
    else
    {
        if(flag)
        {
            v.push_back('(');
            v.push_back(c);
            dfs(v, idx + 1, !flag);
            
            v.pop_back();
            v.pop_back();
            v.push_back(c);
            dfs(v, idx + 1, flag);
            
        }
        else
        {   v.push_back(c);
            v.push_back(')');
            dfs(v, idx + 1, !flag);
            
            v.pop_back();
            dfs(v, idx + 1, flag);
        }
    }
}
*/
