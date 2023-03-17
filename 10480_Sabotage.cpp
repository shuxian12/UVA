#include<iostream>
#include<vector>
#include<queue>
#include<cstring>

using namespace std;

// https://blog.csdn.net/qq_43680965/article/details/106790346
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1421

const int INF = 0x3f3f3f3f;

int capacity[55][55], flow[55][55], parent[55], argument[55];
int u[505], v[505];
int s = 1, t = 2;

void maxflow(int n){
    memset(flow, 0, sizeof(flow));
    // int maxflow = 0;

    while(true){
        memset(argument, 0, sizeof(argument));
        queue<int> q;
        argument[s] = INF;
        q.push(s);

        while(!q.empty()){
            int cur = q.front();
            q.pop();
            if(cur == t)    break;  // 找到增广路了
            //if(u==t) break;//求最大流时需加上此句 ，本题不能加 ???
            for(int i = 1; i <= n; i++){
                if(!argument[i] && capacity[cur][i] > flow[cur][i]){
                    parent[i] = cur;
                    argument[i] = min(argument[cur], capacity[cur][i] - flow[cur][i]);
                    q.push(i);
                }
            }
        }
        if(argument[t] == 0)    break; // 没有增广路了
        for(int i = t; i != s; i = parent[i]){
            flow[parent[i]][i] += argument[t];
            flow[i][parent[i]] -= argument[t];
        }
        // maxflow += argument[t];
    }
}


int main(){
    int n, m, w;
    while(cin >> n >> m && n && m){
        memset(capacity, 0, sizeof(capacity));
        for(int i = 0; i < m; i++){
            cin >> u[i] >> v[i] >> w;
            capacity[u[i]][v[i]] = capacity[v[i]][u[i]] = w;
        }
        maxflow(n);
        int sum = 0;
        for(int i = 0; i < m; i++){
            if(argument[u[i]] && !argument[v[i]] || !argument[u[i]] && argument[v[i]]){     //求残余网络中：一个方向还残余容量，另一个方向没有容量的边
                cout << u[i] << " " << v[i] << endl;
                // sum += capacity[u[i]][v[i]];
            }
        }
        cout << endl;
    }
}