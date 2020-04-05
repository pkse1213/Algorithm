#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct Tree_Info
{
    int x1, x2, y, idx;
};

int N, Q, A, B;
Tree_Info Tree[100001];
int Group[100001];

bool Standard(Tree_Info T1, Tree_Info T2)
{
    if(T1.x1 == T2.x1) return T1.x2 > T2.x2;
    return T1.x1 < T2.x1;
}


int main()
{
    cin >> N >> Q;
    for(int i = 0; i < N; i++)
    {
        scanf("%d %d %d", &Tree[i].x1, &Tree[i].x2, &Tree[i].y);
        Tree[i].idx = i;
    }
    
    sort(Tree, Tree + N, Standard);
    
    int Cnt = 0;
    Group[Tree[0].idx] = Cnt;
    
    for(int i = 1; i < N; i++)
    {
        if(Tree[i].x1 <= Tree[i - 1].x2)
        {
            Group[Tree[i].idx] = Cnt;
        }
        else
        {
            Group[Tree[i].idx] = ++Cnt;
        }
    }
    
    for(int i = 0; i < Q; i++)
    {
        scanf("%d %d", &A, &B);
        cout << (Group[A - 1] == Group[B - 1]) << endl;
    }
    
    return 0;
}


