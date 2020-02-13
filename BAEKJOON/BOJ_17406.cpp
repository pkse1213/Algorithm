/*
 BAEKJOON
 17406. 배열 돌리기 4
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 51
using namespace std;

struct rotation
{
    int r, c, s;
};

int N, M, K, R, C, S, Answer = 987654321;
vector<rotation> V;
int map[MAX][MAX];
int c_map[MAX][MAX];
int operation[6];
bool selected[6] = { false };

void input()
{
    cin >> N >> M >> K;
    
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cin >> map[i][j];
        }
    }
    
    for(int i = 0; i < K; i++)
    {
        cin >> R >> C >> S;
        rotation r;
        r.r = R; r.c = C; r.s = S;
        V.push_back(r);
    }
}

void copy_map()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            c_map[i][j] = map[i][j];
        }
    }
}

void print_map()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cout << c_map[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl << endl;
}

void rotate()
{
    for(int p = 0; p < K; p++)
    {
        int idx = operation[p];
        int r = V[idx].r;
        int c = V[idx].c;
        int s = V[idx].s;
        
        for(int d = 1; d <= s; d++)
        {
            int first = c_map[r - d][c - d];
            
            for(int i = 0; i < d * 2; i++)
            {
                c_map[r - d + i][c - d] = c_map[r - d + i + 1][c - d];
            }
            
            for(int i = 0; i < d * 2; i++)
            {
                c_map[r + d][c - d + i] = c_map[r + d][c - d + i + 1];
            }
            
            for(int i = 0; i < d * 2; i++)
            {
                c_map[r + d - i][c + d] = c_map[r + d - i - 1][c + d];
            }
            
            for(int i = 0; i < d * 2 -1; i++)
            {
                c_map[r - d][c + d - i] = c_map[r - d][c + d - i - 1];
            }
            
            c_map[r - d][c - d + 1] = first;
        }
        
//        print_map();
    }
}

void find_min()
{
    int min_temp = 987654321;
    
    for(int i = 1; i <= N; i++)
    {
        int sum = 0;
        for(int j = 1; j <= M; j++)
        {
            sum += c_map[i][j];
        }
        min_temp = min(min_temp, sum);
    }
    
    Answer = min(Answer, min_temp);
}

void DFS(int idx, int cnt)
{
    if(cnt == K)
    {
        copy_map();
        rotate();
        find_min();
        return;
    }
    
    for(int i = 0; i < K; i++)
    {
        if(selected[i] == true) continue;
        
        operation[cnt] = i;
        selected[i] = true;
        
        DFS(idx + 1, cnt + 1);
        
        selected[i] = false;
    }
}

void solve()
{
    DFS(0, 0);
    cout << Answer << endl;
}

int main()
{
    input();
    solve();
    return 0;
}
