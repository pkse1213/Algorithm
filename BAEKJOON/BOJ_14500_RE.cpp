/*
 다시풀기
 
 14500. 테트로미노
 2:30~
 
 1) 처음 생각 -> 모양별로 다 for문 돌려서 완전탐색해봐야 한다고 생각.
    겁나 오래걸림. 바보 하하 -> 답이 나오긴 한다고 함
    회전이 가능한걸 생각 못함
 
 2) DFS
    - 4가지 모양은 depth=3 으로 dfs탐색 하면 다 나옴 (그림 참고:https://yabmoons.tistory.com/35)
    - ㅜ 모양은 depth=3으로는 나오지 못함 -> 따로 해줘야 함
 */

#include <iostream>
#include <vector>
#include <cstring>
#define MAX 500
using namespace std;

int N, M, Max;
int MAP[MAX][MAX];
bool Visited[MAX][MAX];
vector<pair<int, int>> Selected;
int Dr[4] = {-1, 1, 0, 0};
int Dc[4] = {0, 0, -1, 1};

void Initialize()
{
    Max = 0;
    memset(Visited, false, sizeof(Visited));
}

void Input()
{
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
        }
    }
}

int Calculate()
{
    int Sum = 0;
    
    for(int i = 0; i < Selected.size(); i++)
    {
        Sum += MAP[Selected[i].first][Selected[i].second];
    }
    return Sum;
}

void DFS(int R, int C, int Cnt)
{
    Selected.push_back({R, C});
    
    if(Cnt == 4)
    {
        Max = max(Max, Calculate());
        return;
    }
    
    for(int i = 0; i < 4; i++)
    {
        int Nr = R + Dr[i];
        int Nc = C + Dc[i];
        
        if(Nr < 0 || Nr > N - 1 || Nc < 0 || Nc > M - 1 || Visited[Nr][Nc] == true)
        {
            continue;
        }
        
        Visited[R][C] = true;
        DFS(Nr, Nc, Cnt + 1);
        
        Selected.pop_back();
        Visited[Nr][Nc] = false;
    }
}

void Rest_Shape()
{
    // ㅗ, ㅜ
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M - 2; j++)
        {
            Selected.clear();
            
            for(int m = 0; m < 3; m++)
            {
                Selected.push_back({i, j + m});
            }
            
            if(i - 1 >= 0)
            {
                Selected.push_back({i - 1, j + 1});
                Max = max(Max, Calculate());
                Selected.pop_back();
            }
            if(i + 1 < N)
            {
                Selected.push_back({i + 1, j + 1});
                Max = max(Max, Calculate());
            }
        }
    }
    
    // ㅏ , ㅓ
    for(int j = 0; j < M; j++)
    {
        for(int i = 0; i < N - 2; i++)
        {
            Selected.clear();
            
            for(int m = 0; m < 3; m++)
            {
                Selected.push_back({i + m, j});
            }
            
            if(j - 1 >= 0)
            {
                Selected.push_back({i + 1, j - 1});
                Max = max(Max, Calculate());
                Selected.pop_back();
            }
            if(j + 1 < M)
            {
                Selected.push_back({i + 1, j + 1});
                Max = max(Max, Calculate());
            }
        }
    }
}

void Solution()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            Selected.clear();
            Visited[i][j] = true;
            DFS(i, j, 1);
            Visited[i][j] = false;
        }
    }
}

void Solve()
{
    Solution();
    Rest_Shape();
}

int main()
{
    Initialize();
    Input();
    Solve();
    
    cout << Max << endl;
    return 0;
}
