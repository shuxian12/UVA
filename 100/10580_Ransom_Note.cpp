#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<queue>
#include<cctype>
using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1521

struct Compfunc{
    bool operator() (const string& a, const string& b){
        if(a.length() == b.length())
            return a < b;
        return a.length() < b.length();
    }
};

int main(){
    string topic, line;
    getline(cin, topic);
    map<char, vector<int> > mp;
    for(int i = 0; i < topic.length(); i++){
        if(topic[i] == ' ') continue;
        mp[topic[i]].push_back(i);
    }

    priority_queue<string, vector<string>, Compfunc> ans[topic.length()];
    while(getline(cin, line) && line.size()){   //line.size() 要刪掉
        for(int i = 0; i < line.length(); i++){
            if(line[i] == ' ') continue;
            if(mp.find(line[i]) != mp.end() || mp.find(tolower(line[i])) != mp.end()){
                vector<int> idx = mp[tolower(line[i])];
                for(int q = 0; q < idx.size(); q++){
                    string tmp = "";
                    tmp += line[i];
                    int j = i + 1, k = idx[q] + 1;
                    while(line[j] == topic[k] || tolower(line[j]) == topic[k]){
                        tmp += line[j];
                        j++;
                        k++;
                    }
                    if(ans[idx[q]].empty() || ans[idx[q]].top().length() < tmp.length())
                        ans[idx[q]].push(tmp);
                }
            }
        }
    }

    queue<string> out;
    for(int i = 0; i < topic.length(); i++){
        if(ans[i].empty())  continue;
        string tmp = ans[i].top();
        out.push(tmp);
        i += tmp.length() - 1;
    }
    cout << out.size() << endl;
    while(out.size()){
        cout << out.front() << endl;
        out.pop();
    }
}
