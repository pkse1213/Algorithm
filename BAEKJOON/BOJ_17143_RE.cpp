/*
 BAEKJOON
 17143. 낚시왕
 
 1시간 10분 소요
 
 처음에 테스트케이스는 맞지만 시간초과가 났다.
 상어의 속력의 범위는 0 ≤ s ≤ 1000이다.
 상어 수가 많아질 수록, 속력 수 만큼 한 칸씩 while문으로 이동한다면 1초 안에 해결할 수 없다.
 
 따라서, 현재 위치(제자리)로 돌아오는 때를 무시하고 그 이후의 거리만 while문으로 이동해야 한다.
 
 이동 방향이 위, 아래일 때는 (R-1)*2만큼 이동할 때마다 제자리로 돌아온다.
 이동 방향이 왼, 오른쪽일 때는 (C-1)*2만큼 이동할 때마다 제자리로 돌아온다.
 
 따라서, 방향에 맞게 속력을 (R-1)*2 or (C-1)*2을 나눈 나머지값 만큼만 이동시켰다.
 그럼 아무리 많이 이동해도 최대 (R-1)*2-1 or (C-1)*2-1 만큼 밖에 이동하지 않기 때문에 시간초과를 해결할 수 있다.
 
 */
#include <iostream>
#include <vector>
#include <cstring>
#define MAX 101
using namespace std;

struct Fish
{
    // s는 속력, d는 이동 방향, z는 크기
    int r, c, s, d, z;
    bool alive = true;
    Fish() {}
    Fish(int rr, int cc, int ss, int dd, int zz)
    {
        r = rr; c = cc; s = ss; d = dd; z = zz;
    }
};

int R, C, M, r, c, s, d, z;
int Answer = 0;
int map[MAX][MAX];
vector<Fish> fish;
int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, 1, -1};

void input()
{
    cin >> R >> C >> M;
    for(int i = 0; i < M; i++)
    {
        cin >> r >> c >> s >> d >> z;
        fish.push_back(Fish(r, c, s, d, z));
    }
}

void print()
{
    for(int i = 1; i <= R; i++)
    {
        for(int j = 1; j <= C; j++)
        {
            if(map[i][j] == -1) cout << '.' << "\t";
            else cout << fish[map[i][j]].z << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void put_fish()
{
    memset(map, -1, sizeof(map));
    
    for(int i = 0; i < fish.size(); i++)
    {
        if(fish[i].alive == false) continue;
        
        if(map[fish[i].r][fish[i].c] > -1)
        {
            int idx = map[fish[i].r][fish[i].c];
            if(fish[i].z > fish[idx].z)
            {
                map[fish[i].r][fish[i].c] = i;
                fish[idx].alive = false;
            }
            else
            {
                fish[i].alive = false;
            }
        }
        else
        {
            map[fish[i].r][fish[i].c] = i;
        }
    }
}

void catch_fish(int t)
{
    for(int i = 1; i <= R; i++)
    {
        if(map[i][t] > -1)
        {
            fish[map[i][t]].alive = false;
            Answer += fish[map[i][t]].z;
            return;
        }
    }
}

int reverse_dir(int d)
{
    if(d == 1) return 2;
    else if(d == 2) return 1;
    else if(d == 3) return 4;
    else if(d == 4) return 3;
}

void move_fish()
{
    for(int i = 0; i < fish.size(); i++)
    {
        if(fish[i].alive == false) continue;
        
        int nr = fish[i].r;
        int nc = fish[i].c;
        int fd = fish[i].d;
        int fs = fish[i].s;
        
        if(fish[i].d == 1 || fish[i].d == 2) // 위, 아래
        {
            fs %= (R-1)*2;
        }
        else if(fish[i].d == 3 || fish[i].d == 4) // 왼, 오
        {
            fs %= (C-1)*2;
        }
        
        while(fs--)
        {
            nr += dr[fd];
            nc += dc[fd];
            
            if(nr < 1 || nr > R || nc < 1 || nc > C)
            {
                fd = reverse_dir(fd);
                fish[i].d = fd;
                nr += dr[fd]*2;
                nc += dc[fd]*2;
            }
        }
        
        fish[i].r = nr;
        fish[i].c = nc;
    }
}

void solve()
{
    for(int t = 1; t <= C; t++)
    {
        put_fish();
        catch_fish(t);
        
        if(t == C)
        {
            cout << Answer << endl;
            return;
        }
        
        move_fish();
    }
}

int main()
{
    input();
    solve();
    
    return 0;
}
