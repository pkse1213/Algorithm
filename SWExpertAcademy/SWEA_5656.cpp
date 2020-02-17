/*
 5656. [모의 SW 역량테스트] 벽돌 깨기
 
 DFS
 
 BFS로 구현했을 때 시간초과남
 
 void CrushBrick(int r, int c, int s)
 {
     queue<pair<pair<int, int>, int>> Q;
     Q.push({ { r, c }, s });
     Visited[r][c] = true;
     
     while(Q.empty() == false)
     {
         r = Q.front().first.first;
         c = Q.front().first.second;
         s = Q.front().second;
         
         Q.pop();
         
         for(int i = 0; i < 4; i++)
         {
             for(int k = 1; k < s; k++)
             {
                 int nr = r + dr[i] * k;
                 int nc = c + dc[i] * k;
                 
                 if(nr < 0 || nr >= H || nc < 0 || nc >= W || Visited[nr][nc] == true)
                 {
                     continue;
                 }
                 
                 Visited[nr][nc] = true;
                 
                 if(C_MAP[nr][nc] > 0)
                 {
                     if(C_MAP[nr][nc] > 1)
                     {
                         Q.push({ { nr, nc }, C_MAP[nr][nc] });
                     }
                     C_MAP[nr][nc] = 0;
                 }
             }
         }
     }
 }
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define H_MAX 15
#define W_MAX 12
#define N_MAX 4
#define INF 987654321
using namespace std;

int T, H, W, N, Sum, Answer;
int MAP[H_MAX][W_MAX];
int C_MAP[H_MAX][W_MAX];
int Visited[H_MAX][W_MAX];
int Selected[N_MAX];
int dr[4] = {0, 0, 1, -1};
int dc[4] = {1, -1, 0, 0};
bool Already_Blank;

void Initialize()
{
    Already_Blank = true;
    Answer = INF;
    memset(Selected, false, sizeof(Selected));
}

void Input()
{
    cin >> N >> W >> H;
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            cin >> MAP[i][j];
            if(MAP[i][j] > 0)
            {
                Already_Blank = false;
            }
        }
    }
}

void Copy_Map()
{
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            C_MAP[i][j] = MAP[i][j];
        }
    }
}

void DFS(int r, int c)
{
    int s = C_MAP[r][c];
    
    for(int i = 0; i < 4; i++)
    {
        for(int k = 1; k < s; k++)
        {
            int nr = r + dr[i] * k;
            int nc = c + dc[i] * k;
            
            if(nr < 0 || nr >= H || nc < 0 || nc >= W || Visited[nr][nc] == true)
            {
                continue;
            }
            
            Visited[nr][nc] = true;
            
            if(C_MAP[nr][nc] > 0)
            {
                if(C_MAP[nr][nc] > 1)
                {
                    DFS(nr, nc);
                }
                C_MAP[nr][nc] = 0;
            }
        }
    }
}

bool Find_Brick(int c)
{
    for(int r = 0; r < H; r++)
    {
        if(C_MAP[r][c] > 0)
        {
            memset(Visited, false, sizeof(Visited));
            
            Visited[r][c] = true;
            DFS(r, c);
            C_MAP[r][c] = 0;
            
            return true;
        }
    }
    return false;
}

void Remove_Blank()
{
    Already_Blank = true;
    for(int c = 0; c < W; c++)
    {
        vector<int> V;
        for(int r = H-1; r >= 0; r--)
        {
            if(C_MAP[r][c] > 0)
            {
                Already_Blank = false;
                V.push_back(C_MAP[r][c]);
                C_MAP[r][c] = 0;
            }
        }
        for(int i = 0; i < V.size(); i++)
        {
            C_MAP[H - 1 - i][c] = V[i];
        }
    }
}

void Start()
{
    for(int i = 0; i < N; i++)
    {
        if(Find_Brick(Selected[i]) == true)
        {
            Remove_Blank();
        }
        if(Already_Blank == true)
        {
            return;
        }
    }
}

void Calculate()
{
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            if(C_MAP[i][j] > 0)
            {
                Sum++;
            }
        }
    }
    Answer = min(Answer, Sum);
}

void Select_Row(int cnt)
{
    if(cnt == N)
    {
        Sum = 0;
        Copy_Map();
        Start();
        Calculate();
        return;
    }
    
    for(int i = 0; i < W; i++)
    {
        Selected[cnt] = i;
        Select_Row(cnt + 1);
    }
}

int main()
{
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        Initialize();
        Input();
        if(Already_Blank == false)
        {
            Select_Row(0);
        }
        cout << "#" << t << " " << Answer << endl;
    }
    return 0;
}
