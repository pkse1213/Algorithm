/*
 1021. 회전하는 큐
 
 deque에 대해 알게 됐다.
 deque는 stack와 queue가 결합된 자료구조
 
 <주요 멤버들>
 vector에 없는 pop_front와 push_front가 있다는 것 빼고는 vector의 기능과 같음
 
 pop_back    마지막 원소를 삭제
 pop_front    첫 번째 원소를 삭제
 push_back    마지막에 원소를 추가
 push_front    제일 앞에 원소 추가
 
 <deque와 vector를 비교할 때 고려해야 하는 점>
 deque는 앞과 뒤에서 삽입과 삭제 성능이 vector보다 더 좋다.
 deque는 앞과 뒤 삽입, 삭제를 제외한 기능은 vector보다 성능이 좋지 못하다.
 
 */
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <deque>
#define MAX 50
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;

int N, M, Tmp, Answer = 0;
deque<int> DQ;
queue<int> Q;

void Input()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
    {
        DQ.push_back(i);
    }
    for(int i = 0; i < M; i++)
    {
        cin >> Tmp;
        Q.push(Tmp);
    }
}

void First(int Idx)
{
    for(int i = 0; i < Idx; i++)
    {
        int F = DQ.front();
        DQ.pop_front();
        DQ.push_back(F);
        Answer++;
    }
    DQ.pop_front();
}

void Second(int Idx)
{
    for(int i = 0; i < Idx; i++)
    {
        int B = DQ.back();
        DQ.pop_back();
        DQ.push_front(B);
        Answer++;
    }
    DQ.pop_front();
}

void Solve()
{
    for(int i = 0; i < M; i++)
    {
        int Target = Q.front();
        Q.pop();
        
        for(int j = 0; j < DQ.size(); j++)
        {
            if(DQ[j] == Target)
            {
                int Size = DQ.size() - j;
                if(j < Size)
                {
                    First(j);
                }
                else
                {
                    Second(Size);
                }
                break;
            }
        }
    }
}

int main()
{
    Input();
    Solve();
    cout << Answer << endl;
    return 0;
}
