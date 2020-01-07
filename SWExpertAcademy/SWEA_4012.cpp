/*
 SW Expert Academy
 4012. [모의 SW 역량테스트] 요리사
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#define MAX 17
using namespace std;
int map[MAX][MAX];
int n;
bool visited[MAX] = { false };

int answer = 200001;

void input()
{
    cin >> n ;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            cin >> map[i][j];
        }
    }
}

void count()
{
    int sum1 = 0;
    int sum2 = 0;
    vector<int> one;
    vector<int> two;
    
    for(int i=1; i<=n; i++)
    {
        if(visited[i])
            one.push_back(i);
        else
            two.push_back(i);
    }
    
    for(int i=0; i<n/2-1; i++)
    {
        for(int j=i+1; j<n/2; j++)
        {
            sum1 += (map[one[i]][one[j]] + map[one[j]][one[i]]);
            sum2 += (map[two[i]][two[j]] + map[two[j]][two[i]]);
        }
    }
    
    answer = min(answer, abs(sum1-sum2));
}


void dfs(int idx, int cnt)
{
    if(cnt >= n/2)
    {
        count();
        return;
    }
    
    for(int i=idx+1; i<=n; i++)
    {
        visited[i] = true;
        dfs(i, cnt+1);
        visited[i] = false;
    }
}


int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case)
    {
        answer = 200001;
        input();
        dfs(0,0);
        
        cout << "#" << test_case << " " << answer << endl;

    }
    return 0;
}
