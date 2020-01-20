/*
 BAEKJOON
 5373. 큐빙
 
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <math.h>
#define MAX 50
using namespace std;
struct Node {
    int r, c;
    Node();
    Node(int _r, int _c): r(_r), c(_c) {}
};
int map[4][4][7];
char side, dir;
int idx[4];
int n, now_side;

void setting()
{
    // U: 윗 면, D: 아랫 면, F: 앞 면, B: 뒷 면, L: 왼쪽 면, R: 오른쪽 면이다.
    // +인 경우에는 시계 방향 (그 면을 바라봤을 때가 기준), -인 경우에는 반시계 방향
    switch (side) {
        case 'U':
            if(dir == '+') idx[0] = 4; idx[1] = 6; idx[2] = 3; idx[3] = 5;
            if(dir == '-') idx[0] = 4; idx[1] = 5; idx[2] = 3; idx[3] = 6;
            break;
            
        case 'D':
            if(dir == '+') idx[0] = 3; idx[1] = 6; idx[2] = 4; idx[3] = 5;
            if(dir == '-') idx[0] = 3; idx[1] = 5; idx[2] = 4; idx[3] = 6;
            break;
            
        case 'F':
            if(dir == '+') idx[0] = 1; idx[1] = 6; idx[2] = 2; idx[3] = 5;
            if(dir == '-') idx[0] = 1; idx[1] = 5; idx[2] = 2; idx[3] = 6;
            break;
            
        case 'B':
            if(dir == '+') idx[0] = 1; idx[1] = 5; idx[2] = 2; idx[3] = 6;
            if(dir == '-') idx[0] = 1; idx[1] = 6; idx[2] = 2; idx[3] = 5;
            break;
            
        case 'L':
            if(dir == '+') idx[0] = 1; idx[1] = 3; idx[2] = 2; idx[3] = 4;
            if(dir == '-') idx[0] = 1; idx[1] = 4; idx[2] = 2; idx[3] = 3;
            break;
            
        case 'R':
            if(dir == '+') idx[0] = 1; idx[1] = 4; idx[2] = 2; idx[3] = 3;
            if(dir == '-') idx[0] = 1; idx[1] = 3; idx[2] = 2; idx[3] = 4;
            break;
            
        default:
            break;
    }
}

void rotate()
{
    // 기준면 회전
    char tmp1, tmp2, tmp3;
    tmp1 = map[1][3][now_side];
    tmp2 = map[1][2][now_side];
    tmp3 = map[1][1][now_side];
    
    if(dir == '+')
    {
        tmp1 = map[1][3][now_side];
        tmp2 = map[1][2][now_side];
        tmp3 = map[1][1][now_side];
        
        map[1][3][now_side] = map[1][1][now_side];
        map[1][2][now_side] = map[2][1][now_side];
        map[1][1][now_side] = map[3][1][now_side];
        
        map[1][1][now_side] = map[3][1][now_side];
        map[2][1][now_side] = map[3][2][now_side];
        map[3][1][now_side] = map[3][3][now_side];
        
        map[3][1][now_side] = map[3][3][now_side];
        map[3][2][now_side] = map[2][3][now_side];
        map[3][3][now_side] = map[1][3][now_side];
        
        map[3][3][now_side] = tmp1;
        map[2][3][now_side] = tmp2;
        map[1][3][now_side] = tmp3;
        
        tmp1 = map[3][1][idx[0]];
        tmp2 = map[3][2][idx[0]];
        tmp3 = map[3][3][idx[0]];
        
        map[3][1][idx[0]] = map[1][1][idx[1]];
        map[3][2][idx[0]] = map[2][1][idx[1]];
        map[3][3][idx[0]] = map[3][1][idx[1]];
        
        map[1][1][idx[1]] = map[1][3][idx[2]];
        map[2][1][idx[1]] = map[1][2][idx[2]];
        map[3][1][idx[1]] = map[1][1][idx[2]];
        
        map[1][3][idx[2]] = map[3][3][idx[3]];
        map[1][2][idx[2]] = map[2][3][idx[3]];
        map[1][1][idx[2]] = map[1][3][idx[3]];
        
        map[3][3][idx[3]] = tmp1;
        map[2][3][idx[3]] = tmp2;
        map[1][3][idx[3]] = tmp3;
        
        
    }
    else if(dir == '-')
    {
        tmp1 = map[1][3][now_side];
        tmp2 = map[1][2][now_side];
        tmp3 = map[1][1][now_side];
        
        map[1][1][now_side] = map[1][3][now_side];
        map[1][2][now_side] = map[2][3][now_side];
        map[1][3][now_side] = map[3][3][now_side];
        
        map[1][3][now_side] = map[3][3][now_side];
        map[2][3][now_side] = map[3][2][now_side];
        map[3][3][now_side] = map[3][1][now_side];
        
        map[3][3][now_side] = map[3][1][now_side];
        map[3][2][now_side] = map[2][1][now_side];
        map[3][1][now_side] = map[1][1][now_side];
        
        map[3][1][now_side] = tmp3;
        map[2][1][now_side] = tmp2;
        map[1][1][now_side] = tmp1;
    }
}

void input()
{
    // 윗 면은 흰색, 아랫 면은 노란색, 앞 면은 빨간색, 뒷 면은 오렌지색, 왼쪽 면은 초록색, 오른쪽 면은 파란색
    // 흰색은 w, 노란색은 y, 빨간색은 r, 오렌지색은 o, 초록색은 g, 파란색은 b.
    char colors[7] = {' ', 'w', 'y', 'r', 'o', 'g', 'b'};
    for(int k=1; k<=6; k++)
        for(int i=1; i<=3; i++)
            for(int j=1; j<=3; j++)
               map[i][j][k] = colors[k];
    
    cin >> n ;
    for(int i=1; i<=n; i++)
    {
        scanf("%c%c", &side, &dir);
        setting();
        rotate();
    }
}

int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case)
    {
        input();
    }
    return 0;
}
