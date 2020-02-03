/*
 BAEKJOON
 17837. 새로운 게임 2
 
 1시간 30분 소요
 
 놓쳤던 부분
 1.
 현재 좌표에 (3, 1, 2, 5, 4)가 있을 때, 2번 말의 차례이면 2부터 위에 있는 말들(2, 5, 4)만 이동하는 것인데
 (3, 1, 2, 5, 4)가 모두 이동하는 줄 알았다.
 
 현재 좌표 벡터에서 현재 말의 idx를 찾아내고 (find_positon 함수), 그 idx부터 맨 뒤까지만 삭제해서 해결.
 
 2.
 파란색일 때, 방향을 바꾸고 파란색이 아니면 무조건 흰색처럼 이동하는 줄 알았다.
 다음 칸이 흰색, 빨간색인지 체크하고 그 색상에 맞게 이동해야 하는 것이었다.
 
 3. 주의사항
 void move_chess(int i, int r, int c, int nr, int nc, int d, int cl, int pos)에서
 매개변수 cl(color)을 없애고, nr, nc값을 받으니깐 color[nr][nc]값으로 체크하면 되지 않나? 생각했다.
 
 -> 런타임 에러 발생
 
 if(1 <= nr && nr <= N && 1 <= nc && nc <= N) move_chess(i, r, c, nr, nc, d, color[nr][nc], pos);
 else move_chess(i, r, c, nr, nc, d, 2, pos);
 
 여기서 배열 인덱스 범위를 초과해도(else문) 이 함수를 호출한다.
 따라서 color[nr][nc]로 값을 참조할 시 런타임 에러가 발생한다.
 color값을 매개변수로 넘겨줘야 한다.
 */

#include <iostream>
#include <vector>
#define MAP_MAX 13
using namespace std;

struct horse
{
    int r, c, dir;
    horse() {}
    horse(int rr, int cc, int d)
    {
        r = rr; c = cc; dir = d;
    }
};

int N, K, answer = 0;
int color[MAP_MAX][MAP_MAX];
vector<int> map[MAP_MAX][MAP_MAX];

int dr[5] = {0, 0, 0, -1, 1}; // 1부터 순서대로 →, ←, ↑, ↓
int dc[5] = {0, 1, -1, 0, 0};
vector<horse> h;

void input()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> color[i][j];
        }
    }
    
    int r, c, d;
    for(int i = 0; i < K; i++)
    {
        cin >> r >> c >> d;
        h.push_back(horse(r, c, d));
        map[r][c].push_back(i);
    }
}

void print()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cout << '(';
            for(int k = 0; k < map[i][j].size(); k++)
            {
                cout << map[i][j][k]+1 << "|" << h[map[i][j][k]].dir << " ";
            }
            cout << ')' << "\t\t";
        }
        cout << endl;
    }
    cout << endl;
}

int reverse_direction(int dir)
{
    if(dir == 1) return 2;
    else if(dir == 2) return 1;
    else if(dir == 3) return 4;
    else if(dir == 4) return 3;
}

int find_positon(int r, int c, int i)
{
    for(int t = 0; t < map[r][c].size(); t++)
    {
        if(map[r][c][t] == i)
        {
            return t;
        }
    }
}

void move_chess(int i, int r, int c, int nr, int nc, int d, int cl, int pos)
{
    /*
     흰색인 경우에는 그 칸으로 이동한다. 이동하려는 칸에 말이 이미 있는 경우에는 가장 위에 A번 말을 올려놓는다.
     A번 말의 위에 다른 말이 있는 경우에는 A번 말과 위에 있는 모든 말이 이동한다.
     예를 들어, A, B, C로 쌓여있고, 이동하려는 칸에 D, E가 있는 경우에는 A번 말이 이동한 후에는 D, E, A, B, C가 된다.
    */
    if(cl == 0)
    {
        for(int j = pos; j < map[r][c].size(); j++)
        {
            // 저장된 말의 idx
            int idx = map[r][c][j];
            map[nr][nc].push_back(idx);
            
            // 위치 값 갱신
            h[idx].r = nr;
            h[idx].c = nc;
        }
        map[r][c].erase(map[r][c].begin()+pos, map[r][c].end());
    }
    /*
     빨간색인 경우에는 이동한 후에 A번 말과 그 위에 있는 모든 말의 쌓여있는 순서를 반대로 바꾼다.
     A, B, C가 이동하고, 이동하려는 칸에 말이 없는 경우에는 C, B, A가 된다.
     A, D, F, G가 이동하고, 이동하려는 칸에 말이 E, C, B로 있는 경우에는 E, C, B, G, F, D, A가 된다.
    */
    else if(cl == 1)
    {
        for(int j = (int)map[r][c].size()-1; j >= pos; j--)
        {
            // 저장된 말의 idx
            int idx = map[r][c][j];
            map[nr][nc].push_back(idx);
            map[r][c].pop_back();
            // 위치 값 갱신
            h[idx].r = nr;
            h[idx].c = nc;
        }
    }
    /*
     파란색인 경우에는 A번 말의 이동 방향을 반대로 하고 한 칸 이동한다. 방향을 반대로 한 후에 이동하려는 칸이 파란색인 경우에는 이동하지 않고 방향만 반대로 바꾼다.
     체스판을 벗어나는 경우에는 파란색과 같은 경우이다.
    */
    else if(cl == 2)
    {
        d = reverse_direction(d);
        h[i].dir = d;
        
        nr = r + dr[d];
        nc = c + dc[d];
        
        if(1 <= nr && nr <= N && 1 <= nc && nc <= N && color[nr][nc] != 2)
        {
            move_chess(i, r, c, nr, nc, d, color[nr][nc], pos);
        }
    }
}

bool check()
{
    for(int i = 0; i < K; i++)
    {
        if(map[h[i].r][h[i].c].size() >= 4)
        {
            return true;
        }
    }
    return false;
}

void solve()
{
    while(++answer)
    {
        for(int i = 0; i < K; i++)
        {
            int r = h[i].r;
            int c = h[i].c;
            int d = h[i].dir;
            int pos = find_positon(r, c, i);
            
            int nr = r + dr[d];
            int nc = c + dc[d];
            
            // 배열 범위 충족
            if(1 <= nr && nr <= N && 1 <= nc && nc <= N) move_chess(i, r, c, nr, nc, d, color[nr][nc], pos);
            // 배열 범위 초과 -> 파란색과 같은 경우
            else move_chess(i, r, c, nr, nc, d, 2, pos);
            
            if(check())
            {
                cout << answer << endl;
                return;
            }
        }
        
        if(answer >= 1000)
        {
            cout << -1 << endl;
            return;
        }
    }
}


int main()
{
    input();
    solve();
    
    return 0;
}
