#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
// #define pii pair<int,int>
using namespace std;

struct edge{
    int  v, w;
    edge(int v, int w){
        this->v = v;
        this->w = w;
    }
};

vector<edge> edges[1005];
vector<int> dag[1005];
int dist[1005], dp[1005];
bool done[1005];
int n, m;

struct cmp{
    bool operator()(edge a, edge b){  // w, v
        return a.w > b.w;
    }
};

void dijkstra(int s){
    // bool done[n+1];
    memset(done, 0, sizeof(done));
    memset(dist, 63, sizeof(dist));
    priority_queue<edge, vector<edge>, cmp> q;
    q.push(edge(s, 0));
    dist[s] = 0;

    while(!q.empty()){
        int cur = q.top().v;
        q.pop();
        if(done[cur]) continue;
        done[cur] = 1;
        for(edge e : edges[cur]){
            if(dist[e.v] > dist[cur] + e.w){
                dist[e.v] = dist[cur] + e.w;
                // cout<<"dist["<<e.v<<"] = "<<dist[e.v]<<endl;
                q.push(edge(e.v, dist[e.v]));
            }
        }

    }
}

int dfs(int u){
    if(dp[u] != -1) return dp[u];
    if(u == 2)  return 1;
    int ans = 0;
    for(int v : dag[u]){
        ans += dfs(v);
    }
    return dp[u] = ans;
}

int main(){
    while(cin >> n && n){
        // memset(dist, 63, sizeof(dist));
        // memset(dag, 0, sizeof(dag));
        memset(dp, -1, sizeof(dp));
        cin >> m;
        int u, v, w;
        for(int i = 0; i < m; i++){
            cin >> u >> v >> w;
            edges[u].push_back(edge(v, w));
            edges[v].push_back(edge(u, w));
        }

        dijkstra(2);

        for(int i = 1; i <= n; i++){
            for(edge e : edges[i]){
                if(dist[i] > dist[e.v])     //d(2->B)<d(2->A)則AB這條路徑可以走
                    dag[i].push_back(e.v);
            }
        }

        int ans = dfs(1);
        cout << ans << endl;
        for(int i = 0; i <= n; i++){
            dag[i].clear();
            edges[i].clear();
        }
    }
}
