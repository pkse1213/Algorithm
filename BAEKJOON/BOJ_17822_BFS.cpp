/*
 BAEKJOON
 17822. 원판 돌리기
 
 1시간 7분 소요
 
 인접한 수 찾는 방법 2가지
 1. 완전탐색
 완전탐색으로 해당 좌표 상,하,좌,우에 같은 값이 있는 지 체크하고,
 같기 때문에 삭제할 좌표를 벡터에 저장하고 한 번에 삭제해 주었다.
 이 때 분명히 겹치는 좌표가 있었을 것이다.
 찾자마자 삭제하지 못한 이유는 현재 좌표(r, c)와 인접한 좌표(r+1, c)가 같은 값이라서 값을 삭제하면,
 (r+1, c)와 (r+2, c)가 같은 값이어도 체크할 수 없다.
 따라서 벡터에 모두 저장한 후, 한번에 삭제하였다.
 
 2. 찾자마자 삭제하지 못하는 문제를 BFS로 해결
 해당 좌표에서 인접한 같은 값을 BFS 탐색으로 모두 체크 + 방문 체크하고 삭제해준다.
 
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 51
using namespace std;
struct Rotate
{
    int x, d, k;
    Rotate() {}
    Rotate(int xx, int dd, int kk)
    {
        x = xx; d = dd; k = kk;
    }
};
struct Node
{
    int r, c;
    Node() {}
    Node(int rr ,int cc)
    {
        r = rr; c = cc;
    }
};

int N, M, T, X, D, K, answer;
int map[MAX][MAX];
int visited[MAX][MAX] = { false };
int dr[4] = {0 , 0, 1, -1};
int dc[4] = {1 , -1, 0, 0};
vector<Rotate> v;
queue<Node> q;
void input()
{
    cin >> N >> M >> T;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cin >> map[i][j];
        }
    }
    
    for(int i = 0; i < T; i++)
    {
        cin >> X >> D >> K;
        v.push_back(Rotate(X, D, K));
    }
}

void rotate_circle(int circle, int k, int d)
{
    // 번호가 xi의 배수인 원판을 di방향으로 ki칸 회전시킨다.
    // di가 0인 경우는 시계 방향, 1인 경우는 반시계 방향이다.
    for(int i = 0; i < k; i++)
    {
        if(d == 0)
        {
            int last = map[circle][M];
            for(int j = M; j >= 2; j--)
            {
                map[circle][j] = map[circle][j-1];
            }
            map[circle][1] = last;
        }
        else if(d == 1)
        {
            int first = map[circle][1];
            for(int j = 1; j <= M-1; j++)
            {
                map[circle][j] = map[circle][j+1];
            }
            map[circle][M] = first;
        }
    }
}

/*
 인접하면서 수가 같은 것을 모두 찾는다.
 그러한 수가 있는 경우에는 원판에서 인접하면서 같은 수를 모두 지운다.
 
 <인접 조건>
 (i, 1)은 (i, 2), (i, M)과 인접하다.
 (i, M)은 (i, M-1), (i, 1)과 인접하다.
 (i, j)는 (i, j-1), (i, j+1)과 인접하다. (2 ≤ j ≤ M-1)
 (1, j)는 (2, j)와 인접하다.
 (N, j)는 (N-1, j)와 인접하다.
 (i, j)는 (i-1, j), (i+1, j)와 인접하다. (2 ≤ i ≤ N-1)
 
 => 상, 하, 좌, 우 체크. But, 1번 째 원판은 2번째 원판만, 마지막 원판은 N-1원판만 인접
*/
bool BFS(int r, int c)
{
    bool flag = false;
    int num = map[r][c];
    q.push(Node(r, c));
    
    while(!q.empty())
    {
        int rr = q.front().r;
        int cc = q.front().c;
        q.pop();
        
        for(int i = 0; i < 4; i++)
        {
            int nr = rr + dr[i];
            int nc = cc + dc[i];
            
            if(nr == M+1 || nr == 0) continue;
            
            if(nc == 0) nc = M;
            else if(nc == M+1) nc = 1;
            
            if(visited[nr][nc] == false && map[nr][nc] == num)
            {
                q.push(Node(nr, nc));
                visited[nr][nc] = true;
                map[nr][nc] = 987654321;
                flag = true;
            }
        }
    }
    if(flag)
    {
        visited[r][c] = true;
        map[r][c] = 987654321;
    }
    return flag;
}

bool check_adjoin()
{
    bool flag = false;
    
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(map[i][j] == 987654321) continue;
            
            if(BFS(i, j)) flag = true;
        }
    }
    return flag;
}

pair<int, int> calculate()
{
    pair<int, int> result;
    result.first = 0;
    result.second = 0;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(map[i][j] == 987654321) continue;
            
            result.first += map[i][j]; result.second++;
        }
    }
    return result;
}

// 인접한 수가 하나도 없는 경우에는 원판에 적힌 수의 평균을 구하고, 평균보다 큰 수에서 1을 빼고, 작은 수에는 1을 더한다.
void calculate_by_avg(double avg)
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(map[i][j] == 987654321) continue;
            
            if(map[i][j] > avg)
                map[i][j]--;
            else if(map[i][j] < avg)
                map[i][j]++;
        }
    }
}

void print()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(map[i][j] == 987654321) cout << "X ";
            else cout << map[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void solution()
{
    for(int t = 0; t < T; t++)
    {
        // 번호가 xi의 배수인 원판을 di방향으로 ki칸 회전시킨다. di가 0인 경우는 시계 방향, 1인 경우는 반시계 방향이다.
        int x = v[t].x; // 배수
        int k = v[t].k; // 칸수
        int d = v[t].d; //
        
        for(int i = x; i <= N; i += x)
        {
            rotate_circle(i, k, d);
        }
//        print();
        bool check = check_adjoin();
        if(check == false)
        {
            pair<int, int> result = calculate();
            double avg = (double)result.first / (double)result.second;
            calculate_by_avg(avg);
        }
//        print();
//        cout << "########################" << endl;
    }
    answer = calculate().first;
}

void solve()
{
    solution();
    cout << answer << endl;
}

int main()
{
    input();
    solve();
    return 0;
    
}
