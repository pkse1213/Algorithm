/*
 1949. 등산로 조정 다시풀기
 
 처음에 꼭대기를 찾기 위해 top 리스트를 queue로 구현했었는데,
 각 테스트 케이스 마다 없애줄 때 한 번에 clear할 수 없다는 것을 깜빡했었다.
 그래서 vector로 다시 바꿔주었는데, 이 부분을 까먹지 말도록 유의하자!
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
int T, N, K, answer = 0;
int mountain[8][8];
bool visited[8][8];
vector<pair<int, pii>> top;
int dr[4] = {0,0,-1,1};
int dc[4] = {-1,1,0,0};

void dfs(int cnt, int h, pii pos, bool used)
{
    if(cnt > answer) answer = cnt;
    
    for(int i = 0; i < 4; i++)
    {
        int nr = pos.first + dr[i];
        int nc = pos.second + dc[i];
        if(nr < 0 || nr > N-1 || nc < 0 || nc > N-1 || visited[nr][nc]) continue;
        
        visited[nr][nc] = true;
        if(mountain[nr][nc] < h)
        {
            dfs(cnt + 1, mountain[nr][nc], make_pair(nr, nc), used);
        }
        else if(used == false && mountain[nr][nc] - K < h)
        {
            dfs(cnt + 1, h - 1, make_pair(nr, nc), true);
        }
        visited[nr][nc] = false;
    }
}

bool comp(pair<int, pii> a, pair<int, pii> b)
{
    return a.first > b.first;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> T;
    for(int t=1; t<=T; t++)
    {
        top.clear();
        answer = 0;
        cin >> N >> K;
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                cin >> mountain[i][j];
                top.push_back(make_pair(mountain[i][j], make_pair(i, j)));
            }
        }
        sort(top.begin(), top.end(), comp);
        int h = 0;
        for(int i = 0; i < top.size(); i++)
        {
            if(top[i].first >= h)
            {
                h = top[i].first;
                memset(visited, false, sizeof(visited));
                visited[top[i].second.first][top[i].second.second] = true;
                dfs(1, top[i].first, top[i].second, false);
                
            }
            else break;
        }
        
        printf("#%d %d\n", t, answer);
    }
    
    return 0;
}
