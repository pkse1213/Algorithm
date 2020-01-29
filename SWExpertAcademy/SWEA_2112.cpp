/*
 SW Expert Academy
 2112. [모의 SW 역량테스트] 보호 필름
 
 DFS
 
 약품처리할 막을 결정했을 때, MAP값을 변경하지 않았다.
 (다른 풀이들 찾아보니깐 다들 변경했길래!? 그럼 계속 초기화해줘야 하잖아!?)
 selected 배열과 type 배열로
 선택된 유무, 선택됐을 시 어떤 타입으로 약처리를 할 것인지 저장.
 필름 체크할 때, selected 배열로 선택된 row인지 확인하고,
 선택되었으면 어떤 타입인지 확인하고 map값 대신 그 타입으로 처리했다!
 
 <시간초과가 나와서 해결한 부분>
 1.
 갯수 제한을 두고 선택해서 작은 갯수부터 탐색
 -> DFS에 매개 변수(limit)로 선택할 갯수를 받고, for문을 돌려 DFS를 돌림
 
 2.
 finish변수를 전역변수로 두고, 작은 수부터 그만큼씩 선택하기 때문에
 발견하면 바로
 finish = true
 로 바꾸고
 if(finish) return;
 조건 확인하여 DFS 바로 종료
 
 3.
 그래도 시간초과가 나서,
 필름을 체크할 때
 if(count < K) check = false;
 로 통과되지 않는 칼럼이 있어도 계속 탐색했던 부분을 찾아내고
 if(count == K) break;
 로 더이상 체크하지 않고 바로 함수 종료시킴
 
 4.
 만약 DFS안에 for문을 돌려서 선택할 거면,
 if(selected[i]) continue;를 잊지말자!!!
 안그럼 같은 거 반복 오지게 함 ㅎ
 */

#include <iostream>
#include <vector>
#include <cstring>
#define D_MAX 14
#define W_MAX 21
using namespace std;

int MAP[D_MAX][W_MAX];
int N, M, K, answer = 0;
bool finish;
bool selected[D_MAX];
int type[D_MAX];
int cnt = 0;

void input()
{
    finish = false;
    cin >> N >> M >> K;
    answer = N + 1;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cin >> MAP[i][j];
        }
    }
}

bool solve()
{
    bool check = true;
    for(int c = 1; c <= M; c++)
    {
        int now, before = -1;
        int count = 1;
        
        for(int r = 1; r <= N; r++)
        {
            if(selected[r])
                now = type[r];
            else
                now = MAP[r][c];
            
            if(now == before)
            {
                count++;
                if(count == K) break;
            }
            else count = 1;
            
            before = now;
        }
        if(count < K) return false;
    }
    return check;
}

void dfs(int limit, int idx, int cnt)
{
    if(cnt == limit)
    {
        if(solve())
        {
            answer = cnt;
            finish = true;
        }
        return;
    }
    
    if(idx > N) return;
    
    selected[idx] = true;
    // A
    type[idx] = 0;
    dfs(limit, idx + 1, cnt + 1);
    if(finish) return;
    
    // B
    type[idx] = 1;
    dfs(limit, idx + 1, cnt + 1);
    if(finish) return;
    
    // 선택 안함
    selected[idx] = false;
    dfs(limit, idx + 1, cnt);
}

int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case)
    {
        input();
        
        for(int i = 0; i <= K; i++)
        {
            memset(selected, false, sizeof(bool)*D_MAX);
            dfs(i, 1, 0);
            if(finish) break;
        }
        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}
