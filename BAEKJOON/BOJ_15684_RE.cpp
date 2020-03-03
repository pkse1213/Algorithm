/*
다시풀기
15684. 사다리 조작

1시간 20분

DFS + 시뮬레이션

방법 1(처음 풀었을 때)
   DFS 안에서 탐색해서 가로선을 추가 할 수 있는 점을 찾고 재귀 -> 시간 단축
방법 2(다시 풀 때)
   다음 칸으로 넘어가며 DFS이기 때문에 시간이 더 걸림
*/
#include <iostream>
#define N_MAX 11
#define H_MAX 31
using namespace std;

int N, L, M, a, b;
bool Find = false;
pair<bool, bool> MAP[H_MAX][N_MAX];
pair<bool, bool> C_MAP[H_MAX][N_MAX];

void Input()
{
    cin >> M >> L >> N;

    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            MAP[i][j] = { false, false };
        }
    }
    
    for(int i = 0; i < L; i++)
    {
        cin >> a >> b;
        MAP[a][b].second = true;
        MAP[a][b + 1].first = true;
    }
}

void Copy_Map()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            C_MAP[i][j] = MAP[i][j];
        }
    }
}

bool Check()
{
    for(int i = 1; i <= M; i++)
    {
        int c = i;
        for(int r = 1; r <= N; r++)
        {
            if(C_MAP[r][c].first == true) c--;
            else if(C_MAP[r][c].second == true) c++;
        }
        if(c != i) return false;
    }
    return true;
}

void DFS(int R, int C, int Cnt, int Total)
{
    if(Find == true) return;
        
    if(Cnt == Total)
    {
        if(Check() == true)
        {
            Find = true;
        }
        return;
    }
    
    if(C > M - 1)
    {
        if(R == N)
        {
            return;
        }
        else
        {
            R++; C = 1;
        }
    }
    
    if(C_MAP[R][C].second == false && C_MAP[R][C + 1].second == false)
    {
        C_MAP[R][C].second = true;
        C_MAP[R][C + 1].first = true;
        
        DFS(R, C + 2, Cnt + 1, Total);
        if(Find == true) return;
        
        C_MAP[R][C].second = false;
        C_MAP[R][C + 1].first = false;
        
        DFS(R, C + 1, Cnt, Total);
    }
    
    else if(C_MAP[R][C].second == true)
    {
        DFS(R, C + 2, Cnt, Total);
    }
    
    else if(C_MAP[R][C + 1].second == true)
    {
        DFS(R, C + 3, Cnt, Total);
    }
}

int Solve()
{
    for(int Total = 0; Total <= 3; Total++)
    {
        Copy_Map();
        DFS(1, 1, 0, Total);
        if(Find == true) return Total;
    }
    return -1;
}

int main()
{
    Input();
    cout << Solve() << endl;
    return 0;
}
