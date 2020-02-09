/*
 BAEKJOON
 15644. 구슬 탈출 3
 
 */
#include <iostream>
#include <string>
#include <vector>
#define MAX 10
using namespace std;

int N, M, answer = 987654321;
string str;
char map[MAX][MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
pair<int, int> red;
pair<int, int> blue;
string answer_str;

void input()
{
    cin >> N >> M;
    
    for(int i = 0; i < N; i++)
    {
        cin >> str;
        for(int j = 0; j < M; j++)
        {
            if(str[j] == 'B')
            {
                blue.first = i;
                blue.second = j;
                map[i][j] = '.';
            }
            else if(str[j] == 'R')
            {
                red.first = i;
                red.second = j;
                map[i][j] = '.';
            }
            else
            {
                map[i][j] = str[j];
            }
        }
    }
}

pair<bool, pair<int, int>> roll(pair<int, int> ball, int dir)
{
    while(1)
    {
        int nr = ball.first + dr[dir];
        int nc = ball.second + dc[dir];
        
        if(map[nr][nc] == '#')
        {
            return make_pair(false, ball);
        }
        else if(map[nr][nc] == 'O')
        {
            return make_pair(true, ball);
        }
        else
        {
            ball.first = nr;
            ball.second = nc;
        }
    }
}

int move_distance(int r, int c, int rr, int cc)
{
    return abs(r - rr) + abs(c - cc);
}

void success(string s)
{
    if(answer == 987654321)
    {
        answer_str = s; answer = (int)s.length();
    }
    
    else
    {
        if(s.length() < answer_str.length())
        {
            answer_str = s; answer = (int)s.length();
        }
    }
}

char reverse_char(int dir)
{
    if(dir == 0) return 'U';
    else if(dir == 1) return 'D';
    else if(dir == 2) return 'L';
    else if(dir == 3) return 'R';
}

int reverse_dir(int dir)
{
    if(dir == 0) return 1;
    else if(dir == 1) return 0;
    else if(dir == 2) return 3;
    else if(dir == 3) return 2;
}

void DFS(int dir, string S, pair<int, int> R, pair<int, int> B)
{
    S += reverse_char(dir);
    
    pair<bool, pair<int, int>> roll_R = roll(R, dir);
    pair<bool, pair<int, int>> roll_B = roll(B, dir);
    
    if((roll_R.first && roll_B.first) || roll_B.first)
    {
        return; // 실패
    }
    
    else if(roll_R.first)
    {
        success(S); return; // 성공
    }
    
    if(S.length() == 10)
    {
        return; // 실패
    }
    
    if(roll_R.second.first == roll_B.second.first && roll_R.second.second == roll_B.second.second)
    {
        int move_R = move_distance(R.first, R.second, roll_R.second.first, roll_R.second.second);
        int move_B = move_distance(B.first, B.second, roll_B.second.first, roll_B.second.second);
        
        if(move_R > move_B)
        {
            roll_R.second.first -= dr[dir];
            roll_R.second.second -= dc[dir];
        }
        else
        {
            roll_B.second.first -= dr[dir];
            roll_B.second.second -= dc[dir];
        }
    }
    
    for(int i = 0; i < 4; i++)
    {
        if(i == dir || i == reverse_dir(dir)) continue; // 같은 방향은 체크할 필요 X
        DFS(i, S, roll_R.second, roll_B.second);
    }
}

void solve()
{
    for(int i = 0; i < 4; i++)
    {
        DFS(i, "", red, blue);
    }
    
    if(answer == 987654321)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << answer << endl;
        cout << answer_str << endl;
    }
}

int main()
{
    input();
    solve();
    
    return 0;
}
