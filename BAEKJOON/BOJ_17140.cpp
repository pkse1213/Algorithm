/*
 BAEKJOON
 17140. 이차원 배열과 연산
 
 [조건] 수의 등장 횟수가 커지는 순으로, 그러한 것이 여러가지면 수가 커지는 순으로 정렬한다
 bool asc(pair<int, int> n1, pair<int, int> n2)
 {
     if(n1.second == n2.second) return n1.first < n2.first;
     else return n1.second < n2.second;
 }
 
 
 쉽지만 놓친 부분
 
 int j;
 for(j = 0; j < tmp.size(); j++)
 {
     ...
 }
 j--;
 j의 마지막 값을 얻으려면 j--해줘야 함
 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 101
using namespace std;

int r, c, k, answer, now_r, now_c;
int arr[MAX][MAX];
vector<pair<int, int>> tmp;

void initialize()
{
    answer = 0;
    now_r = 3; now_c = 3;
}

void input()
{
    cin >> r >> c >> k;
    
    for(int i = 1; i <= 3; i++)
    {
        for(int j = 1; j <= 3; j++)
        {
            cin >> arr[i][j];
        }
    }
}

bool check()
{
    if(arr[r][c] == k) return true;
    else return false;
}

bool find(int num)
{
    for(int i = 0; i < tmp.size(); i++)
    {
        if(tmp[i].first == num)
        {
            tmp[i].second++;
            return true;
        }
    }
    return false;
}

bool asc(pair<int, int> n1, pair<int, int> n2)
{
    if(n1.second == n2.second) return n1.first < n2.first;
    else return n1.second < n2.second;
}

void R()
{
    int nc = 0;
    
    for(int i = 1; i <= now_r; i++)
    {
        tmp.clear();
        
        for(int j = 1; j <= now_c; j++)
        {
            if(arr[i][j] != 0)
            {
                if(find(arr[i][j]) == false) tmp.push_back(make_pair(arr[i][j], 1));
                arr[i][j] = 0;
            }
        }
        
        sort(tmp.begin(), tmp.end(), asc);
        
        int j;
        for(j = 1; j <= tmp.size(); j ++)
        {
            arr[i][j*2-1] = tmp[j-1].first;
            arr[i][j*2] = tmp[j-1].second;
            
            if(j*2 == 100) break;
        }
        nc = max(nc, (j-1)*2);
    }
    now_c = nc;
}

void C()
{
    int nr = 0;
    
    for(int j = 1; j <= now_c; j++)
    {
        tmp.clear();
        
        for(int i = 1; i <= now_r; i++)
        {
            if(arr[i][j] != 0)
            {
                if(find(arr[i][j]) == false) tmp.push_back(make_pair(arr[i][j], 1));
                arr[i][j] = 0;
            }
        }
        
        sort(tmp.begin(), tmp.end(), asc);
        
        int i;
        for(i = 1; i <= tmp.size(); i++)
        {
            arr[i*2-1][j] = tmp[i-1].first;
            arr[i*2][j] = tmp[i-1].second;
            
            if(i*2 == 100) break;
        }
        nr = max(nr, (i-1)*2);
    }
    now_r = nr;
}

void print()
{
    for(int i = 1; i <= 12; i++)
    {
        for(int j = 1; j <= 12; j++)
        {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }

    cout << endl << endl;
}

void solve()
{
    while(1)
    {
//        print();
        
        if(check() == true) break;
        
        if(answer == 100)
        {
            answer = -1; break;
        }
        
        if(now_r >= now_c)
        {
            R();
        }
        else
        {
            C();
        }
        
        answer++;
    }
    
    cout << answer << endl;
}


int main()
{
    initialize();
    input();
    solve();
    
    return 0;
}
