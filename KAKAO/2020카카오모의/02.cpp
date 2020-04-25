#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

bool Standard(vector<int> A, vector<int> B)
{
    return A.size() < B.size();
}

vector<int> solution(string S) {
    vector<int> Answer;
    
    bool Visited[1000001] = { false, };
    vector<vector<int>> V;
    
    string Temp = "";
    for(int i = 0; i < S.size()-1; i++)
    {
        if(S[i] == '}')
        {
            vector<int> V_Temp;
            stringstream SS(Temp);
            string Res;
            
            while (getline(SS, Res, ',')) {
                V_Temp.push_back(atoi(Res.c_str()));
            }
            V.push_back(V_Temp);
        }
        else if(S[i] == '{')
        {
            Temp = "";
        }
        else
        {
            Temp += S[i];
        }
    }
    
    sort(V.begin(), V.end(), Standard);
    
    for(int i = 0; i < V.size(); i++)
    {
        for(int j = 0; j < V[i].size(); j++)
        {
            if(Visited[V[i][j]] == false)
            {
                Answer.push_back(V[i][j]);
                Visited[V[i][j]] = true;
            }
        }
    }
    
    return Answer;
}

int main()
{
    string Str;
    cin >> Str;
    vector<int> Result = solution(Str);
    
    for(int i = 0; i < Result.size(); i++)
    {
        cout << Result[i] << ' ';
    }

    return 0;
}
