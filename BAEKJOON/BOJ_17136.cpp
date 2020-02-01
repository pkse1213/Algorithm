/*
 BAEKJOON
 17136. 색종이 붙이기
 DFS + 브루트포스
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#define MAP_MAX 10
using namespace std;

struct Node {
    int r, c;
    Node() {}
    Node(int _r, int _c): r(_r), c(_c) {}
};
int map[MAP_MAX][MAP_MAX];
int paper[6] = {0};
int answer;
int dr[3] = {1, 0, 1};
int dc[3] = {0, 1, 1};
vector<Node> one;

void initialize()
{
    answer = 987654321;
}

void input()
{
    for(int i = 0; i < MAP_MAX; i++)
    {
        for(int j = 0; j < MAP_MAX; j++)
        {
            cin >> map[i][j];
            if(map[i][j]) one.push_back(Node(i, j));
        }
    }
}

void dfs(int idx, int cnt)
{
    if(idx == one.size())
    {
        answer = min(answer, cnt);
        return;
    }
    
    int r = one[idx].r;
    int c = one[idx].c;
    
    if(map[r][c] == 0) dfs(idx + 1, cnt);
    

    for(int k = 1; k <= 5; k++)
    {
        if(r + k > MAP_MAX || c + k > MAP_MAX)
            break;
        
        // 이 때에도 break하면 안 되는 이유 -> 이 사이즈의 종이는 없지만 다음 크기의 사이즈 종이는 있을 수 있으므로!
        if(paper[k] == 5) continue;
        
        bool flag = true;
        
        for(int n = 0; n < k; n++)
        {
            for(int m = 0; m < k; m++)
            {
                if(map[r + n][c + m] == 0)
                {
                    flag = false;
                    break;
                }
            }
            if(!flag) break;
        }
        
        if(flag)
        {
            for(int n = 0; n < k; n++)
            {
                for(int m = 0; m < k; m++)
                {
                    map[r + n][c + m] = 0;
                }
            }
            paper[k]++;
            
            dfs(idx + 1, cnt + 1);
            
            for(int n = 0; n < k; n++)
            {
                for(int m = 0; m < k; m++)
                {
                    map[r + n][c + m] = 1;
                }
            }
            paper[k]--;
        }
        else
        {
            break;
        }
    }
    
}

int main(int argc, char** argv)
{
    initialize();
    input();
    dfs(0, 0);
    
    if(answer == 987654321) answer = -1;
    cout << answer << endl;
    
    return 0;
}
