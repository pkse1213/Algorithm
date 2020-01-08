/*
 SW Expert Academy
 5644. [모의 SW 역량테스트] 무선 충전
 
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <math.h>
#define MAX 11
using namespace std;

struct node
{
    int r, c;
    node();
    node(int _r, int _c): r(_r), c(_c) {}
};

struct battery
{
    node position;
    int carge, power;
    battery();
    battery(node ps, int c, int p): position(ps), carge(c), power(p) {}
};

int dr[5] = {0, -1, 0, 1, 0}; // 북 동 남 서
int dc[5] = {0, 0, 1, 0, -1};
int n, a, m, x, y, c, p;
vector<int> map[11][11];
vector<battery> bc;
queue<node> one;
queue<node> two;

int answer = 0;

void input()
{
    cin >> n >> a;
    one.push(node(1, 1));
    two.push(node(10,10));
    
    for(int i=0; i<n; i++)
    {
        cin >> m;
        int nr = one.back().r + dr[m];
        int nc = one.back().c + dc[m];
        one.push(node(nr, nc));
    }
    
    for(int i=0; i<n; i++)
    {
        cin >> m;
        int nr = two.back().r + dr[m];
        int nc = two.back().c + dc[m];
        two.push(node(nr, nc));
    }
    
    bc.clear();
    for(int i=0; i<a; i++)
    {
        cin >> x >> y >> c >> p;
        bc.push_back(battery(node(y, x), c, p));
    }
}

void draw()
{
    for(int i=1; i<11; i++)
    {
        for(int j=1; j<11; j++)
        {
            cout << map[i][j].size() << ' ' ;
        }
        cout << endl;
    }
}

/* 처음 생각했던 것 -> 이건 나중에 map 초기화를 해줘야 해서 더 오래걸리고 조건이 복잡함
void init_battery()
{
    for(int s=0; s<bc.size(); s++)
    {
        int carge = bc[s].carge;
        int r = bc[s].position.r;
        int c = bc[s].position.c;
        
        map[r][c].push_back(s);
        
        for(int i=0; i<=carge; i++)
        {
            if(i!=0)
            {
                map[r][c-i].push_back(s);
                map[r][c+i].push_back(s);
            }
            
            for(int j=1; j<=carge-i; j++)
            {
                if(1<=r-j && r-j<=10 && 1<=c-i && c-i<=10) map[r-j][c-i].push_back(s);
                if(1<=r+j && r+j<=10 && 1<=c-i && c-i<=10) map[r+j][c-i].push_back(s);
                
                if(i==0) continue;
                
                if(1<=r-j && r-j<=10 && 1<=c+i && c+i<=10) map[r-j][c+i].push_back(s);
                if(1<=r+j && r+j<=10 && 1<=c+i && c+i<=10) map[r+j][c+i].push_back(s);
            }
        }
    }
}
*/

void init_battery()
{
    for(int i=1; i<=10; i++)
    {
        for(int j=1; j<=10; j++)
        {
            // map 초기화를 안해줘도 되는 이유
            map[i][j].clear();
            
            for(int k=0; k<bc.size(); k++)
            {
                battery b = bc[k];
                if(abs(b.position.r-i)+abs(b.position.c-j) <= b.carge)
                    map[i][j].push_back(k);
            }
        }
    }
}

void compute()
{
    while (!one.empty() && !two.empty()) {
        node p1 = one.front();
        node p2 = two.front();
        
        // 1) 둘다 X
        if(map[p1.r][p1.c].size() == 0 && map[p2.r][p2.c].size() == 0)
        {
            
        }
            
        // 2) 둘다 현재 위치에 배터리가 하나 이상씩 있을 때 + 둘이 같은 좌표
        else if(map[p1.r][p1.c].size() > 0 && map[p2.r][p2.c].size() > 0)
        {
            int tmp = 0;
            for(int i=0; i<map[p1.r][p1.c].size(); i++)
            {
                int idx1 = map[p1.r][p1.c][i];
                for(int j=0; j<map[p2.r][p2.c].size(); j++)
                {
                    int idx2 = map[p2.r][p2.c][j];
                    
                    if(idx1 == idx2) tmp = max(tmp, bc[idx1].power);
                    else tmp = max(tmp, bc[idx1].power+bc[idx2].power);
                }
            }
            answer += tmp;
        }
        
        // 3) 둘중 하나
        else if(map[p1.r][p1.c].size() > 0)
        {
            // 1번 사람 체크
            int tmp = 0;
            for(int i=0; i<map[p1.r][p1.c].size(); i++)
            {
                int idx = map[p1.r][p1.c][i];
                tmp = max(tmp, bc[idx].power);
            }
            answer += tmp;
        }
        
        else if(map[p2.r][p2.c].size() > 0)
        {
            // 2번 사람 체크
            int tmp = 0;
            
            for(int i=0; i<map[p2.r][p2.c].size(); i++)
            {
                int idx = map[p2.r][p2.c][i];
                tmp = max(tmp, bc[idx].power);
            }
            answer += tmp;
        }
        
        one.pop();
        two.pop();
    }
}


int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case)
    {
        answer = 0;
        input();
        init_battery();
        //draw();
        compute();

        cout << "#" << test_case << " " << answer << endl;

    }
    return 0;
}
