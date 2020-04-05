#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#define MAX 101
using namespace std;

int N, Len, Highest = 0, Width = 0;
string Sort, Str;
vector<pair<int, int>> Number;
vector<vector<char>> Result;

void Input()
{
    cin >> N >> Sort;
    for(int i = 0; i < N; i++)
    {
        cin >> Len >> Str;
        
        for(int i = 0; i < Str.length(); i++)
        {
            char Temp = Str[i];
            Number.push_back({Len, atoi(&Temp)});
        }
        
        Width += Len * Str.length();
        Highest = max(Highest, 2 * Len - 1);
    }
    
    for(int i = 0; i < Highest; i++)
    {
        Result.push_back({});
    }
}

void Draw(int Num, int W, int Start, int End, int Middle)
{
    for(int i = 0; i < Highest; i++)
    {
        for(int j = 0; j < W; j++)
        {
            if(Start <= i && i <= End)
            {
                // 맨 윗줄
                if(i == Start && (Num == 0 || Num == 2 || Num == 3 || Num == 5 || Num == 7 || Num == 8 || Num == 9))
                {
                    Result[i].push_back('#');
                }
                // 맨 아랫줄
                else if(i == End && (Num == 0 || Num == 2 || Num == 3 || Num == 5 || Num == 6 || Num == 8))
                {
                    Result[i].push_back('#');
                }
                // 중간
                else if(i == Middle && (Num == 2 || Num == 3 || Num == 4 || Num == 5 || Num == 6 || Num == 8 || Num == 9))
                {
                    Result[i].push_back('#');
                }
                // 가로 맨 왼
                else if(j == 0 && (Num == 0 || Num == 6 || Num == 8))
                {
                    Result[i].push_back('#');
                }
                // 가로 맨 오
                else if(j == W - 1 && (Num == 0 || Num == 1 || Num == 3 || Num == 4 || Num == 7 || Num == 8 || Num == 9))
                {
                    Result[i].push_back('#');
                }
                // 01378
                else if(i < Middle && j == 0 && (Num == 4 || Num == 5 || Num == 9))
                {
                    Result[i].push_back('#');
                }
                else if(i < Middle && j == W - 1 && (Num == 2))
                {
                    Result[i].push_back('#');
                }
                else if(i > Middle && j == 0 && (Num == 2))
                {
                    Result[i].push_back('#');
                }
                else if(i > Middle && j == W - 1 && (Num == 6 || Num == 5))
                {
                    Result[i].push_back('#');
                }
                else
                {
                    Result[i].push_back('.');
                }
            }
            else
            {
                Result[i].push_back('.');
            }
        }
        Result[i].push_back(' ');
    }
}

void Print()
{
    for(int i = 0; i < Highest; i++)
    {
        for(int j = 0; j < Result[i].size(); j++)
        {
            cout << Result[i][j];
        }
        cout << endl;
    }
}

void Solution()
{
    for(int i = 0; i < Number.size(); i++)
    {
        int Height = 2 * Number[i].first - 1;
        int Start = 0, End = 0;
       
        if(Sort == "TOP")
        {
            Start = 0;
            End = Height - 1;
        }
        else if(Sort == "BOTTOM")
        {
            Start = Highest - Height;
            End = Highest - 1;
        }
        else if(Sort == "MIDDLE")
        {
            Start = Highest / 2 - Height / 2;
            End = Highest / 2 + Height / 2;
        }
        
        Draw(Number[i].second, Number[i].first, Start, End, Start + Height / 2);
    }
}

void Solve()
{
    Solution();
    Print();
}

int main()
{
    Input();
    Solve();

    return 0;
}
