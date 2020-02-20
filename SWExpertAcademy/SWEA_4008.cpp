/*
 4008. [모의 SW 역량테스트] 숫자 만들기
 
 이 문제는 꼭 다시 리뷰하자...
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define MAX 12
using namespace std;

int T, N, Answer;
int Number[MAX];
vector<int> Result;
vector<int> Operator;
int Temp[5];

void Initialize()
{
    Answer = 0;
    Result.clear();
}

void Input()
{
    cin >> N;
    
    for(int i = 1; i <= 4; i++)
    {
        cin >> Temp[i];
    }
    for(int i = 0; i < N; i++)
    {
        cin >> Number[i];
    }
    
//    for(int i = 0; i < Origin.size(); i++)
//    {
//        cout << Origin[i] << ' ';
//    }
//    cout << endl;
}

void Calculate()
{
    int res = Number[0];
    for(int i = 0; i < N-1; i++)
    {
        // '+' '-' '*' '/'
        if(Operator[i] == 1)
        {
            res += Number[i + 1];
        }
        else if(Operator[i] == 2)
        {
            res -= Number[i + 1];
        }
        else if(Operator[i] == 3)
        {
            res *= Number[i + 1];
        }
        else if(Operator[i] == 4)
        {
            res /= Number[i + 1];
        }
    }
    
    Result.push_back(res);
}

//void DFS(int cnt)
//{
//    if(cnt == N - 1)
//    {
//        for(int i = 0; i < N - 1; i++)
//        {
//            cout << Operator[i] << ' ';
//        }
//        cout << endl;
//        Calculate();
//        return;
//    }
//    for(int i = 0; i < Origin.size(); i++)
//    {
//        if(Selected[i] == true) continue;
//
//        Operator[cnt] = Origin[i];
//        Selected[i] = true;
//
//        DFS(cnt + 1);
//        Selected[i] = false;
//    }
//}


void DFS(int cnt)
{
    if(cnt == N-1)
    {
        Calculate();
        return;
    }
    
    for(int i = 1; i <= 4; i++){
        // 사용할 수 있는 연산자가 남았다면
        if(Temp[i] > 0){
            Operator.push_back(i);
            Temp[i] -= 1;
            
            DFS(cnt + 1);
            
            Temp[i] += 1;
            Operator.pop_back();
        }
    }
}

void Find_Reslut()
{
    sort(Result.begin(), Result.end());
    int min = Result.front();
    int max = Result.back();
    
    Answer = abs(min - max);
}

void Solve()
{
    DFS(0);
    Find_Reslut();
}

int main()
{
    cin >> T;
    for(int t = 1; t <= T; t++)
    {
        Initialize();
        Input();
        Solve();
        
        cout << "#" << t << " " << Answer << endl;
    }
    
    return 0;
}
