/*
 15685. 드래곤커브 다시풀기
 
 규칙을 찾자.
 */
#include <iostream>
#include <vector>
using namespace std;

int T, x, y, d, g;
int dr[4] = {0,-1,0,1};
int dc[4] = {1,0,-1,0};
bool board[101][101];
vector<int> dir;

int main()
{
    cin >> T;
    
    for(int i = 0; i < T; i++)
    {
        cin >> y >> x >> d >> g;
        dir.clear();
        dir.push_back(d);
        board[x][y] = true;
        x += dr[d];
        y += dc[d];
        board[x][y] = true;
        for(int t = 1; t <= g; t++)
        {
            int s = dir.size();
            for(int i = s-1; i >= 0; i--)
            {
                int nd = (dir[i]+1)%4;
                x += dr[nd];
                y += dc[nd];
                board[x][y] = true;
                dir.push_back(nd);
            }
        }
    
    int cnt = 0;
    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            if(board[i][j] && board[i+1][j] && board[i][j+1] && board[i+1][j+1])
                cnt++;
        }
    }
    
    cout << cnt;
    return 0;
    
}
