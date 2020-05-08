/*
 정규 표현식은 문자열에서 패턴을 찾는데 사용하는데, 이를 통해

 주어진 문자열이 주어진 규칙에 맞는지 확인할 때
 주어진 문자열에서 원하는 패턴의 문자열을 검색할 때
 주어진 문자열에서 원하는 패턴의 문자열로 치환할 때
 
 유용하다
 
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <regex>
#include <string>
using namespace std;
string html = "";
// 전체 문자열 매칭하기
// regex_match 를 이용해서 정규 표현식으로 전체 문자열 패턴 매칭하기
void matching_all_string()
{
    vector<string> file_names = {"db-123-log.txt", "db-124-log.txt",
                                "not-db-log.txt", "db-12-log.txt", "db-12-log.jpg"};
    regex re("db-\\d*-log\\.txt"); // \d* 는 임의의 개수의 숫자를 의미
    regex re2("db-\\d{2,3}-log\\.txt"); // \d{2,3} 는 2~3 개수의 숫자를 의미
    
    for(auto name : file_names)
        cout << name << ": " << boolalpha << regex_match(name,re) << endl;
}

// 부분 매칭 뽑아내기
void extracting_matchig_string()
{
    vector<string> phone_numbers = {"010-1234-5678", "010-123-4567",
                                    "011-1234-5567", "010-12345-6789",
                                    "123-4567-8901", "010-1234-567"};
    
    regex re("01[01]{1}-(\\d{3,4})-(\\d{4})"); // 뽑아내려는 부분을 ()로 감싼다!!
    smatch match;
    for(auto num : phone_numbers)
    {
        if(regex_match(num, match, re))
        {
            for(size_t i = 0; i < match.size(); i++)
            {
                cout << match[i].str() << ',';
            }
            cout << "\nㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n";
            // 결과 010-1234-5678 , 1234 , 5678
            // 가장 처음에는 매칭된 문자열 전체가 들어감!
        }
    }
    /*
    match 에서 매칭된 문자열들을 match[i].str() 을 통해 접근할 수 있습니다.
    참고로 우리의 match 가 smatch 이므로 match[i].str() 은 std::string 이 됩니다.
    반면에 match 가 cmatch 였다면 match[i].str() 는 const char* 이 되겠지요.
     */

}

// 문자열에서 원하는 패턴을 검색하기
// std::regex_search 를 이용해서 정규 표현식으로 문자열 검색하기
void search_pattern()
{
    regex re(R"(<div class="sk[\w -]*">\w*</div>)"); // [\w -]* -> \w(영어), ' ', '-'가 한 문자씩 임의의 개수만큼
    smatch match;
    while (regex_search(html, match, re))
    {
        cout << match.str() << endl;
        html = match.suffix();
        // match.prefix()는 맨앞 ~ 찾은 패턴의 앞
        // match.suffix()는 찾은 패턴의 뒤 ~ 끝
    }
}

// 문자열 치환하기
// regex_replace 를 이용해서 정규 표현식으로 문자열 치환하기
void replace_pattern()
{
    //$1, $2는 캡쳐 그룹이 중첩되었을 때 어느 것이 $1 이고 $2 인지 알아야 하는데,
    // 괄호가 열리는 순서대로 $1, $2, ... 로 진행한다고 생각하면 된다.
    
    // 결과 : "1-sk-circle sk-circle" 숫자가 앞으로 치환되고, 뒤는 건들지 않음
    string html1 = html;
    regex re(R"r(sk-circle(\d))r");
    smatch match;

    string modified_html = regex_replace(html, re, "$1-sk-circle");
    cout << modified_html;
    
    
    html1 = html;
    // 결과 : "7-sk-circle" 치환하며 뒤를 날려버리기
    regex re2(R"r((sk-circle(\d) sk-circle))r");
    smatch match2;

    string modified_html2 = regex_replace(html, re2, "$2-sk-circle"); // $2
    cout << modified_html2;
}



int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    html = R"(
             <div class="social-login">
               <div class="small-comment">다음으로 로그인 </div>
               <div>
                 <i class="xi-facebook-official fb-login"></i>
                 <i class="xi-google-plus goog-login"></i>
               </div>
             </div>
             <div class="manual">
               <div class="small-comment">
                 또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
               </div>
               <input name="name" id="name" placeholder="이름">
               <input name="password" id="password" type="password" placeholder="비밀번호">
             </div>
             <div id="adding-comment" class="sk-fading-circle">
               <div class="sk-circle1 sk-circle">a</div>
               <div class="sk-circle2 sk-circle">b</div>
               <div class="sk-circle3 sk-circle">asd</div>
               <div class="sk-circle4 sk-circle">asdfasf</div>
               <div class="sk-circle5 sk-circle">123</div>
               <div class="sk-circle6 sk-circle">aax</div>
               <div class="sk-circle7 sk-circle">sxz</div>
             </div>
       )";
    // 전체 문자열 매칭하기
//    matching_all_string();
    
    // 부분 매칭 뽑아내기
//    extracting_matchig_string();

    // 원하는 패턴 검색하기
    search_pattern();



    
    return 0;
}
