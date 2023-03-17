#include<iostream>
#include<vector>
#include<string>
#include<queue>

using namespace std;

// https://morris821028.github.io/2014/08/28/oj/uva/uva-721/
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=662


vector<pair<int, int> > g[1000002], g_v[1000002];
int dist[1000002];
bool in_queue[1000002];

int spfa(int source, int n, vector<pair<int, int> > g[]){
    memset(dist, 0X3f3f3f3f, sizeof(dist));
    memset(in_queue, false, sizeof(in_queue));
    // for (int i = 0; i < n; i++) {
    //     dist[i] = 1LL<<60, inq[i] = 0;
    // }
    queue<int> q;
    q.push(source);
    dist[source] = 0, in_queue[source] = true;

    while(!q.empty()){
        int cur = q.front();
        q.pop();
        in_queue[cur] = false;
        for(auto& p : g[cur]){
            int next = p.first, w = p.second;
            if(dist[next] > dist[cur] + w){
                dist[next] = dist[cur] + w;
                if(!in_queue[next]){
                    q.push(next);
                    in_queue[next] = true;
                }
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans += dist[i];
    }
    return ans;
}

int main(){
    int task, n, m, u, v, w;
    cin >> task;
    while(task--){
        cin >> n >> m;
        for(int i = 0; i < m; i++){
            cin >> u >> v >> w;
            g[u].push_back(make_pair(v, w));
            g_v[v].push_back(make_pair(u, w));
        }

        int ans = spfa(1, n, g) + spfa(1, n, g_v);
        cout << ans << endl;
        for(int i = 0; i < n; i++){
            g[i].clear();
            g_v[i].clear();
        }
    }
}