/*
 SW Expert Academy
 2383. [모의 SW 역량테스트] 점심 식사시간
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#include <cstring>
#define MAP_MAX 11
using namespace std;

struct Node {
    int r, c;
    Node() {}
    Node(int _r, int _c): r(_r), c(_c) {}
};

int MAP[MAP_MAX][MAP_MAX];
int N, answer;
vector<Node> man;
vector<pair<int, Node>> stair;
int selected[10];

void input()
{
    man.clear();
    stair.clear();
    memset(selected, 0, sizeof(selected));
    answer = 987654321;
    cin >> N;
    
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == 1) man.push_back(Node(i, j));
            else if (MAP[i][j] > 1) stair.push_back(make_pair(MAP[i][j], Node(i, j)));
        }
    }
}

void print()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cout << MAP[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void start_stair()
{
    priority_queue<int, vector<int>, greater<int>> standby[2]; // 입구와의 거리(도착 시간) 저장
    vector<int> going[2]; // 출발한 시간 저장
    
    for(int i = 0; i < man.size(); i++)
    {
        int index = selected[i];
        int distance = abs(man[i].r - stair[index].second.r) + abs(man[i].c - stair[index].second.c);
        
        standby[index].push(distance);
    }
    
    int time = 1;
    
    while(!(standby[0].empty() && standby[1].empty() && going[0].empty() && going[1].empty()))
    {
        for(int i = 0; i < 2; i++)
        {
            while(going[i].size() < 3 && !standby[i].empty())
            {
                if(standby[i].top()+1 <= time)
                {
                    going[i].push_back(time);
                    standby[i].pop();
                }
                else break;
            }
            
            while(!going[i].empty())
            {
                if((time - going[i].front()) == stair[i].first)
                {
                    going[i].erase(going[i].begin());
                }
                else break;
            }
        }
        time++;
    }
    answer = min(time-1, answer);
}

void select_stair(int index)
{
    start_stair();
    
    if(index == man.size()) return;
    
    for(int i = index; i < man.size(); i++)
    {
        selected[i] = 1;
        select_stair(i + 1);
        selected[i] = 0;
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
        select_stair(0);
//        start_stair();
        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}

/* BOJ
 
 int main(int argc, char** argv)
 {
 input();
 
 cout << answer << endl;
 
 return 0;
 }
 */
