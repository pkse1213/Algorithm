/*
 SW Expert Academy
 5653. [모의 SW 역량테스트] 줄기세포배양
 
 시뮬레이션
 
 주의할 점
 [조건] 줄기 세포의 크기에 비해 배양 용기의 크기가 매우 크기 때문에 시뮬레이션에서 배양 용기의 크기는 무한하다고 가정한다.
 범위를 최악의 조건을 생각해서 정한 후 값을 입력받음
 
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#define MAX 350
using namespace std;

struct Cell
{
    int r, c, x, hour = 0;
    bool alive = true;
    bool able = false;
};

int T, N, M, K, Answer;
vector<Cell> Cells;
int MAP[MAX][MAX];
int dr[4] = { 0, 0, -1, 1 };
int dc[4] = { 1, -1, 0, 0 };

void Initialize()
{
    Answer = 0;
    Cells.clear();
    memset(MAP, -1, sizeof(MAP));
}

void Input()
{
    cin >> N >> M >> K;
    for(int i = 151; i < N + 151; i++)
    {
        for(int j = 151; j < M + 151; j++)
        {
            int x;
            cin >> x;
            
            if(x > 0)
            {
                Cell c;
                c.r = i; c.c = j; c.x = x;
                MAP[i][j] = (int)Cells.size();
                Cells.push_back(c);
            }
        }
    }
}

void Print()
{
    cout << endl << "############################################################" << endl;
    for(int r = 0; r < MAX; r++)
    {
        for(int c = 0; c < MAX; c++)
        {
            if(MAP[r][c] == -1) cout << '.';
            else cout << MAP[r][c];
        }
        cout << endl;
    }
}

void ChangeState(int idx)
{
    Cells[idx].hour++;
    
    // 비활성화인데
    if(Cells[idx].able == false)
    {
        // 활성화 됨
        if(Cells[idx].hour == Cells[idx].x)
        {
            Cells[idx].able = true;
            Cells[idx].hour = 0;
        }
    }
    
    // 활성화인데
    else if(Cells[idx].able == true)
    {
        // 죽음
        if(Cells[idx].hour == Cells[idx].x)
        {
            Cells[idx].alive = false;
        }
    }
}
int C_MAP[MAX][MAX];
void Start()
{
    for(int t = 1; t <= K; t++)
    {
        memset(C_MAP, -1, sizeof(C_MAP));
        vector<pair<int, int>> plus;
        
        for(int i = 0; i < Cells.size(); i++)
        {
            if(Cells[i].alive == false)
            {
                continue;
            }
            
            // 활성상태이면 퍼지기
            if(Cells[i].able == true)
            {
                // 네방향으로
                for(int k = 0; k < 4; k++)
                {
                    int r = Cells[i].r + dr[k];
                    int c = Cells[i].c + dc[k];
                    
                    // 이미 존재하면 번식 X
                    if(MAP[r][c] > -1)
                    {
                        continue;
                    }
                    
                    if(C_MAP[r][c] == -1)
                    {
                        plus.push_back({r, c});
                        C_MAP[r][c] = Cells[i].x;
                    }
                    
                    else
                    {
                        int x = C_MAP[r][c];
                        if(Cells[i].x > x)
                        {
                            C_MAP[r][c] = Cells[i].x;
                        }
                    }
                }
            }
            
            // 세포 상태 변경
            ChangeState(i);
        }
        
        for(int i = 0; i < plus.size(); i++)
        {
            int r = plus[i].first;
            int c = plus[i].second;
            
            MAP[r][c] = (int)Cells.size();
            Cell cell;
            cell.r = r; cell.c = c; cell.x = C_MAP[r][c];
            Cells.push_back(cell);
        }
    }
}

void Calculate()
{
    for(int i = 0; i < Cells.size(); i++)
    {
        if(Cells[i].alive == true)
        {
            Answer++;
        }
    }
}

void Solve()
{
    Start();
    Calculate();
}

int main(int argc, char** argv)
{
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        Initialize();
        Input();
        Solve();
        cout << "#" << t << ' ' << Answer << endl;
    }
    
    return 0;
}
