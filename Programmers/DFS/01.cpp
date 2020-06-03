//
//  01.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/03.
//  Copyright © 2020 박세은. All rights reserved.
//
/*
 DFS. 네트워크

 */
#include <string>
#include <vector>

using namespace std;

int visited[201] = {false};
vector<vector<int>> v;
int num;

void dfs(int cp)
{
    if(cp == v.size()) return;
    for(int i = 0; i < num; i++)
    {
        if(visited[i] || v[cp][i] == 0) continue;
        visited[i] = true;
        dfs(i);
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    v = computers;
    num = n;
    
    for(int j = 0; j < n; j++)
    {
        if(visited[j]) continue;
        visited[j] = true;
        dfs(j);
        answer++;
    }
    return answer;
}
