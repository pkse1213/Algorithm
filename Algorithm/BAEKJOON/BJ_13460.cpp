/*
 BAEKJOON
 13460. 구슬 탈출 2
 
 <주의할 점>
 1. 빨간공과 파란공의 위치만 저장해두고, 지도에 없다고 생각해도 된다.
 2. 한 방향으로 굴렸는데, 파란공과 빨간공이 겹쳐지질 때
    - 더 많이 이동한 공이 한칸 뒤로 간다
 3. 다음 방향을 정할 때, 예외 케이스
    1) 현재 방향은 확인할 필요 없다
    2) 방금 오른쪽으로 굴렸다 -> 다음 왼쪽으로 굴린다
        => 의미 없음 : 이전 상태로 되돌리는 것 뿐, 확인할 필요 없다
 4. 지도의 공 위치를 직접 수정하는 것이 아니라,
    다음 공 위치를 가지고 다니면서 재귀함수로 이동시키고, 상태 확인하며 체크
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#define MAX 11
using namespace std;

struct node {
    int r,c;
    node() {}
    node(int _r, int _c) : r(_r), c(_c) {}
};

int N,M;
char map[MAX][MAX];

int dr[4] = {1, -1, 0, 0}; // 상, 하, 좌 , 우
int dc[4] = {0, 0, -1, 1};
int answer = 11;

node red, blue;

// 쉽게 생각나지 않았던 부분!!!!!!!!!
// 빨간공, 파란공이 겹쳤을 때 이동량 리턴
int move_dist(int r, int nr, int c, int nc) {
    return abs(nr - r) + abs(nc - c);
}

int inverse_dir(int crt_dir){
    if(crt_dir == 0) return 1;
    else if(crt_dir == 1) return 0;
    else if(crt_dir == 2) return 3;
    else return 2;
}

// dir 방향으로 한번 이동하는 것
void move_ball(int cnt, int dir, node R, node B){
    
    // 10번 이동했거나, 이미 나온 가장 작은 횟수보다 클 경우 그만!
    if(cnt > 10 || cnt >= answer){
        return;
    }
    
    bool flag_R = false;
    bool flag_B = false;
    
    // 파란공
    // dir 방향으로 벽이 나올때까지 이동
    int nBr = B.r;
    int nBc = B.c;
    
    while(1){
        // 체크부터 한다
        // 구멍에 빠짐
        if(map[nBr][nBc] == 'O') {
            flag_B = true;
            break;
        }
        // 벽을 만남, 멈춤
        if(map[nBr][nBc] == '#') {
            break;
        }
        // 아니면 계속 그 방향으로 이동
        nBr += dr[dir];
        nBc += dc[dir];
    }
    
    // 벽으로 이동했을 때 whlie문을 빠져나왔기 때문에 한칸 뒤로 가줘야 함 !!!!
    nBr -= dr[dir];
    nBc -= dc[dir];
    
    
    // 파란공이 동시에 빠지건, 혼자 빠지건 실패!
    if(flag_B) return;
    
    // 빨간공
    // dir 방향으로 벽이 나올때까지 이동
    int nRr = R.r;
    int nRc = R.c;
    
    while(1){
        // 체크부터 한다
        // 구멍에 빠짐
        if(map[nRr][nRc] == 'O') {
            flag_R = true;
            break;
        }
        // 벽을 만남, 멈춤
        if(map[nRr][nRc] == '#') {
            break;
        }
        // 아니면 계속 그 방향으로 이동
        nRr += dr[dir];
        nRc += dc[dir];
    }
    
    // 벽으로 이동했을 때 whlie문을 빠져나왔기 때문에 한칸 뒤로 가줘야 함 !!!!
    nRr -= dr[dir];
    nRc -= dc[dir];
    
    
    if(flag_R){
        answer = min(answer, cnt);
    }
    
    // 빨간공, 파란공이 겹쳤을 때
    // 이동량이 더 큰 공이 한칸 이전 단계로 돌아간다
    if(nBr == nRr && nBc == nRc) {
        if(move_dist(B.r, nBr, B.c, nBc) > move_dist(R.r, nRr, R.c, nRc)) {
            nBr -= dr[dir];
            nBc -= dc[dir];
        }
        else{
            nRr -= dr[dir];
            nRc -= dc[dir];
        }
    }
    
    // 다음 방향으로 이동해야 하는데,
    // 현재 이동한 방향, 현재 이동한 방향의 반대방향으로는 이동하지 않음
    for(int i=0; i<4; i++){
        if(i == dir || i == inverse_dir(dir))
            continue;
        
        // 재귀
        move_ball(cnt+1, i, node(nRr, nRc), node(nBr, nBc));
    }
    
}

int main(int argc, char** argv)
{
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> map[i][j];
            
            if(map[i][j] == 'R') {
                red = node(i,j);
                map[i][j] = '.';
            }
            if(map[i][j] == 'B') {
                blue = node(i,j);
                map[i][j] = '.';
            }
        }
    }
    
    // 시작하는 방향이 4가지
    for(int dir=0; dir<4; dir++){
        move_ball(1, dir, red , blue);
    }
    
    if (answer > 10) answer = -1;
    
    cout << answer << endl;
    
    return 0;
}
