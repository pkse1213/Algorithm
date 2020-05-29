/*
 16236. 아기 상어 다시풀기의 다시풀기
 30분
 bfs로 거리를 한칸 씩 늘려가면서 체크하려면,
 int size = (int)q.size();
 for(int m = 0; m < size; m++)
 이런 식으로 1칸씩 이동된 현재 q의 데이터까지만 체크하는 방식으로 해야한다.
 
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#define MAX 11
using namespace std;
typedef pair<int, int> pii;

struct shark_info
{
    int r, c, size = 2, fish = 0;
};

shark_info shark;
int N;
int board[20][20];
bool visited[20][20];
int dr[4] = {0,0,-1,1};
int dc[4] = {1,-1,0,0};

bool comp(pii a, pii b)
{
    if(a.first == b.first) return a.second < b.second;
    else return a.first < b.first;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> board[i][j];
            if(board[i][j] == 9)
            {
                shark.r = i; shark.c = j;
                board[i][j] = 0;
            }
        }
    }
    
    bool eat = true;
    int answer = 0;
    
    while (eat)
    {
        memset(visited, false, sizeof(visited));
        int time = answer;
        queue<pii> q;
        vector<pii> v; // 잡은 물고기
        q.push(make_pair(shark.r, shark.c));
        visited[shark.r][shark.c] = true;
        
        eat = false;
        while (!q.empty())
        {
            time++;
            int size = (int)q.size();
            for(int m = 0; m < size; m++)
            {
                int r = q.front().first;
                int c = q.front().second;
                q.pop();
                
                for(int i = 0; i < 4; i++)
                {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    
                    if(nr < 0 || nr > N-1 || nc < 0 || nc > N-1 ||
                       visited[nr][nc] || board[nr][nc] > shark.size) continue;
                    
                    visited[nr][nc] = true;
                    
                    if(0 < board[nr][nc] && board[nr][nc] < shark.size)
                        v.push_back(make_pair(nr, nc));
                    else
                        q.push(make_pair(nr, nc));
                }
            }
            
            if(v.size() > 0)
            {
                sort(v.begin(), v.end(), comp);
                board[v[0].first][v[0].second] = 0;
                shark.fish++;
                shark.r = v[0].first;
                shark.c = v[0].second;
                if(shark.fish == shark.size)
                {
                    shark.fish = 0;
                    shark.size++;
                }
                answer = time;
                eat = true;
                break;
            }
        }
    }
    printf("%d\n", answer);
    return 0;
}
