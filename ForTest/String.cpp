#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

int main()
{
    string s;
    
    // 문자열 추출
    int s2 = s.substr(3,5); // 인덱스 3부터 5글자만큼
    
    // 라인에서 ','문자 기준으로 자르기
    stringstream ss(s);
    string res;
    while (getline(ss, res, ',')) {
        cout << res << endl;
    }
    
    // 숫자로 변환
    int n = atoi(res.c_str());
    
    // 문자열로 변환
    string tt = to_string(100);
}
