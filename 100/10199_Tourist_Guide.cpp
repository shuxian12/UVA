#include<iostream>
#include<vector>
#include<map>
#include<cstring>

using namespace std;

// http://mobcs.blogspot.com/2015/05/uva-10199-tourist-guide.html
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1140

vector<vector<int> > graph;
vector<string> cut_vertex;
map<string, int> node_map;
vector<string> node_list;
int visited[105], dfn[105], low[105], counter = 0, depth = 0;

void dfs(int node, int pre){
    visited[node] = 1;
    int child = 0;
    dfn[node] = low[node] = depth++;
    bool is_cut = false;

    for(int i = 0; i < graph[node].size(); i++){
        int next = graph[node][i];
        if(!visited[next]){
            child++;
            dfs(next, node);
            low[node] = min(low[node], low[next]);
            if(low[next] >= dfn[node])
                is_cut = true;
        }
        else{
            low[node] = min(low[node], dfn[next]);  // back edge, 比較 自己的祖先 和 走回去的點的dfn, 誰比較老
        }
    }

    if(pre < 0 && child > 1 || pre > -1 && is_cut)    // root 且有兩個以上的child, 或者不是root 且是cut vertex
        cut_vertex.push_back(node_list[node]);

}

int main(){
    int node_num, path_num, case_num = 1;
    // cin >> node_num;
    while(cin >> node_num && node_num){
        if(case_num > 1)
            cout << endl;
        memset(visited, 0, sizeof(visited));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        for(int i = 0; i < node_num; i++){
            string node_name;
            cin >> node_name;
            node_map[node_name] = i;
            node_list.push_back(node_name);
        }
        cin >> path_num;

        graph.resize(node_num);
        for(int i = 0; i < path_num; i++){
            string node1, node2;
            cin >> node1 >> node2;
            graph[node_map[node1]].push_back(node_map[node2]);
            graph[node_map[node2]].push_back(node_map[node1]);
        }
        depth = 0;
        for(int i = 0; i < node_num; i++){
            if(!visited[i]){
                dfs(i, -1);
            }
        }
        sort(cut_vertex.begin(), cut_vertex.end());
        cout << "City map #" << case_num++ << ": " << cut_vertex.size() << " camera(s) found" << endl;
        for(string pos : cut_vertex){
            cout << pos << "\n";
        }

        //debug
        // for(int i = 0; i < node_num; i++){
        //     cout << node_list[i] << " " << dfn[i] << " " << low[i] << endl;
        // }
        node_map.clear(), node_list.clear(), graph.clear(), cut_vertex.clear();
        // cout << endl;
    }
}