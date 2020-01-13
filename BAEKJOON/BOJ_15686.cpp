/*
 BAEKJOON
 15686. 치킨 배달
*/

#include <iostream>
#include <vector>
#include <math.h>
#define MAX 51
using namespace std;
struct node
{
    int r, c;
    node();
    node(int _r, int _c): r(_r), c(_c) {}
};

int map[MAX][MAX];
int n, m, tmp;
vector<node> home;
vector<node> chicken;
vector<bool> check;

int answer = 987654321;

void input()
{
    cin >> n >> m;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            cin >> tmp;
            if(tmp == 1) home.push_back(node(i,j));
            if(tmp == 2)
            {
                chicken.push_back(node(i,j));
                check.push_back(false);
            }
        }
    }
}

void compute()
{
    int sum = 0;
    for(int i=0; i<home.size(); i++)
    {
        int r = home[i].r;
        int c = home[i].c;
        int tmp = 987654321;
        
        for(int j=0; j<chicken.size(); j++)
        {
            if(!check[j]) continue;
            
            int d = abs(r-chicken[j].r) + abs(c-chicken[j].c);
            tmp = min(tmp, d);
        }
        sum += tmp;
    }
    answer = min(answer, sum);
}

void dfs(int cnt, int idx)
{
    if(idx > chicken.size())
        return;
    if(cnt > m)
    {
        compute();
        return;
    }
    check[idx] = true;
    dfs(cnt+1, idx+1);
    
    check[idx] = false;
    dfs(cnt, idx+1);
    
}


int main(int argc, char** argv)
{
    input();
    dfs(1, 0);
    cout << answer;
    return 0;
}
