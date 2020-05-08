#include <iostream>
#include <regex>
#define MAX 11
#define INF 987654321
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;


int solution(vector<string> lines) {
    int answer = 0;

    
    // 03:10:33.020 0.011s
    regex re("[0-9 -]{11}(\\d{2}):(\\d{2}):(\\d{2}.\\d{3}) (\\d[0-9.]*)s");
    smatch match;
    for(int i = 0; i < lines.size(); i++)
    {
        if(regex_match(lines[i], match, re))
        {
            for(int j = 0; j < match.size(); j++)
            {
                cout << match[j].str() << '\n';
            }
            cout << "\nㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n";
        }
    }
    
    return answer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    solution({"2016-09-15 20:59:57.421 0.351s", "2016-09-15 20:59:58.233 1.181s", "2016-09-15 20:59:58.299 0.8s", "2016-09-15 20:59:58.688 1.041s", "2016-09-15 20:59:59.591 1.412s", "2016-09-15 21:00:00.464 1.466s", "2016-09-15 21:00:00.741 1.581s", "2016-09-15 21:00:00.748 2.31s", "2016-09-15 21:00:00.966 0.381s", "2016-09-15 21:00:02.066 2.62s"});
    
    return 0;
}
