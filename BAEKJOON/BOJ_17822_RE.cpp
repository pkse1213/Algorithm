/*
 17822. 원판 돌리기
 
 계속 N, M을 제대로 체크 안하고 R, C 범위 체크를 해주어서 틀렸다... 이런 실수는 없도록 하자ㅠ!
 
 [하나 더 알게된 점]
 삭제된 숫자는 0으로 초기화해도 된다.
 1 ≤ 원판에 적힌 수 ≤ 1,000 이므로
 평균은 항상 1보다 크다.
 따라서 1보다 큰 수(= 아무리 크더라도 2)에서 1을 빼도 0이 되진 않는다.
 
 */
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 51
#define INF 987654321
using namespace std;

struct Turn_Info
{
    int x, d, k;
};

int N, M, T, Answer;
int Circle[MAX][MAX];
bool Visited[MAX][MAX];
vector<Turn_Info> Turn;
int Dr[4] = {0, 0, -1, 1};
int Dc[4] = {-1, 1, 0, 0};

void Input()
{
    cin >> N >> M >> T;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cin >> Circle[i][j];
        }
    }
    for(int i = 1; i <= T; i++)
    {
        Turn_Info turn;
        cin >> turn.x >> turn.d >> turn.k;
        Turn.push_back(turn);
    }
}

void Rotate_Circle(int X, int D, int K)
{
    if(D == 0)
    {
        for(int i = X; i <= N; i += X)
        {
            for(int k = 0; k < K; k++)
            {
                int Last = Circle[i][M];
                for(int j = M; j > 1; j--)
                {
                    Circle[i][j] = Circle[i][j - 1];
                }
                Circle[i][1] = Last;
            }
        }
    }
    else if(D == 1)
    {
        for(int i = X; i <= N; i += X)
        {
            for(int k = 0; k < K; k++)
            {
                int First = Circle[i][1];
                for(int j = 1; j < M; j++)
                {
                    Circle[i][j] = Circle[i][j + 1];
                }
                Circle[i][M] = First;
            }
        }
    }
}

void Print()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(Circle[i][j] == INF) cout << "." << ' ';
            else cout << Circle[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

bool BFS(int r, int c, int Num)
{
    bool Find = false;
    queue<pair<int, int>> Q;
    Q.push({r, c});
    Visited[r][c] = true;
    
    while (Q.empty() == false)
    {
        int R = Q.front().first;
        int C = Q.front().second;
        Q.pop();
        
        for(int i = 0; i < 4; i++)
        {
            int Nr = R + Dr[i];
            int Nc = C + Dc[i];
            
            if(Nr < 1 || Nr > N || Visited[Nr][Nc] == true || Circle[Nr][Nc] == INF) continue;
            
            if(Nc == 0) Nc = M;
            else if(Nc == M + 1) Nc = 1;
            
            if(Circle[Nr][Nc] == Num)
            {
                Q.push({Nr, Nc});
                Visited[Nr][Nc] = true;
                Circle[Nr][Nc] = INF;
                Find = true;
            }
        }
    }
    return Find;
}

pair<int, int> Calculate()
{
    int Sum = 0;
    int Num = 0;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(Circle[i][j] != INF)
            {
                Sum += Circle[i][j];
                Num++;
            }
        }
    }
    return make_pair(Sum, Num);
    
}

void Rearrange_Circle(double Avg)
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(Circle[i][j] != INF)
            {
                if(Circle[i][j] < Avg)
                {
                    Circle[i][j]++;
                }
                else if(Circle[i][j] > Avg)
                {
                    Circle[i][j]--;
                }
            }
        }
    }
}

void Solve()
{
    for(int t = 0; t < T; t++)
    {
//        cout << "###########" << endl;
        Rotate_Circle(Turn[t].x, Turn[t].d, Turn[t].k);
//        Print();
        memset(Visited, false, sizeof(Visited));
        
        bool Find = false;
        for(int i = 1; i <= N; i++)
        {
            for(int j = 1; j <= M; j++)
            {
                if(Visited[i][j] == false && Circle[i][j] != INF)
                {
                    if(BFS(i, j, Circle[i][j]) == true)
                    {
                        Circle[i][j] = INF;
                        Find = true;
                    }
                }
            }
        }
        
        if(Find == false)
        {
            pair<int, int> Result = Calculate();
            double Avg = (double)Result.first / (double)Result.second;
            Rearrange_Circle(Avg);
        }
//        Print();
    }
}

int main()
{
    Input();
    Solve();
    pair<int, int> Reuslt = Calculate();
    cout << Reuslt.first << endl;
    return 0;
}
