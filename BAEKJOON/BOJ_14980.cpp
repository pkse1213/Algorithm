/*
 14890. 경사로
 */

#include <iostream>
#include <math.h>
using namespace std;

int N, L, board[101][101], answer = 0;

void check1()
{
    for(int  i = 0; i < N; i++)
    {
        bool check = false;
        bool find = true;
        int n = 1;
        for(int j = 1; j < N; j++)
        {
            int gap = board[i][j-1] - board[i][j];
            
            // 같을 떄
            if(gap == 0)
            {
                n++;
                // 경사 다른 것 체크 중 & 경사 가능
                if(check && n == L)
                {
                    n = 0;
                    check = false;
                }
            }
            // 다를 때
            else
            {
                // 갭이 1보다 크면 체크 종료
                if(abs(gap) > 1 || (check && n < L))
                {
                    find = false;
                    break;
                }
                // 1 낮아짐
                if(gap > 0)
                {
                    if(L == 1)
                    {
                        n = 0; continue;
                    }
                    else
                    {
                        check = true;
                        n = 1;
                    }
                }
                // 1 높아짐
                else
                {
                    // 경사로 가능
                    if(n >= L)
                    {
                        n = 1;
                    }
                    else
                    {
                        find = false;
                        break;
                    }
                }
                
            }
        }
        if(find == false) continue;
        if(!check || (check && n >= L)) answer++;
    }
}

void check2()
{
    for(int  j = 0; j < N; j++)
    {
        bool check = false;
        bool find = true;
        int n = 1;
        for(int i = 1; i < N; i++)
        {
            int gap = board[i-1][j] - board[i][j];
            
            // 같을 떄
            if(gap == 0)
            {
                n++;
                // 경사 다른 것 체크 중 & 경사 가능
                if(check && n == L)
                {
                    n = 0;
                    check = false;
                }
            }
            // 다를 때
            else
            {
                // 갭이 1보다 크면 체크 종료
                if(abs(gap) > 1 || (check && n < L))
                {
                    find = false;
                    break;
                }
                // 1 낮아짐
                if(gap > 0)
                {
                    if(L == 1)
                    {
                        n = 0; continue;
                    }
                    else
                    {
                        check = true;
                        n = 1;
                    }
                }
                // 1 높아짐
                else
                {
                    // 경사로 가능
                    if(n >= L)
                    {
                        n = 1;
                    }
                    else
                    {
                        find = false;
                        break;
                    }
                }
                
            }
        }
        if(find == false) continue;
        if(!check || (check && n >= L)) answer++;
    }
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> N >> L;
    
    for(int  i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cin >> board[i][j];
        }
    }
    
    check1();
//    cout << answer << endl;
    check2();
    cout << answer;
    
    
    return 0;
}
