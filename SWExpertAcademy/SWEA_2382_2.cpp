/*
 SW Expert Academy
 2382. [모의 SW 역량테스트] 미생물 격리
 
 군집 벡터에서 삭제하는 것이 아니라
 군집 객체에 alive 변수를 두고 죽은 것과 살아있는 군집을 구분해주었더니 맞음
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <cstring>
#define MAP_MAX 51
using namespace std;

struct Crowd
{
    int r, c, micro, dir;
    bool alive;
    Crowd() {}
    Crowd(int _r, int _c, int _micro, int _dir) {
        r = _r; c = _c; micro = _micro; dir = _dir; alive = true;
    }
};

vector<Crowd> crowd;
int r, c, m, d;
int N, M, K, answer = 0;
int dr[5] = {0, -1, 1, 0, 0}; // 상 하 좌 우
int dc[5] = {0, 0, 0, -1, 1};


void input()
{
    crowd.clear();
    answer = 0;
    cin >> N >> M >> K;
    for(int i = 0; i < K; i++)
    {
        cin >> r >> c >> m >> d;
        crowd.push_back(Crowd(r,c,m,d));
    }
}

int reverse_dir(int dir)
{
    switch (dir) {
        case 1:
            return 2;
        case 2:
            return 1;
        case 3:
            return 4;
        case 4:
            return 3;
        default:
            return 0;
    }
}

void check_same()
{
    for(int i = 0; i < crowd.size(); i++)
    {
        if(!crowd[i].alive) continue;
        
        vector<Crowd> tmp;
        
        int r = crowd[i].r;
        int c = crowd[i].c;
        
        for(int j = i+1; j < crowd.size(); j++)
        {
            if(!crowd[j].alive) continue;
            
            if(r == crowd[j].r && c == crowd[j].c)
            {
                crowd[j].alive = false;
                tmp.push_back(crowd[j]);
            }
        }
        
        if(!tmp.empty())
        {
            int max = crowd[i].micro;
            
            for(int p = 0; p < tmp.size(); p++)
            {
                if(tmp[p].micro > max)
                {
                    max = tmp[p].micro;
                    crowd[i].dir = tmp[p].dir;
                }
                crowd[i].micro += tmp[p].micro;
            }
        }
    }
}

void solve()
{
    for(int t=0; t<M; t++)
    {
        for(int i = 0; i < crowd.size(); i++)
        {
            if(!crowd[i].alive) continue;
            int nr = crowd[i].r + dr[crowd[i].dir];
            int nc = crowd[i].c + dc[crowd[i].dir];
            
            if(nr == 0 || nr == N-1 || nc == 0 || nc == N-1)
            {
                crowd[i].dir = reverse_dir(crowd[i].dir);
                crowd[i].micro = crowd[i].micro/2;
                
                if(crowd[i].micro == 0)
                {
                    crowd[i].alive = false;
                    continue;
                }
            }
            crowd[i].r = nr;
            crowd[i].c = nc;
        }
        check_same();
    }
    
    for(int i = 0; i < crowd.size(); i++)
    {
        if(crowd[i].alive)
        answer += crowd[i].micro;
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
