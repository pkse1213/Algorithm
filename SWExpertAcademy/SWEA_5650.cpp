/*
 5650. [모의 SW 역량테스트] 핀볼 게임
 
 1시간 30분 소요
 
 현재 방향에 맞게 블록 방향 처리를 해주면 되었고,
 1. 다음 위치가 벽이라서 다시 현재 위치에 반대 방향으로 되돌아 올 때, 블록이면 다시 방향을 한 번 더 바꿔주어야 한다.
 2. 현재 시작 위치에서 바로 벽이나 5번 블록을 만났을 때, 반대방향으로 돌아와 제자리가 되므로 종료시켜줘야 한다.
 3. 웜홀 쌍을 찾을 때, 현재 웜홀의 r과 c가 모두 달라야 한다고 하였더니 49개가 맞음.
    r, c 둘 다 같지가 않아야 한다 = 둘 중 하나는 달라야 한다 이므로 조건문을 수정했더니 통과.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 101
using namespace std;

int T, N, Answer, Score;
int MAP[MAX][MAX];
int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, 1, 0, -1};
vector<pair<int, int>> Blank;
vector<pair<int, int>> Hole;

void initialize()
{
    Answer = 0;
    Blank.clear();
    Hole.clear();
}

void Input()
{
    cin >> N;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> MAP[i][j];
            
            if(MAP[i][j] == 0)
            {
                Blank.push_back({ i, j });
            }
            else if(MAP[i][j] >= 6)
            {
                Hole.push_back({ i, j });
            }
        }
    }
}

int Reverse_Dir(int dir)
{
    if(dir == 0) return 2;
    else if(dir == 1) return 3;
    else if(dir == 2) return 0;
    else if(dir == 3) return 1;
}

int Rotate_Dir(int dir, int block)
{
    if(block == 1)
    {
        if(dir == 0) return 1;
        else if(dir == 1) return 3;
        else if(dir == 2) return 0;
        else if(dir == 3) return 2;
    }
    else if(block == 2)
    {
        if(dir == 0) return 2;
        else if(dir == 1) return 3;
        else if(dir == 2) return 1;
        else if(dir == 3) return 0;
    }
    else if(block == 3)
    {
        if(dir == 0) return 2;
        else if(dir == 1) return 0;
        else if(dir == 2) return 3;
        else if(dir == 3) return 1;
    }
    else if(block == 4)
    {
        if(dir == 0) return 3;
        else if(dir == 1) return 2;
        else if(dir == 2) return 0;
        else if(dir == 3) return 1;
    }
}

int Start(int i, int j, int d)
{
    Score = 0;
    
    int r = i + dr[d];
    int c = j + dc[d];
    
    while(1)
    {
        if(r < 1 || r > N || c < 1 || c > N || MAP[r][c] == 5)
        {
            Score++;
            // 이전 칸으로 되돌아가고
            r -= dr[d];
            c -= dc[d];
            // 방향 바꿈
            d = Reverse_Dir(d);
        }
        
        // 블랙홀이나 제자리
        if(MAP[r][c] == -1 || (r == i && c == j))
        {
            return Score;
        }
        
        // 블록
        else if(1 <= MAP[r][c] && MAP[r][c] <= 4)
        {
            Score++;
            d = Rotate_Dir(d, MAP[r][c]);
        }
        
        // 웜홀
        else if(6 <= MAP[r][c] && MAP[r][c] <= 10)
        {
            for(int i = 0; i < Hole.size(); i++)
            {
                if((Hole[i].first != r || Hole[i].second != c) &&
                   MAP[Hole[i].first][Hole[i].second] == MAP[r][c])
                {
                    r = Hole[i].first;
                    c = Hole[i].second;
                    break;
                }
            }
        }
        
        r += dr[d];
        c += dc[d];
    }
}

void Solve()
{
    for(int i = 0; i < Blank.size(); i++)
    {
        for(int d = 0; d < 4; d++)
        {
            int Score = Start(Blank[i].first, Blank[i].second, d);
            Answer = max(Answer, Score);
        }
    }
}

int main()
{
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        initialize();
        Input();
        Solve();
        
        cout << "#" << t << " " << Answer << endl;
    }
    return 0;
}
