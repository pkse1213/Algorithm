/*
 다시풀기
 14503. 로봇청소기
 
 20분
 
 시뮬레이션
*/

#include <iostream>
#define MAX 51
using namespace std;

int N, M, R, C, D, Cnt;
int MAP[MAX][MAX];
int Dr[4] = {-1, 0 ,1, 0};
int Dc[4] = {0, -1, 0, 1};

void Input()
{
    cin >> N >> M >> R >> C >> D;
    
    R++; C++;
    if(D == 1) D = 3;
    else if(D == 3) D = 1;
    
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cin >> MAP[i][j];
        }
    }
}

int Reverse_Dir(int d)
{
    if(d == 0) return 2;
    else if(d == 1) return 3;
    else if(d == 2) return 0;
    else return 1;
}

void Solve()
{
    while (1)
    {
        // 1. 현재 위치 청소
        if(MAP[R][C] == 0)
        {
            MAP[R][C] = 2; Cnt ++;
        }
       
        // 2.
        bool Find = false;
        for(int i = 1; i <= 4; i++)
        {
            int d = (D + i) % 4;
            int r = R + Dr[d];
            int c = C + Dc[d];
            
            if(r < 1 || r > N || c < 1 || c > M) continue;
            
            if(MAP[r][c] == 0)
            {
                R = r; C = c; D = d;
                Find = true; break;
            }
        }
        
        if(Find == false)
        {
            int d = Reverse_Dir(D);
            int r = R + Dr[d];
            int c = C + Dc[d];
            
            if(r < 1 || r > N || c < 1 || c > M || MAP[r][c] == 1)
            {
                break;
            }
            else
            {
                R = r; C = c;
            }
        }
    }
}

int main()
{
    Input();
    Solve();
    cout << Cnt << endl;
}
