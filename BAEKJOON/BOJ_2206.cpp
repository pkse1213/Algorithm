/*
 2206. 벽 부수고 이동하기
 
 1) 처음 생각
 벽들의 정보를 저장하고 하나씩 없을 때를 BFS로 계산하려 함
 BFS로 새로운 배열에 거리 값을 저장해주고 + 1 해주고 N-1, M-1일 때 return해주는 건 좋았지만 시간 초과
 
 2)
 3차원 배열Dist[r][c][벽을 부순 때 / 부수지 않은 때]로 나눠서 거리 값 저장.
 
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#define MAX 1001
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;

int MAP[MAX][MAX];
int Dist[MAX][MAX][2];
int N, M, Answer = INF;
int Dr[4] = {0, 0, -1, 1};
int Dc[4] = {-1, 1, 0, 0};
string Str;

void Input()
{
    cin >> N >> M;
    for(int i = 0; i < N; i++)
    {
        cin >> Str;
        for(int j = 0; j < M; j++)
        {
            MAP[i][j] = Str[j] - '0';
        }
    }
}

int BFS()
{
    queue<pair<pii, int>> Q;
    Q.push({{0, 0}, 0});
    Dist[0][0][0] = 1;
    
    while (Q.empty() == false)
    {
        int R = Q.front().first.first;
        int C = Q.front().first.second;
        int B = Q.front().second;
        Q.pop();
        
        if(R == N - 1 && C == M - 1) return Dist[R][C][B];
        
        
        for(int i = 0; i < 4; i++)
        {
            int Nr = R + Dr[i];
            int Nc = C + Dc[i];
            
            if(Nr < 0 || Nr > N - 1 || Nc < 0 || Nc > M - 1) continue;
            
            // 벽을 만났는데 아직 벽을 부수지 않았을 때
            if(MAP[Nr][Nc] == 1 && B == 0)
            {
                
                Q.push({{Nr, Nc}, 1});
                Dist[Nr][Nc][1] = Dist[R][C][B] + 1;
            }
            // 벽이 아닌데, 아직 방문하지 않았을 때
            else if(MAP[Nr][Nc] == 0 && Dist[Nr][Nc][B] == 0)
            {
                Q.push({{Nr, Nc}, B});
                Dist[Nr][Nc][B] = Dist[R][C][B] + 1;
            }
        }
    }
    return -1;
}

int main()
{
    Input();
    cout << BFS() << endl;
    
    return 0;
}
