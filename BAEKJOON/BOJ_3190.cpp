/*
 BAEKJOON
 3190. 뱀
 
 1) queue를 사용한 것
 - 배열을 사용했으면 체크할 때 배열을 모두 순회해야했다
 - 시간 체크 -> queue를 사용해서 맨 앞에 것만 체크하고 pop해주었다
 - 뱀 -> 꼬리가 먼저 들어오고, 꼬리를 삭제 해주므로 queue를 선택
 
 2) 문제를 제대로 안읽어서 좌표 확인을 잘못한 것
 
 */

#include <iostream>
#include <algorithm>
#include <queue>
#define MAX 101

using namespace std;
struct node {
    int r, c;
    node();
    node(int _r, int _c): r(_r), c(_c) {}
};

struct direction {
    int s;
    char d;
    direction();
    direction(int _s, char _d): s(_s), d(_d) {}
};

int K, N, L;
int r, c, s;
char d;
int map[MAX][MAX] {0}; // 0은 아무것도 없음, 1은 뱀, 2는 사과

queue<node> q_snake;
queue<direction> q_dir;
// 방향 정보를 배열이 아닌 queue로 사용한 이유
// 배열모두 순회해 보는 것이 아니라
// 맨 앞에 있는 방향 정보의 시간만 체크하면 되니깐
// 그리고 pop(선입 선출)해버리면 되니깐

int dr[4] = {0, 1, 0, -1}; // 우, 하, 좌, 상
int dc[4] = {1, 0, -1, 0};

int main(int argc, char** argv)
{
    cin >> N >> K;
    
    // 사과
    for(int i=0; i<K; i++){
        cin >> r >> c;
        map[r][c] = 2;
    }
    
    // 방향 전환 정보
    cin >> L;
    for(int i=0; i<L; i++){
        cin >> s >> d;
        q_dir.push(direction(s, d));
    }
    
    int cnt = 0;
    int now_dir = 0; // 방향 오른쪽으로
    // 뱀의 시작 위치 = (1,1)
    int nr = 1;
    int nc = 1;
    map[nr][nc] = 1;
    q_snake.push(node(nr,nc));
    
    while(1){
        cnt++;
        nr += dr[now_dir];
        nc += dc[now_dir];
        
        // 벽이거나, 뱀이거나 -> 탈출
        if(nr < 1 || nc < 1 || nr > N || nc > N || map[nr][nc] == 1) {
            break;
        }
        
        // 사과가 있으면 그냥 머리 추가
        if(map[nr][nc] == 2) {
            q_snake.push(node(nr,nc));
            map[nr][nc] = 1;
        }
        
        // 아무것도 없으면 꼬리 삭제 -> 꼬리 0으로
        // 꼬리가 제일 먼저 들어간 node이므로 pop하면 삭제된다
        else if(map[nr][nc] == 0) {
            q_snake.push(node(nr,nc));
            map[nr][nc] = 1;
            
            map[q_snake.front().r][q_snake.front().c] = 0;
            q_snake.pop();
        }
        
        // 방향 변경
        if(!q_dir.empty() && cnt == q_dir.front().s){
            if(q_dir.front().d == 'D') { // 오른쪽 90도
                now_dir = (now_dir+1) % 4;
            }
            else if(q_dir.front().d == 'L') { // 왼쪽 90도
                if(now_dir == 0){
                    now_dir = 3;
                }
                else {
                    now_dir -= 1;
                }
            }
            // 방향 변경하는 초가 지났으니 pop해준다
            q_dir.pop();
        }
        
    }
    
    cout << cnt;
    return 0;
}
