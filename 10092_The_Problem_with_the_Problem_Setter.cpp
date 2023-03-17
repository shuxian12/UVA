#include <queue>
#include <vector>
#include <iostream>

using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1033
// https://github.com/morris821028/UVa/blob/master/volume100/10092%20-%20The%20Problem%20with%20the%20Problem%20Setter.cpp

struct Node{
    int x, y, v;// x->y, v  //v 尚且可以流動的量
    int next;
} edge[500005];

int e, head[1100], dis[1100], pre[1100], record[1100];  // head[i] is the index of the first edge of node i

void addEdge(int x, int y, int v){
    edge[e].x = x, edge[e].y = y, edge[e].v = v;
    edge[e].next = head[x], head[x] = e++;  // next point to the next edge of node x
    edge[e].x = y, edge[e].y = x, edge[e].v = 0;    // v = 0 means the reverse edge
    edge[e].next = head[y], head[y] = e++;
    //print edge e
    // cout << "edge[" << e-2 << "].x = " << edge[e-2].x << ", edge[" << e-2 << "].y = " << edge[e-2].y << ", edge[" << e-2 << "].v = " << edge[e-2].v << ", edge[" << e-2 << "].next = " << edge[e-2].next << endl;
    // cout<< "edge[" << e-1 << "].x = " << edge[e-1].x << ", edge[" << e-1 << "].y = " << edge[e-1].y << ", edge[" << e-1 << "].v = " << edge[e-1].v << ", edge[" << e-1 << "].next = " << edge[e-1].next << endl;
}
int maxflow(int s, int t){
    int flow = 0;
    int i, j, x, y;
    while(1){
        memset(dis, 0, sizeof(dis));
        dis[s] = 0xffff; // oo
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()){
            x = Q.front();
            Q.pop();
            for(i = head[x]; i != -1; i = edge[i].next){
                y = edge[i].y;
                if(dis[y] == 0 && edge[i].v > 0){   // y 沒走過，且還有流量
                    pre[y] = x, record[y] = i;      // record 紀錄的是edge的index
                    dis[y] = min(dis[x], edge[i].v);
                    Q.push(y);
                }
            }
            if(dis[t])  break;  // 如果dis[t]存在，代表找到了一條路徑會到達終點
        }
        if(dis[t] == 0) break;  // 如果dis[t]不存在，代表找不到增廣路徑，結束
        flow += dis[t];
        for(x = t; x != s; x = pre[x]){     // x = 第幾個點，record[x] = 第幾條edge 
            int ri = record[x];
            edge[ri].v -= dis[t];
            edge[ri ^ 1].v += dis[t];     // ri^1是ri的反向邊
        }
    }
    return flow;
}
int main(){
    int n, m, x, y;     // n: number of categories, m: number of problems
    int i, j, k;
    while(cin >> n >> m && n && m){
        e = 0;  // edge index
        memset(head, -1, sizeof(head));
        int st = 0, ed = n + m + 1;
        int sum = 0;
        for(i = 1; i <= n; i++){
            cin >> x;
            addEdge(m + i, ed, x);    //category -> end
            sum += x;   //total number of problems to be assigned
        }

        for(i = 1; i <= m; i++){
            cin >> x;
            while(x--){
                cin >> y;
                addEdge(i, m + y, 1); //problem i -> category m+y
            }
            addEdge(st, i, 1);  //start -> problem i
        }
        //print head
        // for(int i = 0; i < ed+1; i++){
        //     cout << "head[" << i << "] = " << head[i] << endl;
        // }

        int flow = maxflow(st, ed);
        if(flow == sum){
            cout << 1 << endl;
            vector<int> res[n];
            for(i = 1; i <= m; i++){
                for(j = head[i]; j != -1; j = edge[j].next){    //j = -1 代表這個點全部的edge都走過了
                    if(edge[j].v == 0 && edge[j].y > m){        //edge[j].y > m 為到category的邊
                        res[edge[j].y - m - 1].push_back(i);    //i為problem的index
                        break;
                    }
                }
            }
            for(i = 0; i < n; i++){
                for(j = 0; j < res[i].size(); j++){
                    if(j)   cout << " ";
                    cout << res[i][j];
                }
                cout << endl;
            }
        }
        else
            cout << 0 << endl;
    }
}
// 3 15
// 3 3 4
// 2 1 2
// 1 3
// 1 3
// 1 3
// 1 3
// 3 1 2 3
// 2 2 3
// 2 1 3
// 1 2
// 1 2
// 2 1 2
// 2 1 3
// 2 1 2
// 1 1
// 3 1 2 3
// 0 0

