#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
#include <deque>
#include <vector>
#include <stack>
#include <map>
#include <regex>
#include <math.h>
#define MAX 11
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;


struct ground
{
    int r; int c; int d; int line; int corner;
    ground(int rr, int cc, int dd, int ll, int cor)
    {
        r = rr; c = cc; d = dd; line = ll; corner = cor;
    }
};

bool is_corner(int a, int b)
{
    if(a == -1) return false;
    else if(a == 0 || a == 1)
    {
        if(b == 3 || b == 2) return true;
        else return false;
    }
    else
    {
        if(b == 0 || b == 1) return true;
        else return false;
    }
}

bool is_reverse(int a, int b)
{
    if(a == 0 && b == 1) return true;
    else if(a == 1 && b == 0) return true;
    else if(a == 2 && b == 3) return true;
    else if(a == 3 && b == 2) return true;
    return false;
}

int solution(vector<vector<int>> board) {
    int answer = 999999999;
    
    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    int cost[25][25] = {0,};
    
    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board.size(); j++)
        {
            cost[i][j] = 99999999;
        }
    }
    
    queue<ground> q;
    q.push(ground(0,0,-1,0,0));
    cost[0][0] = 0;
    while (!q.empty())
    {
        int r = q.front().r;
        int c = q.front().c;
        int d = q.front().d;
        int l = q.front().line;
        int cor = q.front().corner;
        q.pop();
        // 직선 도로 하나를 만들 때는 100원이 소요되며, 코너를 하나 만들 때는 500원이
        
        if(r == board.size()-1 && c == board.size()-1)
        {
            if(answer > cost[board.size()-1][board.size()-1])
            answer = cost[board.size()-1][board.size()-1];
        }
        for(int i = 0; i < 4; i++)
        {
            if(is_reverse(d, i)) continue;
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr < 0 || nr > board.size()-1 || nc < 0 || nc > board.size()-1 || board[nr][nc] == 1) continue;
            
            int corner = cor;
            if(d != i) corner++;
            int money = corner*500 + (l+1)*100;
            
            if(nr == board.size()-1 && nc == board.size()-1)
            {
                cout << "dd";
            }
            if(cost[nr][nc] >= money)
            {
                cost[nr][nc] = money;
                q.push(ground(nr,nc,i,l+1,corner));
            }
        }
    }
    
        answer = cost[board.size()-1][board.size()-1];
    
    
    
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    //[0, 0, 1, 0], [0, 0, 0, 0], [0, 1, 0, 1], [1, 0, 0, 0]
    solution({{0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 0, 1, 0}, {0, 1, 0, 0, 0, 1, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}});
    return 0;
}
