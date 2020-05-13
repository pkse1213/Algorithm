/*
 14500. 테트로미노
 */
#include <iostream>
#include <cstring>
using namespace std;

int N, M, board[500][500];
int answer = 0;
bool visited[500][500];

int dr[4] = {0,0,-1,1};
int dc[4] = {1,-1,0,0};

void find(int i, int j, int cnt, int sum)
{
    if(cnt == 4)
    {
        if(answer < sum)
            answer = sum;
        return;
    }
    
    for(int d = 0; d < 4; d++)
    {
        int r = i + dr[d];
        int c = j + dc[d];
        if(r < 0 || r > N-1 || c < 0 || c > M-1 || visited[r][c]) continue;
        
        visited[r][c] = true;
        find(r, c, cnt + 1, sum + board[r][c]);
        visited[r][c] = false;
    }
}

void other_shape()
{
    // ㅗ, ㅜ
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M - 2; j++)
        {
            int sum = 0;
            for(int k = 0; k < 3; k++)
                sum += board[i][j + k];
            
            if(i - 1 >= 0)
                if(answer < sum + board[i - 1][j + 1])
                    answer = sum + board[i - 1][j + 1];
            if(i + 1 <= N - 1)
                if(answer < sum + board[i + 1][j + 1])
                    answer = sum + board[i + 1][j + 1];
        }
    }
    
    // ㅏ, ㅓ
    for(int j = 0; j < M; j++)
    {
        for(int i = 0; i < N-2; i++)
        {
            int sum = 0;
            for(int k = 0; k < 3; k++)
                sum += board[i + k][j];
            
            if(j - 1 >= 0)
                if(answer < sum + board[i + 1][j - 1])
                    answer = sum + board[i + 1][j - 1];
            if(j + 1 <= N - 1)
                if(answer < sum + board[i + 1][j + 1])
                    answer = sum + board[i + 1][j + 1];
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            cin >> board[i][j];
    
    
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
        {
            memset(visited, false, sizeof(visited));
            visited[i][j] = true;
            find(i, j, 1, board[i][j]);
        }
    
    other_shape();
    cout << answer;
    return 0;
}
