/*
 BAEKJOON
 17143. 낚시왕
 
 시간초과..^^
*/

#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 101
using namespace std;

//(r, c)는 상어의 위치, s는 속력, d는 이동 방향, z는 크기
struct shark {
    int r, c, s, d, z;
    shark() {}
    shark(int _r, int _c, int _s, int _d, int _z): r(_r), c(_c), s(_s), d(_d), z(_z) {}
};

int n, m, k;
int x, y, s, d, z;
int dr[5] = { 0, -1, 1, 0, 0 }; // 상 하 우 좌
int dc[5] = { 0, 0, 0, 1, -1 };
int answer = 0;
vector<shark> origin[MAX][MAX];
vector<shark> sh;

void input()
{
    cin >> n >> m >> k;
    for(int i=0; i<k; i++)
    {
        cin >> x >> y >> s >> d >> z;
        sh.push_back(shark(x, y, s, d, z));
        origin[x][y].push_back(sh.back());
    }
}

int change(int dir)
{
    switch (dir) {
        case 1:
            return 2;
        case 2:
            return 1;
        case 3:
            return 4;
        case 4:
            return 3;
        default:
            return 0;
    }
}

int main(int argc, char** argv)
{
    input();

    for(int j=1; j<=m; j++) // 낚시왕이 좌표의 맨 오른쪽으로 이동할 때까지
    {
        vector<shark> map[n+1][m+1];
        int dieR = -1;
        int dieC = -1;
        // 상어 잡기
        for(int r=1; r<=n; r++)
        {
            if(origin[r][j].size() > 0)
            {
                answer += origin[r][j].front().z;
                origin[r][j].clear();
                dieR = r;
                dieC = j;
                break;
            }
        }
        
        // 현재 살아있는 상어 수만큼 반복
        for(int i=0; i<sh.size(); i++)
        {
            // 먼저 죽인 상어이면
            if(sh[i].r == dieR && sh[i].c == dieC)
                continue;
            
            int nr = sh[i].r;
            int nc = sh[i].c;
            
            // 상어의 속력(횟수)만큼 이동할 건데,
            // 벽을 만나면 상어의 방향을 바꾸어주고 다시 이동
            for(int q=0; q<sh[i].s; q++)
            {
                nr += dr[sh[i].d];
                nc += dc[sh[i].d];
                if(nr < 1 || nc < 1 || nr > n || nc > m)
                {
                    nr -= dr[sh[i].d];
                    nc -= dc[sh[i].d];
                    // 방향 바꿔! 위치 갱신
                    sh[i].d = change(sh[i].d);
                    --q;
                    continue;
                }
            }
            
            // 좌표 갱신
            sh[i].r = nr;
            sh[i].c = nc;
           
            // 그 좌표에 상어가 한마리라도 있다면
            if(map[nr][nc].size() > 0)
            {
                // 기존에 있는 상어의 크기보다 작으면 지도에 추가 X
                if(sh[i].z < map[nr][nc].front().z){
                    continue;
                }
                // 더 크다면 기존에 있는 상어 삭제하고 현재 상어를 추가
                else
                {
                    map[nr][nc].clear();
                    map[nr][nc].push_back(sh[i]);
                }
            }
            // 좌표에 상어가 하나도 없다면
            else
            {
                map[nr][nc].push_back(sh[i]);
            }
        }
        
        // 살아있던 상어 모두 삭제
        sh.clear();
        
        for(int r=1; r<=n; r++)
        {
            for(int c=1; c<=m; c++)
            {
                origin[r][c] = map[r][c];
                if(map[r][c].size() == 0)
                {
//                    if(r == dieR && c == dieC)
//                        cout << "✅" << '\t';
//                    else
//                        cout << "-" << '\t';
                    continue;
                }
                sh.push_back(origin[r][c].front());
//                cout << sh.back().z << '\t';
            }
//            cout << endl;
        }
//        cout << endl;
    }
    cout << answer;

    return 0;
}
