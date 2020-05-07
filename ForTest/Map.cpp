#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    map<string, string> m;
    map<string, string>::iterator it;
    
    // map 순회
    for(it = m.begin(); it != m.end(); it++)
    {
        cout << it->first << it->second << endl;
    }
}
