
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#define MAX 21
using namespace std;
int map[MAX][MAX];
int N;
int dr[4] = {1, -1, 0, 0}; // 상, 하, 좌 , 우
int dc[4] = {0, 0, -1, 1};
int res = 0;

void dfs(int cnt, int dir, int tmp[MAX][MAX]){
    if(cnt > 5) return;
    
    int tmp_2[MAX][MAX] = {0};
    queue<int> nums;
    int before_idx, before_num;
    int i;
    
    // 위쪽으로 한번 이동
    if(dir == 0){
        for(int c=0; c<N; c++){
            before_idx = 0;
            before_num = tmp[0][c];
            
            for(int r=1; r<N; r++){
                // 1) 다른 경우
                if(tmp[r][c] != before_num) {
                    if(before_num != 0){
                        nums.push(before_num);
                    }
                    if(r == N-1){
                        nums.push(tmp[r][c]);
                    } else {
                        before_num = tmp[r][c];
                        before_idx = r;
                    }
                }
                // 2) 같은 경우
                else if(tmp[r][c] == before_num && tmp[r][c] != 0) { // 같은 경우
                    tmp[before_idx][c] += tmp[r][c];
                    nums.push(tmp[before_idx][c]);
                    res = max(tmp[before_idx][c], res);
                    tmp[r][c] = 0;
                    
                    before_num = tmp[r][c];
                    before_idx = r;
                }
            }
            
            i = 0;
            while(!nums.empty()) {
                tmp_2[i][c] = nums.front();
                nums.pop();
                i++;
            }
        }
    }
    
    // 아래쪽으로 한번 이동
    if(dir == 1){
        for(int c=0; c<N; c++){
            before_idx = N-1;
            before_num = tmp[N-1][c];
            
            for(int r=N-2; r>=0; r--){
                // 1) 다른 경우
                if(tmp[r][c] != before_num) {
                    if(before_num != 0){
                        nums.push(before_num);
                    }
                    if(r == 0){
                        nums.push(tmp[r][c]);
                    } else {
                        before_num = tmp[r][c];
                        before_idx = r;
                    }
                }
                // 2) 같은 경우
                else if(tmp[r][c] == before_num && tmp[r][c] != 0) { // 같은 경우
                    tmp[before_idx][c] += tmp[r][c];
                    nums.push(tmp[before_idx][c]);
                    res = max(tmp[before_idx][c], res);
                    tmp[r][c] = 0;
                    
                    before_num = tmp[r][c];
                    before_idx = r;
                }
            }
            
            i = N-1;
            while(!nums.empty()) {
                tmp_2[i][c] = nums.front();
                nums.pop();
                i--;
            }
        }
    }
    
    // 왼쪽으로 한번 이동
    if(dir == 2){
        for(int r=0; r<N; r++){
            before_idx = 0;
            before_num = tmp[r][0];
            
            // 왼쪽 이동이니깐 r은 픽스다. 변경 안된다.
            for(int c=1; c<N; c++){
                // 1) 다른 경우
                if(tmp[r][c] != before_num) {
                    if(before_num != 0){
                        nums.push(before_num);
                    }
                    if(c == N-1){
                        nums.push(tmp[r][c]);
                    } else {
                        before_num = tmp[r][c];
                        before_idx = c;
                    }
                }
                // 2) 같은 경우
                else if(tmp[r][c] == before_num && tmp[r][c] != 0) { // 같은 경우
                    tmp[r][before_idx] += tmp[r][c];
                    nums.push(tmp[r][before_idx]);
                    res = max(tmp[r][before_idx], res);
                    tmp[r][c] = 0;
                    
                    before_num = tmp[r][c];
                    before_idx = c;
                }
            }
            i = 0;
            while(!nums.empty()) {
                tmp_2[r][i] = nums.front();
                nums.pop();
                i++;
            }
        }
    }
    
    
    // 오른쪽으로 한번 이동
    if(dir == 3){
        for(int r=0; r<N; r++){
            before_idx = N-1;
            before_num = tmp[r][N-1];
            
            // 왼쪽 이동이니깐 r은 픽스다. 변경 안된다.
            for(int c=N-2; c>=0; c--){
                // 1) 다른 경우
                if(tmp[r][c] != before_num) {
                    if(before_num != 0){
                        nums.push(before_num);
                    }
                    if(c == 0){
                        nums.push(tmp[r][c]);
                    } else {
                        before_num = tmp[r][c];
                        before_idx = c;
                    }
                }
                // 2) 같은 경우
                else if(tmp[r][c] == before_num && tmp[r][c] != 0) { // 같은 경우
                    tmp[r][before_idx] += tmp[r][c];
                    nums.push(tmp[r][before_idx]);
                    res = max(tmp[r][before_idx], res);
                    tmp[r][c] = 0;
                    
                    before_num = tmp[r][c];
                    before_idx = c;
                }
            }
            
            i = N-1;
            while(!nums.empty()) {
                tmp_2[r][i] = nums.front();
                nums.pop();
                i--;
            }
        }
    }
    
    //    for(int i=0; i<N; i++){
    //        for(int j=0; j<N; j++){
    //            cout << tmp_2[i][j];
    //        }
    //        cout << endl;
    //    }
    //    cout << endl;
    
    //    dfs(cnt+1, dir+1, tmp_2);
    for(int i=0; i<4; i++){
        dfs(cnt+1, i, tmp_2);
    }
}


int main(int argc, char** argv){
    cin >> N;
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> map[i][j];
            if(map[i][j] > res)
                res = max(res, map[i][j]);
        }
    }
    
    for(int i=0; i<4; i++){
        dfs(1, i, map);
    }
    cout << res << endl;
    //     dfs(1, 0, map);
    
    return 0;
}
