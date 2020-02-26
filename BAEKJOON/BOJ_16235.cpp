/*
 16235. 나무 재테크
 
 50분
 시뮬레이션
 
 조건에 따라서 잘 구현하면 됨. 큰 어려운 점은 없다.
 */
 #include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#define MAX 11
using namespace std;

int N, M, K, x, y, z, Answer = 0;
vector<int> MAP[MAX][MAX]; // 나이
int Nutrient[MAX][MAX];
int A[MAX][MAX];
int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

void Input()
{
    cin >> N >> M >> K;
    for(int i = 1; i <= N; i++)
    {
       for(int j = 1; j <= N; j++)
        {
            cin >> A[i][j];
            Nutrient[i][j] = 5;
        }
    }
    for(int i = 1; i <= M; i++)
    {
        cin >> x >> y >> z;
        MAP[x][y].push_back(z);
    }
}

void Sorting()
{
    for(int r = 1; r <= N; r++)
    {
        for(int c = 1; c <= N; c++)
        {
            if(MAP[r][c].empty() == false)
            {
                sort(MAP[r][c].begin(), MAP[r][c].end());
            }
        }
    }
}

/*
 봄에는 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다.
 각각의 나무는 나무가 있는 1×1 크기의 칸에 있는 양분만 먹을 수 있다.
 하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다.
 만약, 땅에 양분이 부족해 자신의 나이만큼 양분을 먹을 수 없는 나무는 양분을 먹지 못하고 즉시 죽는다.

 여름에는 봄에 죽은 나무가 양분으로 변하게 된다.
 각각의 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가된다. 소수점 아래는 버린다.
*/
void Spring_Summer()
{
    for(int r = 1; r <= N; r++)
    {
        for(int c = 1; c <= N; c++)
        {
            if(MAP[r][c].empty() == true) continue;
            
            int i;
            bool Die = false;
            for(i = 0; i < MAP[r][c].size(); i++)
            {
                if(Nutrient[r][c] < MAP[r][c][i])
                {
                    Die = true;
                    break;
                }
                else
                {
                    Nutrient[r][c] -= MAP[r][c][i];
                    MAP[r][c][i] += 1;
                }
            }
            
            if(Die == true)
            {
                for(int j = (int)MAP[r][c].size() - 1; j >= i ; j--)
                {
                    Nutrient[r][c] += MAP[r][c][j] / 2;
                    MAP[r][c].pop_back();
                }
            }
        
        }
    }
}

/*
 가을에는 나무가 번식한다.
 번식하는 나무는 나이가 5의 배수이어야 하며, 인접한 8개의 칸에 나이가 1인 나무가 생긴다.
 어떤 칸 (r, c)와 인접한 칸은 (r-1, c-1), (r-1, c), (r-1, c+1), (r, c-1), (r, c+1), (r+1, c-1), (r+1, c), (r+1, c+1) 이다.
 상도의 땅을 벗어나는 칸에는 나무가 생기지 않는다.

 겨울에는 S2D2가 땅을 돌아다니면서 땅에 양분을 추가한다.
 */
void Fall_Winter()
{
    for(int r = 1; r <= N; r++)
    {
        for(int c = 1; c <= N; c++)
        {
            Nutrient[r][c] += A[r][c]; // 겨울
            
            if(MAP[r][c].empty() == true) continue;
            
            for(int i = 0; i < MAP[r][c].size(); i++)
            {
                if(MAP[r][c][i] % 5 == 0)
                {
                    for(int j = 0; j < 8; j++)
                    {
                        int nr = r + dr[j];
                        int nc = c + dc[j];
                        
                        if(nr < 1 || nr > N || nc < 1 || nc > N) continue;
                        
                        MAP[nr][nc].push_back(1);
                    }
                }
            }
        }
    }
}

void Calculate()
{
    for(int r = 1; r <= N; r++)
    {
        for(int c = 1; c <= N; c++)
        {
            Answer += MAP[r][c].size();
        }
    }
}

void Solve()
{
    for(int i = 0; i < K; i++)
    {
        Sorting();
        Spring_Summer();
        Fall_Winter();
    }
}

int main()
{
    Input();
    Solve();
    Calculate();
    cout << Answer << endl;
    return 0;
}

