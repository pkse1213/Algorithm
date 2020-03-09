/*
 SWEA 4796. 의석이의 우뚝 선 산
 
 시뮬레이션
 
 */
#include <iostream>
#include <vector>
using namespace std;

int T, N, H, Answer;;
vector<int> Height;
vector<char> Diff;

void Initialize()
{
    Height.clear();
    Diff.clear();
    Answer = 0;
}

void Input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> H;
        Height.push_back(H);
        
        if(i > 0)
        {
            if(Height[i - 1] < Height[i])
            {
                Diff.push_back('U');
            }
            else
            {
                Diff.push_back('D');
            }
        }
    }
}

void Solve()
{
    int Up = 0;
    int Down = 0;
    
    for(int i = 0; i < Diff.size(); i++)
    {
        if(Diff[i] == 'U')
        {
            if(Down > 0)
            {
                Answer += Up * Down;
                Up = 0;
                Down = 0;
            }
                
            Up++;
        }
        
        else
        {
            if(Up > 0)
            {
                Down++;
            }
        }
    }
    
    // 올라갔다가 마지막에 낮아진 후 끝난 경우도 체크
    Answer += Up * Down;
}

int main()
{
    cin >> T;
    for(int TC = 1; TC <= T; TC++)
    {
        Initialize();
        Input();
        Solve();
        
        printf("#%d %d \n", TC, Answer);
    }
    
    return 0;
}
