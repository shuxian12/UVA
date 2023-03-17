#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>
#include<cmath>
#define eps 1e-5

using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1745
// https://github.com/morris821028/UVa/blob/master/volume108/10804%20-%20Gopher%20Strategy.cpp

double g[100][100];
int head[105], pre[105], dist[105], argu[105], record[105];
int n, m, k, e;
double nx[105], ny[105], mx[105], my[105];
// int capacity[105][105], flow[105][105];

struct node{
    int x, y, v;
    int next;
}edge[10005];

void addEdge(int x, int y, int v){
    edge[e].x = x, edge[e].y = y, edge[e].v = v;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].v = 0;
    edge[e].next = head[y], head[y] = e++;
}

int maxflow(int s, int t){
    int maxflow = 0;
    int i, j, x, y;
    while(true){
        memset(dist, 0, sizeof(dist));
        dist[s] = 0xffff;
        queue<int> q;
        q.push(s);

        while(!q.empty()){
            x = q.front(), q.pop();

            for(i = head[x]; i != -1; i = edge[i].next){
                y = edge[i].y;
                if(dist[y] == 0 && edge[i].v > 0){
                    pre[y] = x, record[y] = i;
                    dist[y] = min(dist[x], edge[i].v);
                    q.push(y);
                }
            }
            if(dist[t])    break;
        }
        if(dist[t] == 0)    break;
        maxflow += dist[t];
        for(i = t; i != s; i = pre[i]){
            edge[record[i]].v -= dist[t];
            edge[record[i] ^ 1].v += dist[t];
        }
    }
    return maxflow;
}

// int maxflow2(int n){
//     memset(flow, 0, sizeof(flow));
//     int maxflow = 0;

//     while(true){
//         memset(argu, 0, sizeof(argu));
//         argu[0] = 0xffff;
//         queue<int> q;
//         q.push(0);

//         while(!q.empty()){
//             int cur = q.front();
//             q.pop();

//             if(cur == n)    break;
//             for(int i = 1; i <= n; i++){
//                 if(argu[i] == 0 && capacity[cur][i] > flow[cur][i]){
//                     argu[i] = min(argu[cur], capacity[cur][i] - flow[cur][i]);
//                     q.push(i);
//                     pre[i] = cur;
//                 }
//             }
//         }
//         if(argu[n] == 0)    break;
//         maxflow += argu[n];
//         for(int i = n; i != 0; i = pre[i]){
//             flow[pre[i]][i] += argu[n];
//             flow[i][pre[i]] -= argu[n];
//         }
//     }
//     return maxflow;
// }

bool solve(double limit){
    e = 0;
    memset(head, -1, sizeof(head));
    // memset(capacity, 0, sizeof(capacity));

    for(int i = 0; i < n; i++){
        addEdge(0, i + 1, 1);
        // capacity[0][i+1] = 1;
        for(int j = 0; j < m; j++){
            if(g[i][j] <= limit){
                // capacity[i+1][j+n+1] = 1;
                addEdge(i + 1, j + n + 1, 1);
            }
        }
    }

    for(int i = 0; i < m; i++){     // hole to sink
        addEdge(i + n + 1, n + m + 1, 1);
        // capacity[i+n+1][n+m+1] = 1;
    }

    int flow = maxflow(0, n + m + 1);
    
    // int flow = maxflow2(n + m + 1);
    // cout<<flow<<endl;
    if(flow >= n - k)    return true;   // 可以繼續下修，直到找到最小的limit
    else    return false;   // 匹配數 小於 地鼠數量 - 可接受失去數量，上修
}

int main(){
    int task_sum, task = 1;
    double l, r, mid;
    cin >> task_sum;
    while(task_sum--){
        cin >> n >> m >> k;
        for(int i = 0; i < n; i++){
            cin >> nx[i] >> ny[i];  // mouse
        }
        for(int i = 0; i < m; i++){
            cin >> mx[i] >> my[i];  // hole
        }
        l = sqrt(pow(nx[0] - mx[0], 2) + pow(ny[0] - my[0], 2)), r = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                g[i][j] = sqrt(pow(nx[i] - mx[j], 2) + pow(ny[i] - my[j], 2));
                l = min(g[i][j], l);
                r = max(g[i][j], r);
            }
        }

        cout << "Case #" << task++ << ":\n";
        if((n == 0 && m == 0) || n == k || n == 0)
            cout << "0.000\n";
        else if(n - k > m)    // 地鼠數量 - 可接受失去數量 大於 洞數量
            cout << "Too bad.\n";
        else{
            int cnt = 0;
            while(fabs(l - r) > eps && cnt < 100){
                mid = (l + r) / 2;
                // cout<<mid<<endl;
                if(solve(mid))     //匹配數大於等於地鼠數量 - 可接受失去數量，下修
                    r = mid;
                else
                    l = mid;
                cnt++;
            }
            printf("%.3f\n", l);  //輸出時，四捨五入到小數點後三位
        }
        cout << endl;
    }

}