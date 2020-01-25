/*
 SW Expert Academy
 2382. [모의 SW 역량테스트] 미생물 격리
 
 군집이 사라질 경우를 vector.erase로 했더니 테스트 케이스가 50개중 49개만 맞는다. 이유는 잘 모르겠다 ㅠㅠ
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
    Crowd() {}
    Crowd(int _r, int _c, int _micro, int _dir) {
        r = _r; c = _c; micro = _micro; dir = _dir;
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
        vector<Crowd> tmp;
        
        int r = crowd[i].r;
        int c = crowd[i].c;
        
        for(int j = i+1; j < crowd.size(); j++)
        {
            if(r == crowd[j].r && c == crowd[j].c)
            {
                tmp.push_back(crowd[j]);
                crowd.erase(crowd.begin()+j);
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
            int nr = crowd[i].r + dr[crowd[i].dir];
            int nc = crowd[i].c + dc[crowd[i].dir];
            
            if(nr == 0 || nr == N-1 || nc == 0 || nc == N-1)
            {
                crowd[i].dir = reverse_dir(crowd[i].dir);
                crowd[i].micro = crowd[i].micro/2;
                
                if(crowd[i].micro == 0)
                {
                    crowd.erase(crowd.begin()+i);
                    i--; continue;
                }
            }
            crowd[i].r = nr;
            crowd[i].c = nc;
        }
        check_same();
    }
    
    for(int i = 0; i < crowd.size(); i++)
    {
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
