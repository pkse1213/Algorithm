/*
 다시풀기
 15683. 감시

 브루트포스
 
 방법 1. 각 CCTV가 감시를 시작할 방향을 먼저 선택(DFS)한 후 실행한다.
 방법 2. 방향을 선택하면서, 그 방향을 체크(DFS)한다. -> MAP 복사 필요
 
 주의. 다른 CCTV는 통과해서 감시할 수 있음
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 9
using namespace std;

/*
 check_num - 체크해야 하는 횟수
           2번의 경우 -> (상,하) (좌,우) 2번만 해주면 됨
           5번의 경우 -> (상,하,좌,우) 2번만 해주면 됨
           나머지 -> (상을 시작으로), (하를 시작으로), (좌를 시작으로), (우를 시작으로) 4번

 dir_num - 한 번 감사할 때 체크하는 방향의 갯수
            1번의 경우 -> 1개
            2,3번의 경우 -> 2개
            4번 -> 3개
            5번 -> 4개
 
 term - 90도 회전인지(나머지), 180도 회전인지(2번)
*/
struct CCTV_Info
{
    int r, c, check_num, dir_num, term;
};

int N, M, Cnt, Min = MAX*MAX;
int MAP[MAX][MAX];
int Dr[4] = {-1, 0, 1, 0}; // 상부터 시계방향
int Dc[4] = {0, 1, 0, -1};
vector<CCTV_Info> CCTV;

void Make_CCTV(int r, int c, int type)
{
    CCTV_Info cctv;
    cctv.r = r;
    cctv.c = c;
    
    if(type == 2)
    {
        cctv.term = 2;
        cctv.check_num = 2;
        cctv.dir_num = 2;
    }
    else if(type == 5)
    {
        cctv.term = 1;
        cctv.check_num = 1;
        cctv.dir_num = 4;
    }
    else
    {
        cctv.term = 1;
        cctv.check_num = 4;
        
        if(type == 1)
        {
            cctv.dir_num = 1;
        }
        else
        {
            cctv.dir_num = type - 1;
        }
    }
        
    CCTV.push_back(cctv);
}

void Input()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cin >> MAP[i][j];
            
            if(1 <= MAP[i][j] && MAP[i][j] <= 5)
            {
                Make_CCTV(i, j, MAP[i][j]);
            }
        }
    }
}

void Copy_Map(int C_MAP[MAX][MAX], int Temp[MAX][MAX])
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            C_MAP[i][j] = Temp[i][j];
        }
    }
}

void Calculate(int Temp[MAX][MAX])
{
    Cnt = 0;
    
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(Temp[i][j] == 0)
            {
                Cnt++;
            }
        }
    }
    Min = min(Min, Cnt);
}

void DFS(int Temp[MAX][MAX], int idx, int cnt)
{
    if(cnt == CCTV.size())
    {
        Calculate(Temp);
        return;
    }
    
    int C_MAP[MAX][MAX];
    
    CCTV_Info cctv = CCTV[idx];
    for(int start = 0; start < cctv.check_num; start++)
    {
        Copy_Map(C_MAP, Temp);
        for(int i = 0; i < cctv.dir_num; i++)
        {
            int dir = (start + i*cctv.term) % 4;
            int r = cctv.r;
            int c = cctv.c;
            
            while (1) {
                r += Dr[dir];
                c += Dc[dir];
                
                if(r < 1 || r > N || c < 1 || c > M || C_MAP[r][c] == 6)
                {
                    break;
                }
                    
                if(C_MAP[r][c] == 0)
                {
                    C_MAP[r][c] = -1;
                }
            }
        }
        
        DFS(C_MAP, idx + 1, cnt + 1);
    }
}

int main()
{
    Input();
    DFS(MAP, 0, 0);
    cout << Min << endl;
    return 0;
}
