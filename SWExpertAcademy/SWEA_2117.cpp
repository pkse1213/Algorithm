/*
 SW Expert Academy
 2117. [모의 SW 역량테스트] 홈 방범 서비스
 
 */

#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
#define MAP_MAX 21
using namespace std;

struct Node {
    int r, c;
    Node() {}
    Node(int _r, int _c): r(_r), c(_c) {}
};
int MAP[MAP_MAX][MAP_MAX];
int N, M, answer, house;

int dr[4] = {-1, 0, 1, 0}; // 북 동 남 서
int dc[4] = {0, 1, 0, -1};

void input()
{
    answer = 0;
    house = 0;
    
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <=N; j++)
        {
            cin >> MAP[i][j];
            if(MAP[i][j]) house++;
        }
    }
}

int distance(int x, int xx, int y, int yy)
{
    return abs(x - xx) + abs(y - yy);
}

int operate(int k, int r, int c)
{
    int cnt = 0;
    
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(distance(r, i, c, j) < k && MAP[i][j] == 1) cnt++;
        }
    }
    return cnt;
}

int operating_cost(int K, int h)
{
    return h * M - (K * K + (K - 1) * (K - 1));
}

void solve()
{
    for(int K = 1; K <= sqrt(N*N*2); K++)
    {
        for(int i = 1; i <= N; i++)
        {
            for(int j = 1; j <= N; j++)
            {
                int h = operate(K, i, j);
                
                if(operating_cost(K, h) >= 0)
                {
                    answer = max(answer, h);
                    if(h == house) return;
                }
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
        solve();
        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}
