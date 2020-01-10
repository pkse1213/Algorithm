/*
 BAEKJOON
 15685. 드래곤 커브
 
*/

#include <iostream>
#include <vector>
#define MAX 101
using namespace std;


vector<int> curves;
bool map[MAX][MAX] = { false } ;
int n, x, y, d, g;
int dr[4] = { 0, -1, 0, 1 }; //  동 북 서 남
int dc[4] = { 1, 0, -1, 0 };
int answer = 0;

void input()
{
    curves.clear();
    cin >> x >> y >> d >> g;
    curves.push_back(d);
    map[y][x] = true;
}

void draw()
{
    for(int t=0; t<g; t++)
    {
        int size = (int)curves.size();
        for(int i=size-1; i>=0; i--)
        {
            int nd = curves[i];
            curves.push_back((nd+1)%4);
        }
    }

    int nr = y;
    int nc = x;
    for(int i=0; i<curves.size(); i++)
    {
        nr += dr[curves[i]];
        nc += dc[curves[i]];
        if(!(0 <= nr && nr <= 100 && 0 <= nc && nc <= 100)) break;
        map[nr][nc] = true;
    }
}

void dp()
{
    for(int i=0; i<MAX-1; i++){
        for(int j=0; j<MAX-1; j++)
        {
            if(map[i][j] && map[i+1][j] && map[i][j+1] && map[i+1][j+1])
                answer++;
        }
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
        draw();
    }
    dp();
    cout << answer << endl;
    return 0;
}
