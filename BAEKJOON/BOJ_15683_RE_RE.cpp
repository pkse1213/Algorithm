/*
 15683. 감시 다시풀기의 다시풀기
 */
#include <iostream>
#include <vector>
using namespace std;

struct cctv_info {
    int r, c, type, kind, round, plus;
};
int N, M, board[9][9], ans = 987654321;
vector<cctv_info> cctv;
int check_num[5] = { 1, 2, 2, 3, 4 };
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};

void copy_map(int origin[9][9], int room[9][9])
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            room[i][j] = origin[i][j];
}

void monitor(int n, int origin[9][9]) {
    if(n == cctv.size()) {
        int cnt = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(origin[i][j] == 0) cnt++;
            }
        }
        if(cnt < ans) ans = cnt;
        return;
    }
    cctv_info tv = cctv[n];
    // s = 시작 방향
    for(int s = 0; s < 4; s++) {
        int room[9][9];
        copy_map(origin, room);
        int r = tv.r;
        int c = tv.c;
        int d = s;
        
        for(int i = 0; i < check_num[tv.type]; i++) {
            d %= 4;
            int nr = r;
            int nc = c;
            while(1) {
                nr += dr[d];
                nc += dc[d];
                
                if(nr < 0 || nr > N-1 || nc < 0 || nc > M-1 ||
                   room[nr][nc] == 6) break;
                else if(room[nr][nc] == 0) {
                    room[nr][nc] = 8;
                }
            }
            d++;
            if(tv.type == 1) d++;
        }
        monitor(n+1, room);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> board[i][j];
            if(1 <= board[i][j] && board[i][j] <= 5) {
                cctv_info tmp;
                tmp.r = i; tmp.c = j; tmp.type = board[i][j] - 1;
                cctv.push_back(tmp);
            }
        }
    }
    
    monitor(0, board);
    cout << ans;
        
    return 0;
}
