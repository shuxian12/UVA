#include<iostream>
#include<vector>
#include<sstream>
#include<cstring>
using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=393
// https://github.com/morris821028/UVa/blob/master/volume004/452%20-%20Project%20Scheduling.cpp

// void dfs(int u, int n){
//     for(int i = 0; i < n; i++){
//         if(Map[u][i] && dist[i] < dist[u] + cost[i]){
//             dist[i] = dist[u] + cost[i];
//             dfs(i, n);
//         }
//     }
// }

int main(){
    int task, days, size = 0, j;
    string line, connect;
    char node;
    cin >> task;
    cin.ignore();
    cin.ignore();
    while(task--){
        int cost[27] = { 0 }, dist[27] = { 0 };
        int Map[27][27] = { 0 };
        // memset(Map, 0, sizeof(Map));
        // memset(cost, 0, sizeof(cost));
        // memset(dist, 0, sizeof(dist));
        int count[27] = { 0 }, done[27] = { 0 };
        size = 0;
        while(getline(cin, line) && line != ""){
            istringstream iss(line);
            connect = "";
            iss >> node >> days >> connect;
            cost[node - 'A'] = days, done[node - 'A'] = 1;
            for(char i : connect){
                Map[node - 'A'][count[node - 'A']++] = i - 'A';     // 反著建圖
            }
            size++;
        }

        int flag = 1, ans = 0, max = 0;
        int used[26] = { 0 };

        while(flag){    // 判斷是否還會再次更新dist, 如果沒有更新，就代表已經沒有路徑可以走了
            flag = 0;
            for(int i = 0; i < 26; i++){
                if(used[i] == 0 && cost[i] != 0){ // done[i] == 1, 還沒被用過，且點存在，用cost udebug會錯
                    max = 0;    // reset max，只找這一輪的最大值
                    for(j = 0; j < count[i]; j++){  // adj的個數
                        if(used[Map[i][j]] == 0)
                            break;
                        if(dist[Map[i][j]] > max)   // j -> i 的最大值
                            max = dist[Map[i][j]];
                    }
                    if(j == count[i]){
                        dist[i] = max + cost[i];
                        if(dist[i] > ans)
                            ans = dist[i];
                        used[i] = 1;
                        flag = 1;
                    }
                }
            }
        }

        // for(int i = 0; i < size; i++){  // 因為有可能有多個起點，或是不知道起點是誰，所以要從每個點開始dfs
        //     dfs(i, size);
        // }
        // int ans = 0;
        // for(int i = 0; i < size; i++){
        //     if(ans < dist[i])
        //         ans = dist[i];
        // }
        cout << ans << endl;
        if(task)
            cout << endl;
    }
}