#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int solution(string answer_sheet, vector<string> sheets) {
    int answer = -1;

    for(int i = 0; i < sheets.size() - 1; i++)
    {
        string sheetA = sheets[i];
        for(int j = i + 1; j < sheets.size(); j++)
        {
            string sheetB = sheets[j];
            int longest_answer = 0;
            int length_answer = 0;
            int count_answer = 0;
            
            for(int k = 0; k < answer_sheet.size(); k++)
            {
                if(answer_sheet[k] != sheetA[k] && sheetA[k] == sheetB[k])
                {
                    length_answer++; count_answer++;
                    longest_answer = max(longest_answer, length_answer);
                }
                else
                {
                    length_answer = 0;
                }
            }
            answer = max(answer, count_answer + longest_answer * longest_answer);
        }
    }
    
    return answer;
}

int main()
{
    cout << solution("4132315142", {"3241523133","4121314445","3243523133","4433325251","2412313253"});
    return 0;
}
