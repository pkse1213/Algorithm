/*
 https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeW7FakkUDFAVH
 4014. [모의 SW 역량테스트] 활주로 건설
 
 48분 소요
 
 시뮬레이션
 
 주의할 경우의 수 (경사로 길이 2라고 가정)
 
 3 3 2 1 1
 높이가 낮아질 때마다 카운트를 다시 시작하면 2의 경우가 건너뛰어질 수 있다.
 
 3 2 2 2 1
 마지막 높이가 낮아진 상태에서 경사로를 둘 수 있는 지 체크해야 함
 
 따라서 낮아질 때를 flag 변수로 제어하며 체크함
 */

#include <iostream>
#define MAX 21
using namespace std;

int T, N, X, Answer;
int map[MAX][MAX];

void Initialize()
{
    Answer = 0;
}

void Input()
{
    cin >> N >> X;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> map[i][j];
        }
    }
}

bool Row(int r)
{
    int cnt = 1;
    int before = map[r][1];
    int flag = false;
    
    for(int c = 2; c <= N; c++)
    {
        if(abs(map[r][c] - before) > 1)
        {
            return false;
        }
        
        if(flag == true)
        {
            if(map[r][c] != before)
            {
                if(cnt < X)
                {
                    return false;
                }
                else
                {
                    flag = false; cnt = 0;
                }
            }
            else if(map[r][c] == before)
            {
                if(cnt == X)
                {
                    flag = false; cnt = 0;
                }
            }
        }
        
        if(map[r][c] == before)
        {
            cnt++;
        }
        else if(map[r][c] == before + 1)
        {
            if(cnt >= X)
            {
                cnt = 1;
            }
            else
            {
                return false;
            }
        }
        else if(map[r][c] == before - 1)
        {
            cnt = 1; flag = true;
        }
        else
        {
            return false;
        }
        
        before = map[r][c];
    }
    
    if(flag == true)
    {
        if(cnt < X)
        {
            return false;
        }
    }
    
    return true;
}

bool Column(int c)
{
    int cnt = 1;
    int before = map[1][c];
    int flag = false;
    
    for(int r = 2; r <= N; r++)
    {
        if(abs(map[r][c] - before) > 1)
        {
            return false;
        }
        
        if(flag == true)
        {
            if(map[r][c] != before)
            {
                if(cnt < X)
                {
                    return false;
                }
                else
                {
                    flag = false; cnt = 0;
                }
            }
            else if(map[r][c] == before)
            {
                if(cnt == X)
                {
                    flag = false; cnt = 0;
                }
            }
        }
        
        if(map[r][c] == before)
        {
            cnt++;
        }
        else if(map[r][c] == before + 1)
        {
            if(cnt >= X)
            {
                cnt = 1;
            }
            else
            {
                return false;
            }
        }
        else if(map[r][c] == before - 1)
        {
            cnt = 1; flag = true;
        }
        else
        {
            return false;
        }
        
        before = map[r][c];
    }
    
    if(flag == true)
    {
        if(cnt < X)
        {
            return false;
        }
    }
    
    return true;
}

void Solve()
{
    for(int i = 1; i <= N; i++)
    {
        if(Row(i) == true) Answer++;
        if(Column(i) == true) Answer++;
    }
}

int main()
{
    cin >> T;
    for(int i = 1; i <= T; i++)
    {
        Initialize();
        Input();
        Solve();
        cout << "#" << i << " " << Answer << endl;
    }
    
    return 0;
}
