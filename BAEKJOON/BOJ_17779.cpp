/*
 BAEKJOON
 17779. 게리맨더링 2
 
 브루트포스
 
 역량테스트 환경에서는 sort()를 사용할 때,
 #include <algorithm>해줘야 함
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <cstring>
#define MAP_MAX 21
using namespace std;

struct Node {
    int r, c;
    Node() {}
    Node(int _r, int _c): r(_r), c(_c) {}
};
int map[MAP_MAX][MAP_MAX];
int visited[MAP_MAX][MAP_MAX];
int N, M, answer = 987654321;
vector<int> people;
int dr[4] = {-1, 0, 1, 0}; // 북 동 남 서
int dc[4] = {0, 1, 0, -1};
int cnt = 0;
void input()
{
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> map[i][j];
            cnt += map[i][j];
        }
    }
}

void print()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cout << visited[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void initialize()
{
    people.clear();
    for(int i = 1; i <= 5; i++)
    {
        people.push_back(0);
    }
    
    memset(visited, 0, sizeof(visited));
}

bool check(int r, int c, int d1, int d2)
{
    if(r < r + d1 + d2 && r + d1 + d2 <= N && 1 <= c - d1 && c - d1 < c && c < c + d2 && c + d2 <= N)
        return true;
    else
        return false;
}

void border(int r, int c, int d1, int d2)
{
    int x, y;
    for(int i = 0; i <= d1; i++)
    {
        // 1.
        x = r + i;
        y = c - i;
        if(!visited[x][y])
        {
            visited[x][y] = 6;
            people[4] += map[x][y];
        }
        
        // 4.
        x = r + d2 + i;
        y = c + d2 - i;
        if(!visited[x][y])
        {
            visited[x][y] = 6;
            people[4] += map[x][y];
        }
    }
    
    for(int i = 0; i <= d2; i++)
    {
        // 2.
        x = r + i;
        y = c + i;
        if(!visited[x][y])
        {
            visited[x][y] = 6;
            people[4] += map[x][y];
        }
        // 3.
        x = r + d1 + i;
        y = c - d1 + i;
        if(!visited[x][y])
        {
            visited[x][y] = 6;
            people[4] += map[x][y];
        }
    }
}

void rest(int r, int c, int d1, int d2)
{
    for(int i = 1; i <= N; i++)
    {
        bool flag = false;
        for(int j = 1; j <= N; j++)
        {
            if(visited[i][j])
            {
                if(r < i && i < r + d1 + d2)
                    flag = !flag;
                continue;
            }
            
            if(flag)
                people[4] += map[i][j];
            
            else if(1 <= i && i < r + d1 && 1 <= j && j <= c)
                people[0] += map[i][j];
                
            else if(1 <= i && i <= r + d2 && c < j && j <= N)
                people[1] += map[i][j];
        
            else if(r + d1 <= i && i <= N && 1 <= j && j < c - d1 + d2)
                people[2] += map[i][j];
            
            else if(r + d2 < i && i <= N && c - d1 + d2 <= j && j <= N)
                people[3] += map[i][j];
            
            visited[i][j] = true;
        }
    }
}

void calculate()
{
    sort(people.begin(), people.end());
    answer = min(answer, people[4] - people[0]);
}

void solve()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            for(int k = 1; k <= N; k++)
            {
                for(int t = 1; t <= N; t++)
                {
                    if(check(i, j, k, t))
                    {
                        initialize();
                        border(i, j, k, t);
                        rest(i, j, k, t);
                        calculate();
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    input();
    solve();
    cout << answer << endl;
    
    return 0;
}
