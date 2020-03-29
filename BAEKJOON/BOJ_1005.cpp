/*
 1005. ACM Craft
 위상 정렬
 
 [풀이]
 X -> Y
 X의 후행자 Y 추가, Y의 선행자++
 
 Result[] = 선행자들이 끝나는데 걸리는 시간 (해당 건물이 시작할 수 있는 시간)
 
 1. 시작점 찾기
 시작점 -> 선행자의 수 = 0
 하나를 찾았다고 해서 break;했더니 런타임 에러가 발생했다.
 선행자가 없는 여러개 일 수 있는데, while(W의 선행자가0일 때까지) 돌기 때문에 무한루프가 발생한다.
 
 2. 시작점들을 큐에 넣는다.
 
 while(W의 선행자가0일 때까지)
 3. 큐의 front를 pop한다. -> cur이라고 가정
 
 4. cur의 후행자에 대해 Result값을 갱신시켜준다.(더 클 경우에만)
 cur 건물의 시작 시간 + cur 건물을 짓는데 걸리는 시간
 
 3. 후행자의 선행자 수--
 만약, 그 후행자의 선행자 수가 0인 경우 큐에 넣고 3번 부터 계속 반복한다.
 
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#define MAX 1001
using namespace std;

int T, N, K, D, X, Y, W;
vector<int> Suc[MAX];
int Pre[MAX];
int Time[MAX];
int Result[MAX];
int Answer;

void Initialize()
{
    memset(Pre, 0, sizeof(Pre));
    memset(Result, 0, sizeof(Result));
}

void Clear()
{
    for(int i = 1; i <= N; i++)
    {
        Suc[i].clear();
    }
}

void Input()
{
    cin >> N >> K;
    
    for(int i = 1; i <= N; i++)
    {
        cin >> Time[i];
    }
    for(int i = 0; i < K; i++)
    {
        cin >> X >> Y;
        Suc[X].push_back(Y);
        Pre[Y]++;
    }
    cin >> W;
}


void Solve()
{
    queue<int> Q;
    
    for(int i = 1; i <= N; i++)
    {
        if(Pre[i] == 0)
        {
            Q.push(i); // break;을 지움
        }
    }
    
    while (Pre[W] > 0) {
        int Num = Q.front();
        Q.pop();
        
        for(int Next: Suc[Num])
        {
            Result[Next] = max(Result[Next], Result[Num] + Time[Num]);
            
            if(--Pre[Next] == 0)
            {
                Q.push(Next);
            }
        }
    }
    
    Answer = Result[W] + Time[W];
}

int main()
{
    cin >> T;
    for(int i = 0; i < T; i++)
    {
        if(i != 0) Clear();
        Initialize();
        Input();
        Solve();
        cout << Answer << endl;
    }
}
