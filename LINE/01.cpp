#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int M, C, T;
queue<int> Message;
vector<int> Consumer[10];

void Input()
{
    cin >> M >> C;
    for(int i = 0; i < M; i++)
    {
        cin >> T;
        Message.push(T);
    }
}

void Solve()
{
    int Time = 1;
    
    while (Message.empty() == false)
    {
        for(int i = 0; i < C; i++)
        {
            if(Consumer[i].size() < Time)
            {
                int m = Message.front();
                Message.pop();
                
                for(int j = 0; j < m; j++)
                {
                    Consumer[i].push_back(m);
                }
                break;
            }
        }
        Time++;
    }
}

int Find_Time()
{
    int Size = 0;
    for(int i = 0; i < C; i++)
    {
        Size = max(Size, (int)Consumer[i].size());
    }
    return Size;
}

int main()
{
    Input();
    Solve();
    cout << Find_Time() << endl;
    return 0;
}
