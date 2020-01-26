/*
 SW Expert Academy
 2115. [모의 SW 역량테스트] 벌꿀채취
 
 */

#include <iostream>
#include <vector>
#include <math.h>
#define MAP_MAX 11
using namespace std;

int MAP[MAP_MAX][MAP_MAX];
int Select[MAP_MAX][MAP_MAX];
int N, M, C;
vector<pair<int, bool>> honey[2];
int max_benefit[2];
int answer;

void input()
{
    max_benefit[0] = 0;
    max_benefit[1] = 0;
    answer = 0;
    cin >> N >> M >> C;
    
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> MAP[i][j];
            Select[i][j] = false;
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


bool check(int r, int c)
{
    bool flag = true;
    for(int i = 1; i < M; i++)
    {
        if(Select[r][c+i])
        {
            flag = false;
            break;
        }
    }
    return flag;
}


void calculate(int c)
{
    int sum = 0;
    for(int i = 0; i < honey[c].size(); i++)
    {
        if(honey[c][i].second) sum += honey[c][i].first * honey[c][i].first;
    }
    
    max_benefit[c] = max(max_benefit[c], sum);
}

void DFS_select_honey(int c, int idx, int sum)
{
    if(idx == honey[c].size())
    {
        calculate(c);
        return;
    }
    
    for(int i = idx; i < honey[c].size(); i++)
    {
        if(sum + honey[c][i].first <= C)
        {
            honey[c][i].second = true;
            DFS_select_honey(c, i + 1, sum + honey[c][i].first);
        }
        else
        {
            calculate(c);
            return;
        }
        
        honey[c][i].second = false;
    }
}

void DFS_select_tong(int idx, int cnt)
{
    if(cnt == 2)
    {
        max_benefit[0] = 0;
        max_benefit[1] = 0;
        
        for(int i = 0; i < 2; i++)
        {
            DFS_select_honey(i, 0, 0);
        }
        answer = max(answer, max_benefit[0] + max_benefit[1]);
        return;
    }
    
    for(int i = idx; i <= N; i++)
    {
        for(int j = 1; j <= (N - M + 1); j++)
        {
            if(!Select[i][j])
            {
                if(check(i, j))
                {
                    for(int c = 0; c < M; c++)
                    {
                        Select[i][j+c] = true;
                        honey[cnt].push_back(make_pair(MAP[i][j+c], false));
                    }
                    
                    DFS_select_tong(i, cnt+1);
                    
                    // 백트레킹
                    for(int c = 0; c < M; c++)
                    {
                        Select[i][j+c] = false;
                    }
                    honey[cnt].clear();
                }
            }
        }
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
        DFS_select_tong(1, 0);
        cout << "#" << test_case << " " << answer << endl;
    }
    
    return 0;
}
