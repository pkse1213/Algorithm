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
int dr[4] = {0 , 0, 1, -1};
int dc[4] = {1 , -1, 0, 0};
vector<Rotate> v;
vector<Node> rm;

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
 없는 경우에는 원판에 적힌 수의 평균을 구하고, 평균보다 큰 수에서 1을 빼고, 작은 수에는 1을 더한다.
 */
 
void adjoin(int r, int c)
{
    bool flag = false;
    for(int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        if(nr == 0 || nr == N+1) continue;
        
        if(nc == 0) nc = M;
        else if(nc == M+1) nc = 1;
        
        if(map[r][c] == map[nr][nc])
        {
            flag = true;
            rm.push_back(Node(nr, nc));
        }
    }
    if(flag) rm.push_back(Node(r, c));
}

double average()
{
    double sum = 0;
    double num = 0;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(map[i][j] == 987654321) continue;
            
            sum += map[i][j]; num++;
        }
    }
    
    return sum/num;
}

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

int calculate_rest()
{
    int sum = 0;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(map[i][j] == 987654321) continue;
            
            sum += map[i][j];
        }
    }
    return sum;
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
        int x = v[t].x;
        int k = v[t].k;
        int d = v[t].d;
        
        // 번호가 xi의 배수인 원판을 di방향으로 ki칸 회전시킨다. di가 0인 경우는 시계 방향, 1인 경우는 반시계 방향이다.

        for(int i = x; i <= N; i += x)
        {
            rotate_circle(i, k, d);
        }
        
//        print();
        
        for(int i = 1; i <= N; i++)
        {
            for(int j = 1; j <= M; j++)
            {
                if(map[i][j] == 987654321) continue;
                adjoin(i, j);
            }
        }
        
        if(rm.size() > 0)
        {
            for(int i = 0; i < rm.size(); i++)
            {
                map[rm[i].r][rm[i].c] = 987654321;
            }
            rm.clear();
        }
        else
        {
            double avg = average();
            calculate_by_avg(avg);
        }
        
//        print();
        
//        cout << "###########################" << endl;
    }
    
    answer = calculate_rest();
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
