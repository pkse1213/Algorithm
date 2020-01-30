/*
 BAEKJOON
 SW Expert Academy
 
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#include <cstring>
#define MAP_MAX 51
using namespace std;

struct Node {
    int r, c;
    Node() {}
    Node(int _r, int _c): r(_r), c(_c) {}
};
int map[MAP_MAX][MAP_MAX];
int N, M, answer;
int dr[4] = {-1, 0, 1, 0}; // 북 동 남 서
int dc[4] = {0, 1, 0, -1};

void initialize()
{
    answer = 0;
}

void input()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cin >> map[i][j];
        }
    }
}

void print()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cout << map[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void solve()
{
    
}

/* SWEA
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
        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}
 */


/* BOJ
int main(int argc, char** argv)
{
    initialize();
    input();
    solve();
    cout << answer << endl;
    
    return 0;
}
*/
