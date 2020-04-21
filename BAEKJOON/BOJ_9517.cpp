/*
 9517. 아이 러브 크로아티아
 
 시뮬레이션
 */
#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, char> pic;

int K, N, Time = 0;
vector<pic> Answer;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> K >> N;
    K--;
    
    for(int i = 0; i < N; i++)
    {
        int T;
        char C;
        cin >> T >> C;
        Answer.push_back({T, C});
    }
    
    for(int i = 0; i < N; i++)
    {
        Time += Answer[i].first;
        if(Time >= 210) break;
        
        if(Answer[i].second == 'T') K = (K+1) % 8;
    }
    
    cout << K + 1 ;
    return 0;
}
