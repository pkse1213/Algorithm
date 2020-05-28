/*
 16235. 나무재태크
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int N, M, K, x, y, z, answer = 0;
vector<int> tree[10][10];
int add[10][10];
int A[10][10];

int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

void input()
{
    cin >> N >> M >> K;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            cin >> add[i][j];
            A[i][j] = 5;
        }
    
    for(int i = 0; i < M; i++)
    {
        cin >> x >> y >> z;
        tree[x-1][y-1].push_back(z);
    }
}


void spring_summer()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(tree[i][j].empty()) continue;
            
            sort(tree[i][j].begin(), tree[i][j].end());
            
            for(int n = 0; n < tree[i][j].size(); n++)
            {
                
                // 죽음
                if(A[i][j] < tree[i][j][n])
                {
                    for(int k = (int)tree[i][j].size()-1; k >= n; k--)
                    {
                        A[i][j] += tree[i][j][n]/2;
                        tree[i][j].pop_back();
                    }
                    break;
                }
                // 나무에 양분 추가
                
                else
                {
                    A[i][j] -= tree[i][j][n];
                    tree[i][j][n] += 1;
                }
            }
        }
    }
}

void fall_winter()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            A[i][j] += add[i][j];
            
            if(tree[i][j].empty()) continue;
            
            for(int n = 0; n < tree[i][j].size(); n++)
            {
                if(tree[i][j][n] % 5 != 0) continue;
                
                for(int d = 0; d < 8; d++)
                {
                    int nr = i + dr[d];
                    int nc = j + dc[d];
                    if(nr < 0 || nr > N-1 || nc < 0 || nc > N-1) continue;
                    tree[nr][nc].push_back(1);
                }
            }
            
        }
    }
}

void calculate()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            answer += tree[i][j].size();
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    input();
    
    
    for(int t = 0; t < K; t++)
    {
        spring_summer();
        fall_winter();
    }
    
    calculate();
    
    
    cout << answer << endl;
    return 0;
}
