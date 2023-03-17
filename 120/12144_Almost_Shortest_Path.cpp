#include<iostream>
#include<queue>
#include<vector>
#include<cstring>

using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3296
// https://github.com/topd97/UVa-1/blob/master/volume121/12144%20-%20Almost%20Shortest%20Path.cpp

struct edge{
    int u, v, w, shortest;
    edge(int u, int v, int w){
        this->u = u;
        this->v = v;
        this->w = w;
        shortest = 0;
    }
};

vector<edge> edges[505];
vector<pair<int, int> > pre[505];
// vector<edge*>  pre[505];
int dist[505];
bool in_queue[505];
int n, m;

void spfa(int source, int end, bool first){
    memset(dist, 63, sizeof(dist));     // 0x3f3f3f3f memset bytewise
    memset(in_queue, 0, sizeof(in_queue));
    queue<int> q;
    q.push(source), dist[source] = 0, in_queue[source] = 1;

    while(!q.empty()){
        int cur = q.front();
        q.pop(), in_queue[cur] = 0;
        for(int i = 0; i < edges[cur].size(); i++){
            edge e = edges[cur][i];
            if(e.shortest) continue;    // shortest path, almost shortest path can't pass
            if(dist[e.v] > dist[cur] + e.w){
                dist[e.v] = dist[cur] + e.w;
                pre[e.v].clear();   // 只能是最短的路徑，所以如果更改值的話要清空，只要其他路徑一樣長都可以被加入
                if(!in_queue[e.v]){
                    q.push(e.v);
                    in_queue[e.v] = 1;
                }
            }

            if(first && dist[e.v] == dist[cur] + e.w){
                pre[e.v].push_back(make_pair(cur, i));
            }
        }
    }
}

void cut(int source, int end){
    memset(in_queue, 0, sizeof(in_queue));
    queue<int> q;
    q.push(end), in_queue[end] = 1;

    while(!q.empty()){
        int cur = q.front();
        q.pop(), in_queue[cur] = 0;
        for(auto p : pre[cur]){     // p = (u, i)
            edges[p.first][p.second].shortest = 1;
            if(!in_queue[p.first]){
                q.push(p.first);
                in_queue[p.first] = 1;
            }
        }
    }

}

int main(){
    int start, end, u, v, w;
    while(cin >> n >> m && n && m){
        for(int i = 0; i < n; i++){
            edges[i].clear();
            pre[i].clear();
        }
        cin >> start >> end;
        for(int i = 0; i < m; i++){
            cin >> u >> v >> w;
            edges[u].push_back(edge(u, v, w));
        }

        spfa(start, end, 1);
        cut(start, end);
        spfa(start, end, 0);
        cout << (dist[end] == 0x3f3f3f3f ? -1 : dist[end]) << endl;
    }
}