#include <iostream>
using namespace std;

int N, M, r, c, d, board[51][51], answer = 0;
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};

int reverse_dir(int d)
{
    if(d == 0) return 2;
    if(d == 2) return 0;
    if(d == 1) return 3;
    if(d == 3) return 1;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> N >> M >> r >> c >> d;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cin >> board[i][j];
        }
    }
    
    while (1)
    {
        board[r][c] = 2; answer++;
        
        int nr = 0, nc = 0;
        bool find = false;
        while (1)
        {
            for(int i = 0; i < 4; i++)
            {
                if(d == 0) d = 3;
                else d--;
                nr = r + dr[d];
                nc = c + dc[d];
                
                if(!(nr < 0 || nr > N-1 || nc < 0 || nc > M-1) &&
                   board[nr][nc] == 0)
                {
                    r = nr; c = nc;
                    find = true; break;
                }
            }
            if(find) break;
            
            r += dr[reverse_dir(d)]; c += dc[reverse_dir(d)];
            
            if(r < 0 || r > N-1 || c < 0 || c > M-1 ||
                board[r][c] == 1)
            {
                cout << answer;
                return 0;
            }
        }
    }
    
    return 0;
}
