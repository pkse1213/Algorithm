
/*
 5648. [모의 SW 역량테스트] 원자 소멸 시뮬레이션
 https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRFInKex8DFAUo
 
 난이도 높은 문제다..
 
 1. map의 범위를 4001으로 한 이유
 atom.r = (r + 1000) * 2;
 atom.c = (c + 1000) * 2;
 
 2. 상 하 좌 우가 이렇게 되는 이유
 int dr[4] = {0, 0, -1, 1};
 int dc[4] = {1, -1, 0, 0};
 
 [조건] 원자는 각자 고유의 움직이는 방향을 가지고 있다. (상하좌우 4방향)
 - 상: y 가 증가하는 방향
 - 하: y 가 감소하는 방향
 - 좌: x 가 감소하는 방향
 - 우: x 가 증가하는 방향
 
 이해가 잘 안간다.. 꼭 다시 체크해보도록...
 */

#include <iostream>
#include <vector>
#include <cstring>
#define MAX 4001
using namespace std;

struct Atom
{
    int r, c, d, k;
    bool alive = true;
};
int T, N, r, c, d, k, Answer;
vector<Atom> Atoms;
int MAP[MAX][MAX];
int dr[4] = {0, 0, -1, 1};
int dc[4] = {1, -1, 0, 0};

void Initialize()
{
    Answer = 0;
    Atoms.clear();
    memset(MAP, 0, sizeof(MAP));
}

void Input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> r >> c >> d >> k;
        Atom atom;
        atom.r = (r + 1000) * 2;
        atom.c = (c + 1000) * 2;
        atom.d = d;
        atom.k = k;
        MAP[(r + 1000) * 2][(c + 1000) * 2] = 1;
        
        Atoms.push_back(atom);
    }
}

bool All_Die()
{
    for(int i = 0; i < Atoms.size(); i++)
    {
        if(Atoms[i].alive == true) return false;
    }
    return true;
}

void Solve()
{
    while(1)
    {
        if(All_Die() == true)
        {
            return;
        }
        
        for(int i = 0; i < Atoms.size(); i++)
        {
            if(Atoms[i].alive == false) continue;
            
            int nd = Atoms[i].d;
            int nr = Atoms[i].r + dr[nd];
            int nc = Atoms[i].c + dc[nd];
            
            if(nr < 0 || nr > MAX-1 || nc < 0 || nc > MAX-1)
            {
                Atoms[i].alive = false;
                MAP[Atoms[i].r][Atoms[i].c]--;
            }
            else
            {
                MAP[Atoms[i].r][Atoms[i].c]--;
                MAP[nr][nc]++;
                
                Atoms[i].r = nr;
                Atoms[i].c = nc;
            }
        }
        
        for(int i = 0; i < Atoms.size(); i++)
        {
            if(Atoms[i].alive == false) continue;
            
            if(MAP[Atoms[i].r][Atoms[i].c] > 1 || MAP[Atoms[i].r][Atoms[i].c] == 0)
            {
                Atoms[i].alive = false;
                MAP[Atoms[i].r][Atoms[i].c] = 0;
                Answer += Atoms[i].k;
            }
        }
    }
}

int main()
{
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        Initialize();
        Input();
        Solve();
        cout << "#" << t << " " << Answer << endl;
    }
    return 0;
}
