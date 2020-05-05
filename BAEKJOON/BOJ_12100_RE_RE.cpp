/*
 12100. 2048
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 21
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

int n, origin[MAX][MAX], board[MAX][MAX], answer = -1;
int route[5];

void copy_map()
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            board[i][j] = origin[i][j];
}

void print()
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void right()
{
    for(int i = 0; i < n; i++)
    {
        int before = -1;
        vector<int> v;
        for(int j = n-1; j >= 0; j--)
        {
            if(board[i][j] == 0) continue;
            if(before == -1) before = board[i][j];
            else if(board[i][j] == before)
            {
                v.push_back(before*2);
                before = -1;
            }
            else
            {
                v.push_back(before);
                before = board[i][j];
            }
            board[i][j] = 0;
        }
        
        if(before != -1) v.push_back(before);
        
        int s = n - v.size();
        for(int j = v.size()-1; j >= 0; j--)
        {
            board[i][s++] = v[j];
        }
    }
}

void left()
{
    for(int i = 0; i < n; i++)
    {
        int before = -1;
        vector<int> v;
        for(int j = 0; j < n; j++)
        {
            if(board[i][j] == 0) continue;
            if(before == -1) before = board[i][j];
            else if(board[i][j] == before)
            {
                v.push_back(before*2);
                before = -1;
            }
            else
            {
                v.push_back(before);
                before = board[i][j];
            }
            board[i][j] = 0;
        }
        
        if(before != -1) v.push_back(before);
        
        for(int j = 0; j < v.size(); j++)
        {
            board[i][j] = v[j];
        }
    }
}

void up()
{
    for(int j = 0; j < n; j++)
    {
        int before = -1;
        vector<int> v;
        for(int i = 0; i < n; i++)
        {
            if(board[i][j] == 0) continue;
            if(before == -1) before = board[i][j];
            else if(board[i][j] == before)
            {
                v.push_back(before*2);
                before = -1;
            }
            else
            {
                v.push_back(before);
                before = board[i][j];
            }
            board[i][j] = 0;
        }
        
        if(before != -1) v.push_back(before);
        
        for(int i = 0; i < v.size(); i++)
        {
            board[i][j] = v[i];
        }
    }
}

void down()
{
    for(int j = 0; j < n; j++)
    {
        int before = -1;
        vector<int> v;
        for(int i = n-1; i >= 0; i--)
        {
            if(board[i][j] == 0) continue;
            if(before == -1) before = board[i][j];
            else if(board[i][j] == before)
            {
                v.push_back(before*2);
                before = -1;
            }
            else
            {
                v.push_back(before);
                before = board[i][j];
            }
            board[i][j] = 0;
        }
        
        if(before != -1) v.push_back(before);
        
        int s = n - v.size();
        for(int i = v.size()-1; i >= 0; i--)
        {
            board[s++][j] = v[i];
        }
    }
}

int find_max()
{
    int m = -1;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            m = max(m, board[i][j]);
        }
    }
    return m;
}

void start_game()
{
    copy_map();
    
    for(int i = 0; i < 5; i++)
    {
        if(route[i] == 1) left();
        if(route[i] == 2) right();
        if(route[i] == 3) up();
        if(route[i] == 0) down();
    }
    
    answer = max(answer, find_max());
}

void find_route(int cnt)
{
    if(cnt == 5)
    {
        start_game();
        return;
    }
    
    for(int i = 0; i < 4; i++)
    {
        route[cnt] = i;
        find_route(cnt+1);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> origin[i][j];
    
    for(int i = 0; i < 4; i++)
    {
        route[0] = i;
        find_route(1);
    }
    
    cout << answer;
    return 0;
}
