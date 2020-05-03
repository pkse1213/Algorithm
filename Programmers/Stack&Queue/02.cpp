/*
 큐. 다리를 지나는 트럭

 */
#include <string>
#include <vector>
#include <queue>
using namespace std;


int solution(int bridge_length, int weight, vector<int> truck_weights) {
    queue<pii> q; // {들어온 시간, 무게}
    int time = 0;
    int idx = 0;
    int sum_weight = 0;
    
    while (1)
    {
        time++;
        if(!q.empty() && q.front().first + bridge_length == time)
        {
            sum_weight -= q.front().second;
            q.pop();
        }
        
        if(sum_weight + truck_weights[idx] <= weight)
        {
            sum_weight += truck_weights[idx];
            q.push({time, truck_weights[idx]});
            idx++;
            
            if(idx == truck_weights.size())
            {
                time += bridge_length;
                break;
            }
        }
        
    }
    return time;
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    cout << solution(2, 10, {7,4,5,6});
    
    return 0;
}
