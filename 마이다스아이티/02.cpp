#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <string>
#include <deque>
#include <stack>
#include <map>
#include <sstream>
#include <regex>
#include <math.h>
#define MAX 11
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

double angle(int x1,int y1, int x2,int y2){
    double dx = x1 - x2;
    double dy = y1 - y2;
    double rad= atan2(dy, dx);
    double d = (rad*180)/M_PI;
    return abs(d);
}

int dis(int r, int c, int rr, int cc)
{
    int dr = abs(r-rr);
    int dc = abs(c-cc);
    return sqrt(dr*dr + dc*dc);
}

//스킬을 사용하기 위해 마우스로 클릭한 위치의 좌표 x, y, 스킬의 공격 거리 r, 스킬의 공격 범위 각도 d와

int solution(int x, int y, int r, int d, vector<vector<int>> target)
{
    int answer = 0;
    
    for(int i = 0; i < target.size(); i++)
    {
        int rr = target[i][0];
        int cc = target[i][1];
        
        int a1 = angle(0,0, rr, cc);
        int a2 = angle(0,0, x, y);
        int aa = abs(a1-a2);
        if(aa > 180) aa -= 180;
        if(dis(0,0,rr,cc) <= r && aa <= d)
        {
            answer++;
        }
    }
    
    return answer;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << solution(-1, 2, 2, 60, {{0, 1}, {-1, 1}, {1, 0}, {-2, 2}});
                     
    return 0;
}
