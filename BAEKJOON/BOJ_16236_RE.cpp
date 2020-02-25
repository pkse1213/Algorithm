/*
 다시풀기
 16236. 아기상어
 
 역시 인간은 같은 실수를 하는구나..
 1)
 BFS로 검색하고 상, 좌, 우, 하로 우선순위를 두고 발견한 물고기를 잡고 바로 탐색을 끝내면 된다고 생각했다.
 크기가 큰 물고기는 지나가지 못하므로 우선순위가 항상 보장되지 않는다.
 따라서 가능한 물고기를 다 벡터에 저장하고 sorting 해야 함.
 비슷한 실수로 틀렸던 문제 -> 17135. 캐슬 디펜스
 
 2)
 물고기와 상어의 거리를 좌표값 차이로만 계산하면 된다고 생각했다.
 int distance(int r, int rr, int c, int cc)
 {
     return abs(r-rr) + abs(c-cc);
 }
 -> 상어보다 크기가 큰 물고기를 마주치면 지날 수 없다.
    따라서 돌아가서 물고기를 잡아먹을 수도 있기 때문에 좌표값으로만 계산하면 안된다.
    Fish 객체에 d 변수를 추가하고, pop한 후 상하좌우를 탐색할 때 d+1을 해서 거리를 저장해 주었다.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define MAX 21
using namespace std;

struct Shark_Info
{
    int r, c;
    int size;
};

struct Fish_Info
{
    int r, c, d;
    Fish_Info(int rr, int cc, int dd)
    {
        r = rr; c = cc; d = dd;
    }
};

int N, Answer, Fish_Num = 0, Time = 0;
Shark_Info Shark;
int MAP[MAX][MAX];
int Visited[MAX][MAX];
int dr[4] = {-1, 0, 0, 1};
int dc[4] = {0, -1, 1, 0};

void Input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
            if(MAP[i][j] == 9)
            {
                MAP[i][j] = 0;
                Shark.r = i; Shark.c = j; Shark.size = 2;
            }
        }
    }
}

bool ACS(Fish_Info A, Fish_Info B)
{
    if(A.d == B.d){
        if(A.r == B.r)
        {
            return A.c < B.c;
        }
        else
        {
            return A.r < B.r;
        }
    }
    else
    {
        return A.d < B.d;
    }
}

void Print()
{
    cout << "(" << Shark.r+1 << "," << Shark.c+1 << ")" << "," << Shark.size << endl;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout << MAP[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void Solve()
{
    while(1)
    {
        memset(Visited, false, sizeof(Visited));
        queue<Fish_Info> Q;
        vector<Fish_Info> V;
        Q.push(Fish_Info(Shark.r, Shark.c, 0));
        Visited[Shark.r][Shark.c] = true;
        
        while (Q.empty() == false) {
            int r = Q.front().r;
            int c = Q.front().c;
            int d = Q.front().d;
            Q.pop();
            
            for(int i = 0; i < 4; i++)
            {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if(nr < 0 || nr > N - 1 || nc < 0 || nc > N - 1 || Visited[nr][nc] == true)
                {
                    continue;
                }
                
                if(0 < MAP[nr][nc] && MAP[nr][nc] < Shark.size)
                {
                    V.push_back(Fish_Info(nr, nc, d + 1));
                }
                
                else if(MAP[nr][nc] == 0 || MAP[nr][nc] == Shark.size)
                {
                    Q.push(Fish_Info(nr, nc, d + 1));
                }
                
                Visited[nr][nc] = true;
            }
        }
        
        if(V.empty() == true)
        {
            return;
        }
        else
        {
            sort(V.begin(), V.end(), ACS);
            MAP[V.front().r][V.front().c] = 0;
            Shark.r = V.front().r;
            Shark.c = V.front().c;
            Time += V.front().d;
            Fish_Num++;
            if(Fish_Num == Shark.size)
            {
                Shark.size++;
                Fish_Num = 0;
            }
        }
    }
}

int main()
{
    Input();
    Solve();
    cout << Time << endl;
}
