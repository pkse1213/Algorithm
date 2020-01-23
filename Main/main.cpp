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
int MAP[MAP_MAX][MAP_MAX];
int N, M, answer = 0;
int dr[4] = {-1, 0, 1, 0}; // 북 동 남 서
int dc[4] = {0, 1, 0, -1};

void input()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cin >> MAP[i][j];
        }
    }
}

void print()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cout << MAP[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}


int main(int argc, char** argv)
{
    input();
    
    cout << answer << endl;
    
    return 0;
}
