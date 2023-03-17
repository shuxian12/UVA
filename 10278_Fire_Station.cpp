#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
#include<sstream>

using namespace std;

// https://github.com/topd97/UVa-1/blob/master/volume102/10278%20-%20Fire%20Station.cpp
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1219

struct edge{
    int v, w;
    edge(int v, int w){
        this->v = v;
        this->w = w;
    }
};

vector<edge> roads[505];
vector<int> dist;
bool in_queue[505];

void spfa(int source){
    memset(in_queue, false, sizeof(in_queue));
    queue<int> q;
    q.push(source), in_queue[source] = true, dist[source] = 0;

    while(!q.empty()){
        int cur = q.front();
        q.pop(), in_queue[cur] = false;

        for(edge e : roads[cur]){
            if(dist[e.v] > dist[cur] + e.w){
                dist[e.v] = dist[cur] + e.w;
                if(!in_queue[e.v]){
                    q.push(e.v);
                    in_queue[e.v] = true;
                }
            }
        }
    }
}

int main(){
    int task, f_num, s_num;
    vector<int> f_station;
    cin >> task;
    while(task--){
        cin >> f_num >> s_num;
        f_station.clear(), f_station.resize(f_num);
        for(int i = 0; i < f_num; i++){
            cin >> f_station[i];
        }
        for(int i = 0; i <= s_num; i++){
            roads[i].clear();
        }
        cin.ignore();
        string line;
        while(getline(cin, line) && line != ""){
            istringstream iss(line);
            int a, b, w;
            iss >> a >> b >> w;
            roads[a].push_back(edge(b, w));
            roads[b].push_back(edge(a, w));
        }

        dist.clear(), dist.resize(s_num + 1, 0x3f3f3f3f);
        for(int i = 0; i < f_num; i++){     //每個點到最近消防站的位置
            spfa(f_station[i]);
        }

        int ans = 0x3f3f3f3f, max_s = 0;
        vector<int> origin = dist;
        for(int i = 1; i <= s_num; i++){    //要找建立新的消防站，可以使得所有消防站到所有的地方的距离最短的地方
            spfa(i);
            int max_dist = 0;
            for(int j = 1; j <= s_num; j++){
                if(dist[j] > max_dist)
                    max_dist = dist[j];     //裡面要找最大值
            }
            dist = origin;          //要把dist還原
            if(max_dist < ans){     //外面要找最小值
                ans = max_dist;
                max_s = i;
            }
        }
        cout << max_s << endl;

        if(task) cout << endl;
    }
}