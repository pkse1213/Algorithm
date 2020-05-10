#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
#include <deque>
#include <vector>
#include <stack>
#include <map>
#include <regex>
#include <math.h>
#define MAX 11
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;


string solution(vector<int> numbers, string hand) {
    string answer = "";
    
    int r_j = 4, r_i = 3;
    int l_j = 4, l_i = 1;
    for(int i = 0; i < numbers.size(); i++)
    {
        int n = numbers[i];
        
        if(n == 1 || n == 4 || n == 7)
        {
            answer += 'L';
            l_j = (n + 2 )/3; l_i = 1;
        }
        else if(n == 3 || n == 6 || n == 9)
        {
            answer += 'R';
            r_j = n / 3; r_i = 3;
        }
        else if(n == 2 || n == 5 || n == 8 || n == 0)
        {
            int m = (n + 1) / 3;
            if(n==0) m = 4;
            
            if(abs(r_j-m) + abs(r_i-2) < abs(l_j-m) + + abs(l_i-2))
            {
                answer += 'R'; r_j = m; r_i = 2;
            }
            else if(abs(r_j-m) + abs(r_i-2) > abs(l_j-m) + + abs(l_i-2))
            {
                answer += 'L';l_j = m; l_i = 2;
            }
            else
            {
                if(hand == "right")
                {
                    answer += 'R'; r_j = m; r_i = 2;
                }
                else if(hand == "left" )
                {
                    answer += 'L'; l_j = m; l_i = 2;
                }
            }
        }
        
    }
    return answer;
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    
    
    solution({1, 3, 4, 5, 8, 2, 1, 4, 5, 9, 5}, "right");
    return 0;
}
