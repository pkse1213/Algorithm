/*
 BAEKJOON
 17471. 게리맨더링
 
 처음 생각)
 DFS나 BFS로 연결되어 있는 애들을 하나씩 증가시키면서 체크하려고 함
 -> 불가능^^
 
 선거구에서 1~ N/2개를 뽑는 조합을 구현한 후,
 (N/2개인 이유 -> 6개 중에 2개를 뽑는 것과 4개를 뽑는 것은 같은 의미)
 선택된 선거구끼리, 선택되지 않은 선거구끼리 선이 연결되어 있는지 확인한 후 연결되어 있으면 계산해줌
 
 연결된 선의 정보는 map배열에 저장
 */

#include <iostream>
#include <queue>
#include <math.h>
#include <cstring>
#define GU_MAX 11
using namespace std;

int gu[GU_MAX];
bool selected[GU_MAX] = { false };
bool map[GU_MAX][GU_MAX] = { false };
int visited[GU_MAX];
int N, M, K, answer = 987654321;

void input()
{
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        cin >> gu[i];
    }
    
    for(int i = 1; i <= N; i++)
    {
        cin >> M;
        for(int j = 1; j <= M; j++)
        {
            cin >> K;
            map[i][K] = true;
            map[K][i] = true;
        }
    }
}

void print()
{
    for(int i = 1; i <= N; i++)
    {
        cout << selected[i] << "\t";
    }
    cout << endl;
}

void calculate()
{
    int a = 0;
    int b = 0;
    
    for(int i = 1; i <= N; i++)
    {
        if(selected[i])
        {
            a += gu[i];
        }
        else
        {
            b += gu[i];
        }
    }
    answer = min(answer, abs(a-b));
}

bool check(int limit, bool flag)
{
    memset(visited, 0, sizeof(visited));
    int count = 0;
    queue<int> q;
    
    for(int i = 1; i <= N; i++)
    {
        if(selected[i] == flag)
        {
            q.push(i);
            visited[i] = true;
            break;
        }
    }
    
    while(!q.empty())
    {
        int idx = q.front();
        q.pop(); count++;
        
        for(int i = 1; i <= N; i++)
        {
            if(map[idx][i] && !visited[i] && selected[i] == flag)
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    
    if(limit == count)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void dfs(int limit, int idx, int cnt)
{
    if(cnt == limit)
    {
        if(check(limit, true) && check(N-limit, false))
            calculate();
       
        return;
    }
    
    if(idx == N+1) return;
    
    for(int i = idx; i <= N; i++)
    {
        selected[i] = true;
        dfs(limit, i + 1, cnt + 1);
        selected[i] = false;
        
    }
    /* 위와 같은 결과
    selected[idx] = true;
    solve(limit, idx + 1, cnt + 1);

    selected[idx] = false;
    solve(limit, idx + 1, cnt);
     */
}

int main(int argc, char** argv)
{
    input();
    int limit;
    if(N % 2 > 0) limit = (N / 2) + 1;
    else limit = N / 2;
    
    for(int i = 1; i <= limit; i++)
    {
        dfs(i, 1, 0);
    }
    if(answer == 987654321) answer = -1;
    cout << answer << endl;
    
    return 0;
}
