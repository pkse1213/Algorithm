/*
 2382. [모의 SW 역량테스트] 미생물 격리
 
 */

#include <iostream>
#include <vector>
#define MAX 101
using namespace std;

struct association
{
    int r, c, bug, dir;
    bool alive = true;
};

int t, n, m, k;
vector<association> v;
int dr[5] = {0,-1,1,0,0};
int dc[5] = {0,0,0,-1,1};

int reverse_dir(int d)
{
    if(d == 1) return 2;
    else if(d == 2) return 1;
    else if(d == 3) return 4;
    else if(d == 4) return 3;
    return 0;
}

void move()
{
    for(int i = 0; i < v.size(); i++)
    {
        // 이미 사라졌으면 x
        if(v[i].alive == false) continue;
        
        // 이동할 곳
        int nr = v[i].r + dr[v[i].dir];
        int nc = v[i].c + dc[v[i].dir];
        
        // 약품 처리
        if(nr == 0 || nr == n-1 || nc == 0 || nc == n-1)
        {
            // 반으로
            v[i].bug /= 2;
            if(v[i].bug == 0) // 0이면 없앰
            {
                v[i].alive = false;
                continue;
            }
            v[i].dir = reverse_dir(v[i].dir);
        }
        v[i].r = nr;
        v[i].c = nc;
    }
    
    for(int i = 0; i < v.size()-1; i++)
    {
        if(v[i].alive == false) continue;
        
        int bug = v[i].bug;
        for(int j = i+1; j < v.size(); j++)
        {
            if(v[j].alive == false) continue;
            
            if(v[j].r == v[i].r && v[j].c == v[i].c)
            {
                v[i].bug += v[j].bug;
                if(v[j].bug > bug)
                {
                    v[i].dir = v[j].dir;
                    bug = v[j].bug;
                }
                v[j].alive = false;
            }
        }
    }
    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   //셀의 개수 N, 격리 시간 M, 미생물 군집의 개수 K
    cin >> t;
    for(int i = 0; i < t; i++)
    {
        v.clear();
        cin >> n >> m >> k;
        
        for(int j = 0; j < k; j++)
        {
            association tmp;
            cin >> tmp.r >> tmp.c >> tmp.bug >> tmp.dir;
            v.push_back(tmp);
        }
        
        while(m--)
        {
            move();
        }
        
        int sum = 0;
        for(int j = 0; j < v.size(); j++)
        {
            if(v[j].alive) sum += v[j].bug;
        }
        cout << "#" << i+1 << ' ' << sum << '\n';
    }
    
    return 0;
}
