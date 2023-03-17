#include<iostream>
#include<vector>
#include<queue>

using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1271

const int INF = 0x3f3f3f3f;
int capacity[205][205], flow[205][205], parent[205], argument[205];
int t;

int maxflow(int n){
    memset(flow, 0, sizeof(flow));
    int maxflow = 0;

    while(true){
        memset(argument, 0, sizeof(argument));
        queue<int> q;
        argument[0] = INF;
        q.push(0);

        while(!q.empty()){
            int cur = q.front();
            q.pop();
            if(cur == t)    break;  // 找到增广路了
            for(int i = 1; i <= n; i++){
                if(!argument[i] && capacity[cur][i] > flow[cur][i]){
                    parent[i] = cur;
                    argument[i] = min(argument[cur], capacity[cur][i] - flow[cur][i]);
                    q.push(i);
                }
            }
        }
        if(argument[t] == 0)    break; // 没有增广路了
        for(int i = t; i != 0; i = parent[i]){
            flow[parent[i]][i] += argument[t];
            flow[i][parent[i]] -= argument[t];
        }
        maxflow += argument[t];
    }
    return maxflow;
}

int main(){
    int n, m, u, v, w;
    while(cin >> n){
        memset(capacity, 0, sizeof(capacity));
        t = 2 * n + 1;      // t is end/sink
        for(int i = 1; i <= n; i++){
            cin >> w;
            capacity[i][i + n] = w;     // 自己到自己的容量 u --> u -> u'   
        }
        cin >> m;
        for(int i = 1; i <= m; i++){
            cin >> u >> v >> w;
            capacity[u + n][v] = w;    // u->v 的容量
        }

        int b, d;
        cin >> b >> d;
        for(int i = 1; i <= b; i++){
            cin >> u;
            capacity[0][u] = INF;   // 0 is the source
        }
        for(int i = 1; i <= d; i++){
            cin >> u;
            capacity[u + n][t] = INF; // t is the sink
        }
        cout << maxflow(t) << endl;
    }
}