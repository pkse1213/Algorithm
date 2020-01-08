/*
 SW Expert Academy
 5658. [모의 SW 역량테스트] 보물상자 비밀번호
 
 처음에 한 변에 있는 원소들의 맨 앞과 맨 뒤를 옮기고 추가하니 queue를 사용하면 된다고 생각했다.
 변의 16진수 값들은 내림차순이어야 하므로 proir_queue를 사용하면 된다고 생각했다.
 
 queue는 index로 접근할 수 없어 탐색할 수 없었다.
 3번째 원소에 접근하려면 pop()하는 수 밖에 없다.
 iterator 자체가 없으므로 begin(), end() 함수도 없다.
 
 데이터를 동적으로 추가하고 index로 원소에 접근할 수 있는 vector로 수정하였다.
 변의 16진수 값들은 sort()를 사용하고 desc()를 선언하여 내림차순으로 정렬하였다.
 
 -> 단지 선입 선출로 데이터를 넣고 빼기만 할 때는 queue가 유용하지만
    탐색을 해야한다면 vector를 쓰자
 
 vector의 맨 앞 원소를 삭제할 때 erase()를 사용하였다.
 erase()는 vector.begin(), vector.end()를 함께 사용하여 특정 원소를 삭제한다.
 -> v.erase(v.begin()+2); // v의 세 번째 원소 삭제
 -> 주의 : vector.front(), vetor.back()은 맨 앞, 맨 뒤의 원소에 접근하는 것!
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <string>
#define MAX 500
using namespace std;

int n, k, res = 0;
string str;
vector<char> locker[4];
vector<int> answer;

void input()
{
    cin >> n >> k;
    cin >> str;
    int idx = 0;
    res = 0;
    answer.clear();
    
    for(int i=0; i<4; i++)
    {
        locker[i].clear();
        for(int j=0; j<n/4; j++)
        {
            locker[i].push_back(str[idx++]);
        }
    }
}

bool desc(int a, int b) { return a > b; }

void rotate()
{
    for(int t=1; t<=n/4; t++)
    {
        for(int i=0; i<4; i++)
        {
            int tmp = 0;
            int q = n/4;
            for(int j=0; j<n/4; j++)
            {
                char c = locker[i][j];
                if('0' <= c && c <= '9')
                    tmp += (c - '0')*pow(16.0, --q);
                else if('A' <= c && c <= 'F')
                    tmp += (c - 'A' + 10)*pow(16.0, --q);
            }
            
            if(answer.empty())
            {
                answer.push_back(tmp);
                continue;
            }

            for(int j=0; j<answer.size(); j++)
            {
                // 같은 값이 있으면 안 넣는다
                if(answer[j] == tmp) break;

                // 마지막 index이면 넣는다
                else if(j==answer.size()-1)
                {
                    answer.push_back(tmp);
                    break;
                }
            }
        }
        // 마지막에는 회전 안시켜줘도 됨
        if(t==n/4) break;
        
        for(int i=0; i<4; i++)
        {
            char tmp = locker[i].back();
            int ni = i;
            
            if(i==3)
                ni = 0;
            else
                ni += 1;
            
            locker[ni].insert(locker[ni].begin(), tmp);
            locker[i].erase(locker[i].end()-1);
        }
    }
    sort(answer.begin(), answer.end(), desc);
    res = answer[k-1];
    
}


int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case)
    {
        input();
        rotate();
        cout << "#" << test_case << " " << res << endl;
    }
    return 0;
}
