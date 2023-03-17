#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include<queue>
using namespace std;

// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&category=0&problem=1091

unordered_map<string, int> dic;
vector<string> idx;
vector<string> table[17];

vector<int> bfs(int start, int end, vector<int> adj[]){
    vector<int> path;
    if(idx[start].length() != idx[end].length()){
        return path;
    }
    vector<bool> visited(idx.size(), false);
    vector<int> parent(idx.size(), -1);
    // if(start.length() != end.length()) return;
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        // if(visited[cur]) continue;
        visited[cur] = true;
        for(int i = 0; i < adj[cur].size(); i++){
            if(!visited[adj[cur][i]]){
                q.push(adj[cur][i]);
                parent[adj[cur][i]] = cur;
                visited[adj[cur][i]] = true;
            }
        }
        if(visited[end]) break;
    }

    if(!visited[end]){
        path.clear();
        return path;
    }
    while(end >= 0){
        path.push_back(end);
        end = parent[end];
    }
    return path;
}

bool doublet(string a, string b){
    if(a.length() != b.length()) return false;
    int diff = 0;
    for(int i = 0; i < a.length(); i++){
        if(a[i] != b[i])    diff++;
    }
    if(diff > 1)    return false;
    return true;
}

int main(){

    string line;
    int num = 0;
    while(getline(cin, line) && line.length() > 0){
        table[line.length()].push_back(line);
        idx.push_back(line);    // 位置表
        dic[line] = num++;      // 字典表
    }
    // cout<<idx.size()<<table[7].size()<<endl;
    vector<int> adj[num];
    for(int i = 1; i < 17; i++){
        if(table[i].size() == 0) continue;
        for(int j = 0; j < table[i].size() - 1; j++){
            for(int k = j + 1; k < table[i].size(); k++){
                int diff = 0;
                for(int l = 0; l < i; l++){
                    if(table[i][j][l] != table[i][k][l])
                        diff++;
                }
                if(diff == 1){
                    adj[dic[table[i][j]]].push_back(dic[table[i][k]]);
                    adj[dic[table[i][k]]].push_back(dic[table[i][j]]);
                }
            }
        }
    }
    string start, end;
    // vector<vector<int> > output;
    // int a = 18;
    int a = 0;
    while(cin >> start >> end){
        if(a++) cout << endl;
        if(dic.find(end) == dic.end() || dic.find(start) == dic.end())
            cout << "No solution." << endl;
        else{
            vector<int> ans = bfs(dic[start], dic[end], adj);
            if(ans.size() == 0){
                cout << "No solution." << endl;
            }
            else{
                // output.push_back(ans);
                for(int i = ans.size() - 1; i >= 0; i--){
                    cout << idx[ans[i]] << endl;
                }
            }
        }
        // cout<<endl;
        // a--;
        // if(a == 0)  break;
    }

    // for(int i = 0; i < output.size(); i++){
    //     for(int j = output[i].size()-1; j >= 0; j--){
    //         cout<<idx[output[i][j]]<<endl;
    //     }
    //     cout<<endl;
    // }

    // for(int i = 0; i < num; i++){
    //     cout<<idx[i]<<" "<<i<<": ";
    //     for(int j = 0; j < adj[i].size(); j++){
    //         cout << adj[i][j] << " ";
    //     }
    //     cout<<endl;
    // }


}