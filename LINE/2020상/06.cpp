#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

struct Dir
{
    string name;
    map<string, Dir> child;
    Dir(){};
};

Dir root;
vector<string> answer;

void dfs(Dir dir, string before)
{
    before += "/" + dir.name;
    answer.push_back(before);
    map<string, Dir>::iterator it;
    
    for(it = dir.child.begin(); it != dir.child.end(); it++)
    {
        dfs(it->second, before);
    }
}

void mkdir(string route)
{
    stringstream ss(route);
    string name;
    
    Dir *cur = &root;
    while (getline(ss, name, '/'))
    {
        if(name == "") continue;
        if(cur->child.find(name) == cur->child.end())
        {
            Dir temp;
            temp.name = name;
            cur->child[name] = temp;
        }
        else
        {
            cur = &cur->child[name];
        }
    }
}

pair<Dir&, string> find_parent_dir(string route)
{
    stringstream ss(route);
    string name;

    Dir *cur = &root;
    Dir *parent = nullptr;
    while (getline(ss, name, '/'))
    {
        if(name == "") continue;
        parent = cur;
        cur = &cur->child[name];
    }
    return { *parent, name };
}

pair<Dir&, string> find_current_dir(string route)
{
    stringstream ss(route);
    string name;

    Dir *cur = &root;
    while (getline(ss, name, '/'))
    {
        if(name == "") continue;
        cur = &cur->child[name];
    }
    
    return { *cur, name };
}

void rm(string route)
{
    pair<Dir&, string> result = find_parent_dir(route);
    result.first.child.erase(result.second);
}

void cp(string route)
{
    int idx = 0;
    string routes[2];
    
    stringstream ss(route);
    string tmp;
    while (getline(ss, tmp, ' '))
    {
        if(tmp == "") continue;
        routes[idx++] = tmp;
    }
    
    pair<Dir&, string> result1 = find_current_dir(routes[0]);
    pair<Dir&, string> result2 = find_current_dir(routes[1]);
    
    Dir new_dir;
    new_dir.child = result1.first.child;
    new_dir.name = result1.second;
    
    result2.first.child[result1.second] = new_dir;
}

vector<string> solution(vector<string> directory, vector<string> command)
{
    for(int i = 0; i < directory.size(); i++)
    {
        mkdir(directory[i]);
    }
    
    for(int i = 0; i < command.size(); i++)
    {
        string cmd = command[i];
        if(cmd[0] == 'm')
        {
            cmd.erase(cmd.begin(), cmd.begin() + 6);
            mkdir(cmd);
        }
        else if(cmd[0] == 'r')
        {
            cmd.erase(cmd.begin(), cmd.begin() + 3);
            rm(cmd);
        }
        else if(cmd[0] == 'c')
        {
            cmd.erase(cmd.begin(), cmd.begin() + 3);
            cp(cmd);
        }
    }
    
    map<string, Dir>::iterator it;
    answer.push_back("/");
    for(it = root.child.begin(); it != root.child.end(); it++)
    {
        dfs(it->second, "");
    }
    
    return answer;
}

int main()
{
    vector<string> result = solution({"/",
        "/hello",
        "/hello/tmp",
        "/root",
        "/root/abcd",
        "/root/abcd/etc",
        "/root/abcd/hello"
    }, {"mkdir /root/tmp",
        "cp /hello /root/tmp", "rm /hello"
    });
    for(int i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }
    
    
    return 0;
}
