/*
 SW Expert Academy
 1767. 프로세서 연결하기
 
 DFS + 백트래킹
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#define MAX 13
using namespace std;

struct node{
    int r, c;
    
    node() {}
    node(int _r, int _c) : r(_r), c(_c) {}
};

int T, N;
int map[MAX][MAX];
int max_core, min_line; // 연결된 코어의 최대 갯수, 연결된 전선의 최소 갯수
vector<node> core;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

// 코어 배열의 인덱스, 전선 연결한 코어 갯수, 전선의 갯수
void dfs_back_tracking(int idx, int cnt_core, int cnt_line){
    // 주의! idx == core.size()-1 아님!
    if(idx == core.size()) {
        // 더 많은 코어가 연결되었을 경우
        if(cnt_core > max_core){
            max_core = cnt_core;
            min_line = cnt_line;
        }
        // 코어 연결갯수는 같지만 더 적은 전선 체크
        else if(cnt_core == max_core){
            min_line = min(cnt_line, min_line);
        }
        
        return;
    }
    
    for(int i=0; i<4; i++){
        vector<node> tmp; // 전선을 설치할 node 집합
        node crt_core = core[idx]; // 현재 검사 코어
        bool chk = false; // 설치 가능 유무
        int nr = crt_core.r;
        int nc = crt_core.c;
        
        // 모서리까지 이동하며 전선을 설치할 수 있는지 체크
        while(1){
            // 모서리면 반복문 탈출
            if(nr == 0 || nc == 0 || nr == N-1 || nc == N-1){
                chk = true;
                break;
            }
            
            // 한 방향으로 계속 이동
            nr += dr[i];
            nc += dc[i];
            
            if(map[nr][nc] == 0){ // 전선 설치 가능하면 추가
                tmp.push_back(node(nr, nc));
            }
            else { // 아니면 반복문 탈출
                break;
            }
        }
        
        // 설치 가능하면
        if(chk) {
            for(int t=0; t<tmp.size(); t++){
                map[tmp[t].r][tmp[t].c] = 2;
            }
            // 재귀 (코어의 인덱스 +1, 코어 설치했으니깐 +1, 라인 수+tmp 개수
            dfs_back_tracking(idx+1, cnt_core+1, cnt_line+(int)tmp.size());
            
            // 되돌리기
            for(int t=0; t<tmp.size(); t++){
                map[tmp[t].r][tmp[t].c] = 0;
            }
        }
    }
    
    // 헷갈리는 부분!!!!!!!!!!!!!!!!!!!!!
    // 설치하지 않은 경우 + 설치했지만 되돌린 경우
    dfs_back_tracking(idx+1, cnt_core, cnt_line);
    
}


int main(int argc, char** argv)
{
    int test_case;
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case){
        // 코어 초기화
        core.clear();
        
        cin >> N;
        for(int r=0; r<N; r++){
            for(int c=0; c<N; c++){
                cin >> map[r][c];
                
                if(map[r][c] == 1) {
                    // 모서리부분은 제외하고
                    if(r == 0 || c == 0 || r == N-1 || c == N-1)
                        continue;
                    
                    // 코어를 벡터에 추가
                    core.push_back(node(r,c));
                }
            }
        }
        
        max_core = 0;
        min_line = N*N;
        
        dfs_back_tracking(0, 0, 0);
        
        cout << "#" << test_case << " " << min_line << endl;
        
    }
    return 0;
}
