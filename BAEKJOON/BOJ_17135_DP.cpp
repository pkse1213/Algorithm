/*
 BAEKJOON
 17135. 캐슬 디펜스
 
 2. DFS (궁수 선택) + DP (적 선택)

 적의 위치를 모두 벡터에 미리 저장해두고 각 궁수와의 거리를 모두 체크했다.
 D 이내 거리의 적들은 kill_enemy_temp 벡터에 저장한 후 sort하였다.
 적들이 한 칸씩 내려올 때마다 적의 위치를 다시 찾아야해서 1번 방법보다 훨씬 오래걸린다.
 
 **놓쳤던 부분**

 궁수가 N+1 행에만 위치한다는 말인데, N+1에도 존재할 수 있다고 이해했다.
 문제가 짧지만, 문제를 잘 읽읍시다..^^

 **주의할 부분**

 **같은 적이 여러 궁수에게 공격당할 수 있다.**
 각 궁수가 적을 찾았을 때, 바로 죽이면 안된다. 죽일 수 있는 적을 찾으면 먼저 kill_enemy 배열에 적 위치를 저장해 두었다.
 그리고 모든 궁수가 적을 찾은 후에 아래와 같이 한 명씩 죽이되, 이미 죽였던 적은 카운팅하지 않아야 한다.
 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 16
using namespace std;

int N, M, D, Answer = 0;
vector<pair<int, int>> goongsu; // 선택된 궁수
vector<pair<int, int>> enemy; // 존재하는 적
pair<int, int> kill_enemy[3]; // 죽일 선택된 적
int map[MAX][MAX];
int c_map[MAX][MAX];
int sr = 0;

void input()
{
    bool find = false;
    cin >> N >> M >> D;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cin >> map[i][j];
            if(map[i][j] == 1 && find == false)
            {
                sr = i; find = true;
            }
        }
    }
}

int distance(int r, int c, int rr, int cc)
{
    return abs(r - rr) + abs(c - cc);
}

void copy_map()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            c_map[i][j] = map[i][j];
        }
    }
}

void find_enemy()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(c_map[i][j] == 1)
            {
                enemy.push_back(make_pair(i, j));
            }
        }
    }
}

bool standard(pair<int, pair<int, int>> e1, pair<int, pair<int, int>> e2)
{
    if(e1.first == e2.first)
    {
        return e1.second.second < e2.second.second;
    }
    else
    {
        return e1.first < e2.first;
    }
}

int catch_enemy()
{
    int kill = 0;
    
    for(int g = 0; g < goongsu.size(); g++)
    {
        vector<pair<int, pair<int, int>>> kill_enemy_temp;
        
        for(int i = 0; i < enemy.size(); i++)
        {
            int dist = distance(goongsu[g].first, goongsu[g].second, enemy[i].first, enemy[i].second);
            if(dist <= D)
            {
                kill_enemy_temp.push_back(make_pair(dist, enemy[i]));
            }
        }
        
        if(kill_enemy_temp.size() == 1)
        {
            kill_enemy[g] = kill_enemy_temp.front().second;
        }
        else if(kill_enemy_temp.size() > 1)
        {
            sort(kill_enemy_temp.begin(), kill_enemy_temp.end(), standard);
            kill_enemy[g] = kill_enemy_temp.front().second;
        }
        else
        {
            kill_enemy[g] = make_pair(-1, -1);
        }
    }
    
    for(int i = 0; i < goongsu.size(); i++)
    {
        if(kill_enemy[i].first == -1 && kill_enemy[i].second == -1) continue;
        
        if(c_map[kill_enemy[i].first][kill_enemy[i].second] == 1)
        {
            c_map[kill_enemy[i].first][kill_enemy[i].second] = 0;
            kill += 1;
        }
    }
    
    return kill;
}

void move_enemy()
{
    for(int i = N; i >= 1; i--)
    {
        for(int j = 1; j <= M; j++)
        {
            c_map[i][j] = c_map[i-1][j];
        }
    }
}

void start_game()
{
    int sum = 0;
    copy_map();
    
    for(int t = 1; t <= N - sr + 1; t++)
    {
        enemy.clear();
        find_enemy();
        sum += catch_enemy();
        if(t == N - sr + 1)
        {
            Answer = max(Answer, sum);
            return;
        }
        move_enemy();
    }
}

void DFS(int cnt, int c)
{
    if(cnt == 3)
    {
        start_game();
        return;
    }
    
    if(c == M+1)
    {
        return;
    }
    
    goongsu.push_back(make_pair(N+1, c));
    DFS(cnt + 1, c + 1);
    
    goongsu.pop_back();
    DFS(cnt, c + 1);
}

void solve()
{
    DFS(0, 1);
    cout << Answer;
}

int main()
{
    input();
    solve();
    return 0;
}
