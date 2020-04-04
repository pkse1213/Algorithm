#include <iostream>
#include <string>
#include <vector>
using namespace std;

int solution(vector<int> Stones, int K)
{
    int Answer = 0;
    
    vector<int> Temp = Stones;
    sort(Temp.begin(), Temp.end());
    
    int Left = Temp.front();
    int Right = Temp.back();
    int Mid = 0;
    Answer = Left;
    
    while (Left <= Right) {
        Mid = (Left + Right) / 2;
        
        int Jump = 0;
        for(int i = 0; i < Stones.size(); i++)
        {
            int Tmp = Stones[i] - (Mid - 1);
            
            if(Tmp <= 0) Jump++;
            else Jump = 0;
            
            if(Jump == K) break;
        }
        
        if(Jump < K)
        {
            if(Answer < Mid) Answer = Mid;
            Left = Mid + 1;
        }
        else
        {
            Right = Mid - 1;
        }
    }
    
    return Answer;
}

int main()
{
    int Result = solution({2, 4, 5, 3, 2, 1, 4, 2, 5, 1}, 3);
    cout << Result << endl;
    return 0;
}


