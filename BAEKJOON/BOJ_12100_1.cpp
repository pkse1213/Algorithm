/*
 BAEKJOON
 12100. 2048 (Easy)
 
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#define MAX 21
using namespace std;
int input[MAX][MAX];
int N;
int dr[4] = {1, -1, 0, 0}; // 상, 하, 좌 , 우
int dc[4] = {0, 0, -1, 1};
int res = 0;

void dfs(int cnt, int dir, int map[MAX][MAX]){
    if(cnt > 5) return;
    
    int tmp[MAX][MAX] = {0};
    queue<int> q;
    int before_idx, before_num;
    int i;
    
    // 위쪽으로 한번 이동
    if(dir == 0){
        for(int c=0; c<N; c++){
            before_idx = 0;
            before_num = map[0][c];
            
            for(int r=1; r<N; r++){
                // 1) 다른 경우
                if(map[r][c] != before_num) {
                    if(r != N-1){
                        // 현재가 0인데, 마지막 숫자가 아님
                        // (2) (0) 4 8
                        // (2) 0 0 (0) 0
                        if(map[r][c] == 0){
                            continue; // 검사 X
                        }
                        
                        // 이전 숫자가 0이든 뭐든, 현재가 마지막은 아님
                        // 현재 숫자를 이전 숫자로 바꿔준다
                        // (0) (2) 4
                        // (2) 0 (4) 8
                        // (4) (8) 2
                        else {
                            before_num = map[r][c];
                            before_idx = r;
                        }
                    }
                    
                    // 이전 숫자가 0이든 어떤 숫자이든, 현재가 마지막 숫자이면
                    // (2) 0 (4)
                    // (2) 0 0 (0)
                    // (0) (2)
                    else {
                        // 이전 숫자가 0이 아니면 push
                        if(before_num != 0){
                            q.push(before_num);
                        }
                        // 현재 마지막 숫자가 0이 아니면 Push
                        if(map[r][c] != 0){
                            q.push(map[r][c]);
                        }
                    }
                }
                
                
                // 2) 같은 경우
                else if(map[r][c] == before_num) {
                    // 같은데 (0) (0)
                    if(map[r][c] == 0) {
                        continue; // 검사 X
                    }
                    map[before_idx][c] += map[r][c];
                    q.push(map[before_idx][c]);
                    res = max(map[before_idx][c], res);
                    map[r][c] = 0;
                    
                    before_num = map[r][c];
                    before_idx = r;
                }
            }
            
            i = 0;
            while(!q.empty()) {
                tmp[i][c] = q.front();
                q.pop();
                i++;
            }
        }
    }
    
    // 아래쪽으로 한번 이동
    if(dir == 1){
        for(int c=0; c<N; c++){
            before_idx = N-1;
            before_num = map[N-1][c];
            
            for(int r=N-2; r>=0; r--){
                // 1) 다른 경우
                if(map[r][c] != before_num) {
                    if(r != 0){
                        // 현재가 0인데, 마지막 숫자가 아님
                        if(map[r][c] == 0){
                            continue; // 검사 X
                        }
                        else {
                            before_num = map[r][c];
                            before_idx = r;
                        }
                    }
                    
                    // 이전 숫자가 0이든 어떤 숫자이든, 현재가 마지막 숫자이면
                    else {
                        // 이전 숫자가 0이 아니면 push
                        if(before_num != 0){
                            q.push(before_num);
                        }
                        // 현재 마지막 숫자가 0이 아니면 Push
                        if(map[r][c] != 0){
                            q.push(map[r][c]);
                        }
                    }
                    
                }
                // 2) 같은 경우
                else if(map[r][c] == before_num) {
                    // 같은데 (0) (0)
                    if(map[r][c] == 0) {
                        continue; // 검사 X
                    }
                    map[before_idx][c] += map[r][c];
                    q.push(map[before_idx][c]);
                    res = max(map[before_idx][c], res);
                    map[r][c] = 0;
                    
                    before_num = map[r][c];
                    before_idx = r;
                }
            }
            
            i = N-1;
            while(!q.empty()) {
                tmp[i][c] = q.front();
                q.pop();
                i--;
            }
        }
    }
    
    // 왼쪽으로 한번 이동
    if(dir == 2){
        for(int r=0; r<N; r++){
            before_idx = 0;
            before_num = map[r][0];
            
            // 왼쪽 이동이니깐 r은 픽스다. 변경 안된다.
            for(int c=1; c<N; c++){
                // 1) 다른 경우
                if(map[r][c] != before_num) {
                    if(r != N-1){
                        // 현재가 0인데, 마지막 숫자가 아님
                        if(map[r][c] == 0){
                            continue; // 검사 X
                        }
                        
                        else {
                            before_num = map[r][c];
                            before_idx = c;
                        }
                    }
                    
                    // 이전 숫자가 0이든 어떤 숫자이든, 현재가 마지막 숫자이면
                    else {
                        // 이전 숫자가 0이 아니면 push
                        if(before_num != 0){
                            q.push(before_num);
                        }
                        // 현재 마지막 숫자가 0이 아니면 Push
                        if(map[r][c] != 0){
                            q.push(map[r][c]);
                        }
                    }
                    
                }
                // 2) 같은 경우
                else if(map[r][c] == before_num) {
                    // 같은데 (0) (0)
                    if(map[r][c] == 0) {
                        continue; // 검사 X
                    }
                    map[r][before_idx] += map[r][c];
                    q.push(map[r][before_idx]);
                    res = max(map[r][before_idx], res);
                    map[r][c] = 0;
                    
                    before_num = map[r][c];
                    before_idx = c;
                }
            }
            
            
            i = 0;
            while(!q.empty()) {
                tmp[r][i] = q.front();
                q.pop();
                i++;
            }
        }
    }
    
    // 오른쪽으로 한번 이동
    if(dir == 3){
        for(int r=0; r<N; r++){
            before_idx = N-1;
            before_num = map[r][N-1];
            
            // 왼쪽 이동이니깐 r은 픽스다. 변경 안된다.
            for(int c=N-2; c>=0; c--){
                // 1) 다른 경우
                if(map[r][c] != before_num) {
                    if(r != 0){
                        // 현재가 0인데, 마지막 숫자가 아님
                        if(map[r][c] == 0){
                            continue; // 검사 X
                        }
                        
                        else {
                            before_num = map[r][c];
                            before_idx = c;
                        }
                    }
                    
                    // 이전 숫자가 0이든 어떤 숫자이든, 현재가 마지막 숫자이면
                    else {
                        // 이전 숫자가 0이 아니면 push
                        if(before_num != 0){
                            q.push(before_num);
                        }
                        // 현재 마지막 숫자가 0이 아니면 Push
                        if(map[r][c] != 0){
                            q.push(map[r][c]);
                        }
                    }
                    
                }
                // 2) 같은 경우
                else if(map[r][c] == before_num) {
                    // 같은데 (0) (0)
                    if(map[r][c] == 0) {
                        continue; // 검사 X
                    }
                    map[r][before_idx] += map[r][c];
                    q.push(map[r][before_idx]);
                    res = max(map[r][before_idx], res);
                    map[r][c] = 0;
                    
                    before_num = map[r][c];
                    before_idx = c;
                }
                
            }
            i = N-1;
            while(!q.empty()) {
                tmp[r][i] = q.front();
                q.pop();
                i--;
            }
        }
    }
    
    //    for(int i=0; i<N; i++){
    //        for(int j=0; j<N; j++){
    //            cout << tmp[i][j] << "\t";
    //        }
    //        cout << endl;
    //    }
    //    cout << endl;
    //
    //    dfs(cnt+1, dir+1, tmp_2);
    for(int i=0; i<4; i++){
        dfs(cnt+1, i, tmp);
    }
}


int main(int argc, char** argv){
    cin >> N;
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> input[i][j];
            if(input[i][j] > res)
                res = max(res, input[i][j]);
        }
    }
    
    for(int i=0; i<4; i++){
        dfs(1, i, input);
    }
    cout << res << endl;
    //     dfs(1, 0, map);
    
    return 0;
}
