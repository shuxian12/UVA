#include<iostream>
#include<vector>
#include<map>
#include<queue>

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=985

using namespace std;
vector<int> adjacency_list[10000];
map<string, int> mp;

void bfs(int start, int node_size, int m){    //start = mp[erdos], node_size = mp.size()
    queue<int> q;
    int distance[node_size];
    for(int i = 0; i < node_size; i++)
        distance[i] = -1;
    distance[start] = 0;
    q.push(start);
    while(!q.empty()){
        int current = q.front();
        q.pop();
        for(int i = 0; i < adjacency_list[current].size(); i++){
            int next = adjacency_list[current][i];
            if(distance[next] == -1){
                distance[next] = distance[current] + 1;
                q.push(next);
            }
        }
    }

    for(int i = 0; i < m; i++){
        string name;
        getline(cin, name);
        if(distance[mp[name]] == -1)
            cout << name << " infinity" << endl;
        else
            cout << name << ' ' << distance[mp[name]] << endl;
    }
}

int main(){
    int n, m, count = 0, num, task = 1;
    cin >> num;
    while(num--){
        cin >> n >> m;
        // cout<<n<<' '<<m<<endl;
        cin.ignore();
        mp.clear();
        string line;
        // count = 0;
        for(int i = 0; i < n;i++){
            getline(cin, line);
            int start = 0, end = 0;
            vector<int> index;  //每一行的作者的index
            while(line[start] != ':'){
                end = start;
                while(line[end] != ':' && line[end] != ',' || line[end - 1] != '.'){
                    end++;
                }
                string name = line.substr(start, end - start);
                // cout<<name<<endl;
                if(mp.find(name) == mp.end())
                    mp[name] = count++;
                index.push_back(mp[name]);
                start = end;
                while(line[start] < 'A' || line[start] > 'Z'){
                    if(line[start] != ':')
                        start++;    //跳過空白還有標點符號
                    else
                        break;
                }
            }

            for(int j = 0; j < index.size(); j++){
                for(int k = 0; k < j; k++){
                    adjacency_list[index[j]].push_back(index[k]);
                    adjacency_list[index[k]].push_back(index[j]);
                }
            }
            index.clear();
        }
        // for(int i = 0; i < count; i++){
        //     for(int j = 0; j < adjacency_list[i].size(); j++){
        //         cout << adjacency_list[i][j] << ' ';
        //     }
        //     cout << endl;
        // }
        cout << "Scenario " << task++ << endl;
        bfs(mp["Erdos, P."], count, m);
        for(int i = 0; i < count; i++)
            adjacency_list[i].clear();
    }
}