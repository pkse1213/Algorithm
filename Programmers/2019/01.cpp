/*
 Summer/Winter Coding(2019)
 멀쩡한 사각형
 
 최대공약수 까지는 쉽게 알았는데
 대각선이 w + h - 1개를 차지한다는 것,, 놀랍다;..
 */
using namespace std;
typedef long long ll;


ll gcd(ll a, ll b)
{
    ll c;
    while (b != 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

long long solution(int w, int h) {
    ll answer = 1;
    ll W = (ll)w;
    ll H = (ll)h;
    
    ll g = gcd(W, H);
    ll sum = W*H;
    
    answer = sum - g * ((w / g) + (h / g) - 1);

    return answer;
}
