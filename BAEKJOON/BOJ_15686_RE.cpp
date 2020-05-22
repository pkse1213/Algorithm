/*
 15686. 치킨배달 다시풀기
 
 */
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

int N, M;
int board[50][50];
vector<pii> ch;
vector<pii> h;
bool selected[13];
int chicken_distance = 987654321;

int distance(int r, int c, int rr, int cc)
{
    return abs(r-rr) + abs(c-cc);
}

void calculate()
{
    int sum = 0;
    for(int i = 0; i < h.size(); i++)
    {
        int len = 987654321;
        for(int j = 0; j < ch.size(); j++)
        {
            if(selected[j])
            {
                int dis = distance(h[i].first, h[i].second, ch[j].first, ch[j].second);
                if(dis < len) len = dis;
            }
        }
        sum += len;
    }
    if(chicken_distance > sum)
        chicken_distance = sum;
}

void dfs(int n, int cnt)
{
    if(n > ch.size()) return;
    if(cnt == M)
    {
        calculate();
        return;
    }
    
    selected[n] = true;
    dfs(n+1, cnt+1);
    selected[n] = false;
    dfs(n+1, cnt);
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> board[i][j];
            if(board[i][j] == 1) h.push_back(make_pair(i,j));
            else if(board[i][j] == 2) ch.push_back(make_pair(i,j));
        }
    }
    dfs(0, 0);
    cout << chicken_distance;
   
    return 0;
}
