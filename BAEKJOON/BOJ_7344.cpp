/*
 7344. 나무 막대
 
 길이(I)와 무게(W) 두 정보를 가지고 있다.
 
 1) 길이(혹은 무게)에 대하여 정렬
    길이에 대해서는 정렬되어 있으므로, 무게에 대해서만 비교하면서 작업 수행
 
 2) 길이가 가장 짧은 작업을 먼저 수행하고
    (반복)
    그 다음 인덱스부터 방금 수행한 작업의 무게보다 무게가 더 나가는 것을 찾아서 수행
    
 3) 한 바퀴 다 돌았으면 아까 작업 수행한 것의 다음 인덱스부터
    아직 수행하지 않은 것을 선택
    2번) 반복
 
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, N, I, W, Cnt;
vector<pair<pair<int, int>, bool>> Work;

void Initialize()
{
    Cnt = 0;
    Work.clear();
}

void Input()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> I >> W;
        Work.push_back({{I, W}, false});
    }
}

void Solve()
{
    sort(Work.begin(), Work.end());
    
    for(int i = 0; i < Work.size(); i++)
    {
        if(Work[i].second == false)
        {
            Cnt++;
            int Pre_W = Work[i].first.second;
            Work[i].second = true;
            
            
            for(int k = i + 1; k < Work.size(); k++)
            {
                if(Work[k].second == false && Pre_W <= Work[k].first.second)
                {
                    Pre_W = Work[k].first.second;
                    Work[k].second = true;
                }
            }
        }
    }
}

int main()
{
    cin >> T;
    for(int i = 0; i < T; i++)
    {
        Initialize();
        Input();
        Solve();
        cout << Cnt << endl;
    }
    
    return 0;
}

