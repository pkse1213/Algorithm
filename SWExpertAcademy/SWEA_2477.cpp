/*
 SW Expert Academy
 2477. 차량정비소(다시)
 
 우선순위 큐 (priority_queue) 기존 사용범
 -> priority_queue<int, vector<int>, greater<int>>
  
 greater struct
 struct _LIBCPP_TEMPLATE_VIS greater : binary_function<_Tp, _Tp, bool>
 {
    _LIBCPP_CONSTEXPR_AFTER_CXX11 _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _Tp& __x, const _Tp& __y) const
        {return __x > __y;}
 };
  
 struct CompareIdx
 {
     bool operator() (Customer a, Customer b)
     {
         return a.idx > b.idx;
     }
 };
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#define MAX 10
using namespace std;
struct Customer
{
    int idx ,time , rc;
    Customer() {}
    Customer(int _idx, int _time, int _rc) : idx(_idx), time(_time), rc(_rc) {}
};

int recep[MAX][3]; // [0]:걸리는 시간 [1]:남은 시간 [2]:고객 idx
int repair[MAX][3];
Customer cs[10001];
priority_queue<int, vector<int>, greater<int>> recep_cst;
queue<int> repair_cst;
int now_recep[MAX];
int now_repair[MAX];

int t, n, m, a, b, k, arrived_time;
int answer = 0;

void input()
{
    // n->접수 ->정비
    cin >> n >> m >> k >> a >> b;
    for(int i=1; i<=n; i++)
    {
        cin >> recep[i][0];
        recep[i][1] = 0;
        recep[i][2] = 0;
    }
    
    for(int j=1; j<=m; j++)
    {
        cin >> repair[j][0];
        repair[j][1] = 0;
        repair[j][2] = 0;
    }
    
    for(int i=1; i<=k; i++)
    {
        cin >> arrived_time;
        cs[i] = Customer(i, arrived_time, 0);
    }
}

void play()
{
    int finish_repair = 0,
        finish_recept = 0,
        now = 0;
    
    while(1)
    {
        // 0초부터 1초마다 체크
        // 현재 시간에 들어온 고객 추가
        for(int i=1; i<=k; i++)
            if(cs[i].time == now)
                recep_cst.push(cs[i].idx);
        
        //삭제
//        cout <<endl<<"t=" << now << endl << "now_reception : "  ;
        
        for(int i=1; i<=n; i++)
        {
            // 고객이 이미 접수중일 때 -> 남은 시간 감소
            if(recep[i][2])
            {
                if(++recep[i][1] >= recep[i][0])
                {
                    repair_cst.push(now_recep[i]);
                    recep[i][1] = 0;
                    recep[i][2] = 0;
                }
            }
            // 고객이 없을때(비어있을 때) -> 고객 추가, 남은 시간 리셋
            else if(!recep_cst.empty())
            {
                //삭제
//                cout << i << '-' << recep_cst.top() << " ";
                
                finish_recept++; // 접수한 고객수 ++
                cs[recep_cst.top()].rc = i; // 고객의 접수처 = 현재 접수처 idx 설정
                now_recep[i] = recep_cst.top(); // 현제 idx 접수처의 현재 접수중인 고객으로 설정
                recep_cst.pop(); // 접수대기에서 pop
                
                recep[i][2] = 1; // 현재 고객이 있다는 flag
                recep[i][1]++;
            }
        }
        
        
//        cout << endl << "recep_cst : ";
//        for(int i=1; i<recep_cst.size(); i++)
//        {
//            cout << recep_cst.top() + i << " ";
//        }
//        cout << endl;
//
//
//         cout << "now_repair : ";
        
        for(int i=1; i<=m; i++)
        {
            // 고객이 이미 접수중일 때 -> 남은 시간 감소
            if(repair[i][2])
            {
                if(++repair[i][1] >= repair[i][0])
                {
                    repair[i][1] = 0;
                    repair[i][2] = 0;
                }
            }
                        
            // 고객이 없을때(비어있을 때) -> 고객 추가, 남은 시간 리셋
            else if(!repair_cst.empty())
            {
//                cout << i << ':' << repair_cst.front() << " ";
                finish_repair++;
                
                if(cs[repair_cst.front()].rc == a && i == b)
                    answer += repair_cst.front();
                repair_cst.pop();
                repair[i][2] = 1;
                
                repair[i][1] ++;
            }
        }
//        cout << endl;
        
        
//        cout << "repair_cst : ";
        for(int i=1; i<repair_cst.size(); i++)
        {
//            cout << repair_cst.front() + i << " ";
        }
//        cout << endl;
        
        if(finish_recept == k && finish_repair == k)
           break;
        now ++;
    }
}

int main(int argc, char** argv)
{
    cin >> t;
    for(int i=0; i<t; i++)
    {
        answer = 0;
        input();
        play();
        if(answer == 0) answer = -1;
        cout << "#" << i+1 << " " << answer << endl;
    }
    return 0;
}
