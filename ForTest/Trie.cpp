

struct Trie
{
    Trie *next[26];
    bool finish; // 여기서 끝나는게 있는가?
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
    void insert(const char* key) {
        if(*key == '\0')
            finish = true; // 문자열이 끝나는 지점이다
        else {
            int curr = *key - 'a';
            if(next[curr] == NULL)
                next[curr] = new Trie(); // 탐색이 처음되는 지점일 경우 동적할당
            next[curr]->insert(key + 1); // 다음 문자 삽입
        }
    }
    
    Trie* find(const char *key) {
        if(*key == '\0') return this;
        int curr = *key - 'a';
        if(next[curr] == NULL) return NULL; // 찾는 값이 존재하지 않음
        return next[curr]->find(key + 1); // 다음문자 탐색
    }

};

