/*

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <math.h>
#define MAX 101
using namespace std;

struct node {
    int r, c;
    node();
    node(int _r, int _c): r(_r), c(_c) {}
};

int map[MAX][MAX] ; // 0은 아무것도 없음, 1은 뱀, 2는 사과

int dr[4] = {0, 1, 0, -1}; // 우, 하, 좌, 상
int dc[4] = {1, 0, -1, 0};

int main(int argc, char** argv)
{
    
    
    return 0;
}
