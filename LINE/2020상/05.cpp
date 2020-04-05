#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;


struct compare{
    bool operator()(pair<int, string> A, pair<int, string> B)
    {
        if(A.first == B.first) return A.second > B.second;
        else return A.first < B.first;
    }
};

vector<string> solution(vector<vector<string>> dataSource, vector<string> tags) {
    vector<string> answer;
    priority_queue<pair<int, string>, vector<pair<int, string>>, compare> pq;
    
    for(int i = 0; i < dataSource.size(); i++)
    {
        dataSource[i].insert(dataSource[i].end(), tags.begin(), tags.end());
        
        int size = (int)dataSource[i].size();
        sort(dataSource[i].begin() + 1, dataSource[i].end());
        dataSource[i].erase(unique(dataSource[i].begin() + 1, dataSource[i].end()), dataSource[i].end());
        
        int resize = size - (int)dataSource[i].size();
        
        if(resize > 0) pq.push({ resize, dataSource[i][0] });
    }
    
    for(int i = 0; i < 10; i++)
    {
        if(pq.empty()) break;
        answer.push_back(pq.top().second);
        pq.pop();
    }
    
    return answer;
}

int main()
{
    vector<string> result = solution({{"doc1", "t1", "t2", "t3"},
        {"doc2", "t0", "t2", "t3"},{"doc8", "t0", "t2", "t3"},{"Doc2", "t0", "t2", "t3"},{"coc2", "t0", "t2", "t3"},{"bc2", "t0", "t2", "t3"},
        {"doc3", "t1", "t6", "t7"},
        {"doc4", "t1", "t2", "t4"},
        {"doc5", "t6", "t100", "t8"}
    }, {"t1", "t2", "t3"});
    
    
    for(int i = 0; i < result.size(); i++)
    {
        cout << result[i] << ' ';
    }
    return 0;
}

