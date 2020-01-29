/*
 SW Expert Academy
 1953. [모의 SW 역량테스트] 탈주범 검거
 
 조건을 따줘주며 BFS
 */

#include <iostream>
#include <vector>
#include <queue>
#define MAP_MAX 50
using namespace std;

struct Node {
    int r, c;
    Node() {}
    Node(int _r, int _c): r(_r), c(_c) {}
};
int MAP[MAP_MAX][MAP_MAX];
bool visited[MAP_MAX][MAP_MAX];
int TIME[MAP_MAX][MAP_MAX];
vector<int> side;
queue<Node> position;

int N, M, R, C, L, answer;
int dr[4] = {-1, 1, 0, 0}; // 상 하 좌 우
int dc[4] = {0, 0, -1, 1};

void input()
{
    cin >> N >> M >> R >> C >> L;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
            visited[i][j] = false;
            TIME[i][j] = 0;
        }
    }
}

void initialize()
{
    answer = 0;
    side.clear();
    while(!position.empty()) position.pop();
}

void transferable(int dir)
{
    side.clear();
    
    switch (dir) {
        case 1:
            for(int i = 0; i < 4; i++)
                side.push_back(i);
            break;
        case 2:
            side.push_back(0);
            side.push_back(1);
            break;
        case 3:
            side.push_back(2);
            side.push_back(3);
            break;
        case 4:
            side.push_back(0);
            side.push_back(3);
            break;
        case 5:
            side.push_back(1);
            side.push_back(3);
            break;
        case 6:
            side.push_back(1);
            side.push_back(2);
            break;
        case 7:
            side.push_back(0);
            side.push_back(2);
            break;
        default:
            break;
    }
}

int reverse_direction(int dir)
{
    switch (dir) {
        case 0:
            return 1;
            break;
        case 1:
            return 0;
            break;
        case 2:
            return 3;
            break;
        case 3:
            return 2;
            break;
        default:
            return -1;
            break;
    }
}

bool check(int dir, int next)
{
    switch (dir) {
        case 0:
            if(next == 1 || next == 2 || next == 5 || next == 6) return true;
            else return false;
            break;
        case 1:
            if(next == 1 || next == 2 || next == 4 || next == 7) return true;
            else return false;
            break;
        case 2:
            if(next == 1 || next == 3 || next == 4 || next == 5) return true;
            else return false;
            break;
        case 3:
            if(next == 1 || next == 3 || next == 6 || next == 7) return true;
            else return false;
            break;
        default:
            return false;
            break;
    }
}

void BFS()
{
    position.push(Node(R, C));
    visited[R][C] = true;
    TIME[R][C] = 1;
    
    while (!position.empty()) {
        int r = position.front().r;
        int c = position.front().c;
        
        if(TIME[r][c] > L) return;
        
        position.pop(); answer++;
        
        transferable(MAP[r][c]);
        
        for(int i = 0; i < side.size(); i++)
        {
            int nr = r + dr[side[i]];
            int nc = c + dc[side[i]];
            
            if(nr < 0 || nr > N-1 || nc < 0 || nc > M-1) continue;
            if(visited[nr][nc] || MAP[nr][nc] == 0) continue;

            if(check(side[i], MAP[nr][nc]))
            {
                position.push(Node(nr, nc));
                visited[nr][nc] = true;
                TIME[nr][nc] = TIME[r][c] + 1;
            }
        }
    }
}

int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case)
    {
        input();
        initialize();
        BFS();
        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}
