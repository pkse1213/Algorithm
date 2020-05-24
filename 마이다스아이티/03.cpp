#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
#include <deque>
#include <stack>
#include <map>
#include <sstream>
#include <regex>
#include <math.h>
#define MAX 11
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

int dr[4] = {0,0,1,-1};
int dc[4] = {1,-1,0,0};


void print(vector<vector<int>> board)
{
    
    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[i].size(); j++)
        {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}


int game(int r, int c, vector<vector<int>> board)
{
//    if(r == 2 && c == 1)
//        cout << "\n";
    board[r][c] = 0;
    for(int i = r; i > 0; i--)
    {
        board[i][c] = board[i-1][c];
    }
    board[0][c] = 0;
    while(1)
    {
        bool diff = false;
        bool selected[10][10];
        memset(selected, false, sizeof(selected));
        
        for(int i = 0; i < board.size(); i++)
        {
            vector<int> v;
            v.push_back(0);
            int before = board[i][0];
            for(int j = 1; j < board.size(); j++)
            {
                int cur = board[i][j];
                if(cur != before || board[i][j] == 0)
                {
                    if(v.size() >= 3)
                    {
                        diff = true;
                        for(int n = 0; n < v.size(); n++)
                        {
                            selected[i][v[n]] = true;
                        }
                    }
                    v.clear();
                    v.push_back(j);
                }
                else v.push_back(j);
                
                before = cur;
            }
            if(v.size() >= 3)
            {
                diff = true;
                for(int n = 0; n < v.size(); n++)
                {
                    selected[i][v[n]] = true;
                }
            }
        }
        
        for(int j = 0; j < board.size(); j++)
        {
            vector<int> v;
            v.push_back(0);
            int before = board[0][j];
            for(int i = 1; i < board.size(); i++)
            {
                int cur = board[i][j];
                
                if(cur != before || board[i][j] == 0)
                {
                    if(v.size() >= 3)
                    {
                        for(int n = 0; n < v.size(); n++)
                        {
                            selected[v[n]][j] = true;
                            diff = true;
                        }
                    }
                    v.clear();
                    v.push_back(i);
                }
                else v.push_back(i);
                before = cur;
            }
            if(v.size() >= 3)
            {
                for(int n = 0; n < v.size(); n++)
                {
                    selected[v[n]][j] = true;
                    diff = true;
                }
            }
        }

//        print(board);
        if(!diff)
            break;
        
        for(int j = 0; j < board.size(); j++)
        {
            vector<int> v;
            for(int i = (int)board.size()-1; i >= 0; i--)
            {
                if(board[i][j] != 0 && !selected[i][j])
                {
                    v.push_back(board[i][j]);
                }
                board[i][j] = 0;
            }
            for(int i = 0; i < v.size(); i++)
            {
                board[board.size()-1-i][j] = v[i];
            }
        }
        
//        print(board);
//        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
    }
    
    int cnt = 0;
    for(int i = 0; i < board.size(); i++)
        for(int j = 0; j < board.size(); j++)
            if(board[i][j] == 0) cnt++;
    
    return cnt;
    
    
}


int solution(vector<vector<int>> board)
{
    int ans = 0;
    
    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board.size(); j++)
        {
            int score = game(i, j, board);
            if(score > ans) ans = score;
        }
    }
    return ans;
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cout << solution(    {{1, 1, 3, 3},{4, 1, 3, 4},{1, 2, 1, 1},{2, 1, 3, 2}});
    return 0;
}

