#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#define MAX 101
using namespace std;

int R, C, N, H;
string S;
char map[MAX][MAX];
vector<char> height;
vector<pair<int, int>> cluster;
int dr[4] = {0, 0, -1, 1};
int dc[4] = {1, -1, 0, 0};

void input()
{
    cin >> R >> C;
    for(int i = 1; i <= R; i++)
    {
        cin >> S;
        for(int j = 1; j <= C; j++)
        {
            map[i][j] = S[j-1];
        }
    }
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> H;
        height.push_back(H);
    }
}

void print()
{
    for(int i = 1; i <= R; i++)
    {
        for(int j = 1; j <= C; j++)
        {
            cout << map[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

bool desc(int a, int b)
{
    return a > b;
}

void fight()
{
    for(int i = 0; i < height.size(); i++)
    {
        H = R - height[i] + 1;
        pair<int, int> mineral = make_pair(0, 0);
        
        if(i % 2 == 0) // 홀수, 왼->오
        {
            for(int n = 1; n <= C; n++)
            {
                if(map[H][n] == 'x')
                {
                    mineral = make_pair(H, n);
                    break;
                }
            }
        }
        else if(i % 2 == 1) // 짝수, 오->왼
        {
            for(int n = C; n >= 1; n--)
            {
                if(map[H][n] == 'x')
                {
                    mineral = make_pair(H, n);
                    break;
                }
            }
        }
        
        // 해당 높이에 미네랄이 없으면 다음으로
        if(mineral.first == 0 && mineral.second == 0)
        {
            continue;
        }
        
        map[mineral.first][mineral.second] = '.';

        bool visited[MAX][MAX] = { false };
        visited[mineral.first][mineral.second] = true;
        
        for(int j = 0; j < 4; j++)
        {
            queue<pair<int, int>> Q;
            vector<int> V[MAX];
            
            int sr = mineral.first + dr[j];
            int sc = mineral.second + dc[j];
            
            if(sr < 1 || sr > R || sc < 1 || sc > C || visited[sr][sc] == true) continue;
            
            visited[sr][sc] = true;
            
            if(map[sr][sc] == 'x')
            {
                bool find = false;
                
                Q.push(make_pair(sr, sc));
                V[sc].push_back(sr);
                
                while(!Q.empty())
                {
                    int r = Q.front().first;
                    int c = Q.front().second;
                    Q.pop();
                    
                    for(int k = 0; k < 4; k++)
                    {
                        int nr = r + dr[k];
                        int nc = c + dc[k];
                        
                        if(nr < 1 || nr > R || nc < 1 || nc > C || visited[nr][nc] == true)
                        {
                            continue;
                        }
                        
                        visited[nr][nc] = true;
                        
                        if(map[nr][nc] == 'x')
                        {
                            if(nr == R)
                            {
                                find = true;
                                break;
                            }
                            else
                            {
                                Q.push(make_pair(nr, nc));
                                V[nc].push_back(nr);
                            }
                        }
                    }
                    
                    if(find == true)
                    {
                        break;
                    }
                }
               
                if(find == false)
                {
                    int distance = MAX;
                    for(int c = 1; c <= C; c++)
                    {
                        
                        if(V[c].empty() == false)
                        {
                            for(int n = 0; n < V[c].size(); n++)
                            {
                                map[V[c][n]][c] = '.';
                            }
                            
                            for(int n = 0; n < V[c].size(); n++)
                            {
                                int temp = 0;
                                for(int r = V[c][n] + 1; r <= R; r++)
                                {
                                    temp++;
                                    if(map[r][c] == 'x')
                                    {
                                        temp--;
                                        break;
                                    }
                                }
                                distance = min(distance, temp);
                            }
                        }
                    }
                    
                    for(int c = 1; c <= C; c++)
                    {
                        if(V[c].empty() == false)
                        {
                            for(int n = 0; n < V[c].size(); n++)
                            {
                                map[V[c][n] + distance][c] = 'x';
                            }
                        }
                    }
                }
            }
        }
//        print();
    }
}

void solve()
{
    fight();
    print();
}

int main()
{
    input();
    solve();
    return 0;
}

