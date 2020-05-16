/*
 2383. [모의 SW 역량테스트] 점심 식사시간
 
 해당시간에 도착한 사람을 먼저 빼주고, 시작하는 사람을 넣어줘야 했다..
 이 부분때문에 시간 많이 날렸다ㅠㅠ
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;

struct stair_info
{
    int r, c, t;
    stair_info(int rr, int cc, int tt)
    {
        r = rr; c = cc; t = tt;
    }
};

int T, N, board[11][11], answer = 987654321;
vector<pii> people;
vector<stair_info> stair;
priority_queue<int, vector<int>, greater<int>> arrived[2];
queue<int> downing[2];
int selected[10];

int down_stair()
{
    for(int i = 0; i < people.size(); i++)
    {
        int s = selected[i];
        arrived[s].push(abs(stair[s].r - people[i].first) + abs(stair[s].c - people[i].second) + 1);
    }

    int cnt = 0;
    int time = 0;
    int on_stair[2] = {0,0};
    
    while (cnt < people.size())
    {
        time++;
        
        for(int i = 0; i < 2; i++)
        {
            while(!downing[i].empty() && downing[i].front() == time)
            {
                downing[i].pop();
                on_stair[i]--; cnt++;
            }
            
            while(on_stair[i] < 3 && !arrived[i].empty() && arrived[i].top() <= time)
            {
                downing[i].push(time + stair[i].t);
                arrived[i].pop();
                on_stair[i]++;
            }
        }
    }
    return time;
}


void choose(int n)
{
    if(n == people.size())
    {
        int time = down_stair();
        if(time < answer) answer = time;
        return;
    }
    
    for(int i = 0; i < stair.size(); i++)
    {
        selected[n] = i;
        choose(n + 1);
    }
}

int main()
{
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        answer = 987654321;
        stair.clear();
        people.clear();
        cin >> N;
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                cin >> board[i][j];
                if(board[i][j] == 1) people.push_back(make_pair(i, j));
                else if(board[i][j] > 1) stair.push_back(stair_info(i, j, board[i][j]));
            }
        }
        
        choose(0);
        printf("#%d %d\n", t, answer);
    }
    return 0;
}
