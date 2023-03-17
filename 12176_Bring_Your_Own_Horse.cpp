#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3328
// https://morris821028.github.io/2014/07/06/oj/uva/uva-12176/
// https://hackmd.io/@konchin/ryhgIlhMu#查詢LCA

struct edge{
    int x, y, w;
    edge(int a = 0, int b = 0, int c = 0){
        x = a;
        y = b;
        w = c;
    }
    bool operator<(const edge& a) const{
        return  w < a.w;
    }
};

vector<edge> road(100005);
vector<edge> tree[3005];
int p[3005], r[3005];

int find_set(int x){
    if(x != p[x])
        p[x] = find_set(p[x]);
    return p[x];
}

void union_set(int px, int py){
    if(r[px] > r[py])
        r[px] += r[py], p[py] = px;
    else
        r[py] += r[px], p[px] = py;
}

void kruscal(int n, int R){
    sort(road.begin(), road.begin() + R);
    int count = 0;
    for(int i = 0; i <= n; i++){
        p[i] = i, r[i] = 1;
        tree[i].clear();
    }

    for(int i = 0; i < R; i++){
        int x = find_set(road[i].x), y = find_set(road[i].y);
        if(x != y){
            union_set(x, y);
            tree[road[i].x].push_back(edge(road[i].x, road[i].y, road[i].w));
            tree[road[i].y].push_back(edge(road[i].y, road[i].x, road[i].w));
            count++;
            if(count == n - 1)  break;
        }
    }
}

int acient[3005][20], acient_w[3005][20];
int treeLevel[3005], treePath[3005];    // treePath[level] = node

void dfs(int u, int p, int level){
    treeLevel[u] = level, treePath[level] = u;

    // 先建立祖先表
    for(int i = 1; (1 << i) < level; i++){  //從2^1開始建立，因為2^0 = 1，已經建立好了(上一輪dfs)
        acient[u][i] = treePath[level - (1 << i)];   // 紀錄 u 的第 2^i 倍祖先
        acient_w[u][i] = max(acient_w[u][i - 1], acient_w[acient[u][i - 1]][i - 1]);  // 最無法理解的部分
    }

    for(int i = 0; i < tree[u].size(); i++){
        int v = tree[u][i].y;   // v 是 u 的子節點
        if(v != p){
            acient[v][0] = u;
            acient_w[v][0] = tree[u][i].w;
            dfs(v, u, level + 1);
        }
    }
}

int getLCA(int u, int v){
    int level_u = treeLevel[u], level_v = treeLevel[v];
    int ans = 0;
    // 接著調整兩個詢問節點的高度，先想辦法調整到兩個節點到水平高度
    while(u != v && level_u != level_v){
        for(int i = 15; i >= 0; i--){
            if(abs(level_u - level_v) >= (1 << i)){
                if(level_u > level_v){
                    ans = max(ans, acient_w[u][i]); // 只會走過這一次所以要比大小
                    u = acient[u][i];
                    level_u -= (1 << i);    // 調整高度 2的次方
                }
                else{
                    ans = max(ans, acient_w[v][i]);
                    v = acient[v][i];
                    level_v -= (1 << i);
                }
            }
        }
    }
    while(u != v){
        ans = max(ans, acient_w[u][0]);
        u = acient[u][0];
        level_u -= 1; //2^0
        ans = max(ans, acient_w[v][0]);
        v = acient[v][0];
        level_v -= 1;
    }
    return ans;
}

int main(){
    // cout<<(1<<5)<<endl;
    int task, N, R, Q, cases = 1;
    cin >> task;
    while(task--){
        cin >> N >> R;
        for(int i = 0; i < R; i++){
            cin >> road[i].x >> road[i].y >> road[i].w;
        }
        kruscal(N, R);
        memset(acient, 0, sizeof(acient));
        memset(acient_w, 0, sizeof(acient_w));
        dfs(1, -1, 1);  // root = 1, parent = -1, level = 1

        cout << "Case " << cases++ << endl;
        cin >> Q;
        while(Q--){
            int k, t;
            cin >> k >> t;
            cout << getLCA(k, t) << endl;
        }
        cout << endl;
    }

}