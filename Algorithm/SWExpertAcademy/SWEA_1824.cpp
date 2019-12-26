/*
 SW Expert Academy

 */
#include <iostream>
using namespace std;
int T,R,C;
char map[21][21];
int chk[21][21][16][4]; // 행, 열, 메모리 값, 방향(상0, 하1, 좌2, 우3)
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool dfs(int r, int c, int memory, int d){ // 행, 열, 메모리 값, 방향(상0, 하1, 좌2, 우3)
    bool res = false;
    int ch = map[r][c];
    
    if(ch == '@') return true;
    else if('0' <= ch && ch <= '9') memory = ch - '0';
    else if(ch == '<' || (ch == '_' && memory != 0)) d = 2;
    else if(ch == '>' || (ch == '_' && memory == 0)) d = 3;
    else if(ch == '^' || (ch == '|' && memory != 0)) d = 0;
    else if(ch == 'v' || (ch == '|' && memory == 0)) d = 1;
    else if(ch == '+') memory = (++memory) % 16;
    else if(ch == '-') memory = (memory == 0) ? 15 : memory++;
    // 머물러 있는 상태에서 방향, 메모리값 변경
    
    // 변경된 방향, 메모리값 이후 방문한적 있는지 체크
    // 있으면 무한루프 -> false
    // 없다면 방문 기록
    if(chk[r][c][memory][d] == 1) return false;
    else chk[r][c][memory][d] = 1;
    
    
    
    int nr = r + dr[d];
    int nc = c + dc[d];
    if(nr == 0) nr = R;
    else if(nr == R+1) nr = 1;
    if(nc == 0) nc = C;
    else if(nc == C+1) nc = 1;
    
    if(ch == '?'){
        for(int i=0; i<4; i++){
            
        }
        
    }
    
    
    
    
}



int SWEA_1824() {
    scanf("%d", &T);
    
    for(int t=1; t<=T; t++){
        scanf("%d %d", &R, &C);
        
        for(int i=1; i<=R; i++){
            for(int j=1; j<=C; j++){
                scanf("%s", &map[i][j]);
            }
            
        }
        
        
    }
    return 0;
}
