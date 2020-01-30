/*
 SW Expert Academy
 1949. [모의 SW 역량테스트] 등산로 조성
 
 DFS
 처음에 놓친 부분
 등산로를 깎았을 때는 map[nr][nc]값으로 비교하면 안되고,
 이전 값보다 최소로 깎은 map[r][c]-1과 비교했어야 했다.
 따라서 pre변수를 추가해서 경우를 나누고 현재 등산로 값을 전달했다.
*/

#include <iostream>
#include <vector>
#include <math.h>
#define MAP_MAX 9
using namespace std;

struct Node {
    int r, c;
    Node() {}
    Node(int _r, int _c): r(_r), c(_c) {}
};
int MAP[MAP_MAX][MAP_MAX];
int VISITED[MAP_MAX][MAP_MAX];
int N, K, ANSWER, H_MAX;
vector<Node> highest;

int dr[4] = {-1, 0, 1, 0}; // 북 동 남 서
int dc[4] = {0, 1, 0, -1};

void input()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> MAP[i][j];
            
            if(MAP[i][j] > H_MAX)
            {
                highest.clear();
                highest.push_back(Node(i, j));
                H_MAX = MAP[i][j];
            }
            else if(MAP[i][j] == H_MAX)
            {
                highest.push_back(Node(i, j));
            }
        }
    }
}

void initialize()
{
    highest.clear();
    H_MAX = 0;
    ANSWER = 0;
}

void DFS(int R, int C, int cnt, int pre, bool chance)
{
    VISITED[R][C] = true;
    ANSWER = max(ANSWER, cnt);
    
    for(int i = 0; i < 4; i++)
    {
        int nr = R + dr[i];
        int nc = C + dc[i];
        
        if((nr < 1 || nr > N || nc < 1 || nc > N) || VISITED[nr][nc]) continue;
        
        // 내리막길
        if(MAP[nr][nc] < pre)
        {
            DFS(nr, nc, cnt + 1, MAP[nr][nc], chance);
        }
        
        // 오르막길
        else
        {
            // 기회 유무 + K만큼 깎으면 내리막길 되는지?
            if(chance && pre > (MAP[nr][nc] - K))
            {
                DFS(nr, nc, cnt + 1, pre - 1, false);
            }
        }
    }
    VISITED[R][C] = false;
}

void solve()
{
    for(int i = 0; i < highest.size(); i++)
    {
        DFS(highest[i].r, highest[i].c, 1, MAP[highest[i].r][highest[i].c], true);
    }
}

int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case)
    {
        initialize();
        input();
        solve();
        cout << "#" << test_case << " " << ANSWER << endl;
    }
    return 0;
}
