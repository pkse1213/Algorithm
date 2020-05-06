/*
 가사검색
 트라이(Trie)
 
 검색 키워등 ?는 접두사 혹은 접미사이다.
 ["fro??", "????o", "fr???", "fro???", "pro?"]
 
 따라서 "fro??"와 같은 접미사일 경우는 기존 방식대로 쉽게 찾을 수 있다.
 하지만 ?가 들어왔을 때, for문을 돌려서 검색한다고 생각했는데
 map을 사용해 여기까지의 접두사를 가지고
 len길이의 문자열인 단어의 개수를 저장해서 빠르게 답을 유출할 수 있었다.
 
 두 번째 문제는 "????o"와 같은 ?가 접미사로 들어올 경우이다.
 map을 사용해 o까지는 확인해보지 않고 바로 return하기 때문에 문제가 발생했다.
 트라이 구조에 처음에 단어들을 저장할 때 바르게 정렬된 것과, 뒤집어서 정렬된 것을 따로 만들었다.
 따라서 접두사가 ?일 경우에는 뒤집어 정렬된 트라이를, 아닐 때는 바르게 정렬된 트라이를 탐색해서 해결했다.
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

struct Trie
{
    Trie *next[26];
    bool finish; // 여기서 끝나는게 있는가?
    map<int, int> m;
    // 생성자
    Trie() {
        memset(next, 0, sizeof(next));
    }
    // 소멸자
    ~Trie() {
        for(int i = 0; i < 26; i++)
        {
            if(next[i]) delete next[i];
        }
    }
    // 문자 삽입
    void insert(const char* key, int len) {
        if(*key == '\0')
            finish = true; // 문자열이 끝나는 게 있다
        else {
            int curr = *key - 'a';
            if(next[curr] == NULL)
                next[curr] = new Trie(); // 탐색이 처음되는 지점일 경우 동적할당
            m[len]++;
            next[curr]->insert(key + 1, len); // 다음 문자 삽입
        }
    }
    
    int find(const char *key, int len) {
        if(*key == '\0')
        {
            if(finish) return 1;
            else return 0;
        }
        
        if(*key == '?')
        {
            return m[len];
        }
        else
        {
            int curr = *key - 'a';
            
            if(next[curr] == NULL) return 0; // 찾는 값이 존재하지 않음
            
            return next[curr]->find(key+1, len); // 다음문자 탐색
        }
    }
};


vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    
    Trie *root_r = new Trie();
    Trie *root_l = new Trie();
    
    for(int i = 0; i < words.size(); i++)
    {
        root_r->insert(words[i].c_str(), words[i].size());
        reverse(words[i].begin(), words[i].end());
        root_l->insert(words[i].c_str(), words[i].size());
    }
    
    for(int i = 0; i < queries.size(); i++)
    {
        int res = 0;
        if(queries[i][0] != '?') res = root_r->find(queries[i].c_str(), queries[i].size());
        else
        {
            reverse(queries[i].begin(), queries[i].end());
            res = root_l->find(queries[i].c_str(), queries[i].size());
        }
        answer.push_back(res);
    }
    
    return answer;
}
