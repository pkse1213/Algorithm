/*
 14891. 톱니바퀴
 
 미리 양 옆의 N-S극 체크한 후에,
 돌릴지 말지 정하고 나서
 동시에 돌려야한다.
 
 하나 돌리고 그 결과에 맞춰서
 양 옆을 돌리는 건 줄 알았는데 아니었다.
 
 문제를 꼼꼼하게 읽어보고 설계하도록 하자.
 */

#include <iostream>
using namespace std;

int N;
int num[100];
int dir[100];
int wheel[4][8];
int ch[4] = { 0 };

void rotate_wheel() {
    for(int w = 0; w < 4; w++)
    {
        if(ch[w] == -1) {
            int tmp = wheel[w][0];
            for(int i = 0; i < 7; i++) {
                wheel[w][i] = wheel[w][i+1];
            }
            wheel[w][7] = tmp;
        }
        else if(ch[w] == 1) {
            int tmp = wheel[w][7];
            for(int i = 7; i > 0; i--) {
                wheel[w][i] = wheel[w][i-1];
            }
            wheel[w][0] = tmp;
        }
    }
}

void check(int w, int d) {
    if(w-1 >= 0 && ch[w-1] == 0)
    {
        if(wheel[w-1][2] != wheel[w][6]) {
            ch[w-1] = -d;
            check(w-1, -1*d);
        }
    }
    if(w+1 < 4 && ch[w+1] == 0)
    {
        if(wheel[w+1][6] != wheel[w][2]) {
            ch[w+1] = -d;
            check(w+1, -1*d);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    string str;
    for(int i = 0; i < 4; i++) {
        cin >> str;
        for(int j = 0; j < 8; j++) {
            
            wheel[i][j] = (str[j] - '0');
        }
    }
    
    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> num[i] >> dir[i];
    
    for(int i = 0; i < N; i++) {
        int w = --num[i];
        int d = dir[i];
        memset(ch, 0, sizeof(ch));
        ch[w] = d;
        check(w, d);
        
        rotate_wheel();
    }
    
    int ans = 0;
    for(int i = 0; i < 4; i++)
    {
        if(wheel[i][0] == 1) ans += (pow(2, i));
    }
    cout << ans;
    return 0;
}
