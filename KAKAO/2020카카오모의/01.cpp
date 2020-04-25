#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>
#define MAX 11
using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    
    stack<int> catched;
    for(int i = 0; i < moves.size(); i++)
    {
        int c = moves[i] - 1;
        
        for(int r = 0; r < board.size(); r++)
        {
            if(board[r][c] > 0)
            {
                if(catched.empty() == true)
                {
                    catched.push(board[r][c]);
                }
                else
                {
                    if(catched.top() == board[r][c])
                    {
                        catched.pop();
                        answer += 2;
                    }
                    else
                    {
                        catched.push(board[r][c]);
                    }
                }
                
                board[r][c] = 0;
                break;
            }
        }
    }
    return answer;
}

int main()
{
    int Result = solution({ {0,0,0,0,0},
                            {0,0,1,0,3},
                            {0,2,5,0,1},
                            {4,2,4,4,2},
                            {3,5,1,3,1}}, {1,5,3,5,1,2,1,4});
    
    cout << Result << endl;

    return 0;
}

