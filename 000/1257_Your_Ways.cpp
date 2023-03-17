#include<iostream>
#include<cstring>

using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=3698

int main(){
    int road[1005][1005] = {};
    const int mod = 2552;
    int n, m, k, q, a, b, c, d, task;
    for(int i = 0; i <= 1001; i++){
        road[i][0] = road[0][i] = 1;
    }
    for(int i = 1; i <= 1001; i++){
        for(int j = 1; j <= 1001; j++){
            road[i][j] = (road[i - 1][j] + road[i][j - 1]) % mod;
        }
    }

    cin >> task;
    while(task--){
        cin >> n >> m >> k;
        while(k--){
            cin >> q;
            int ans = road[n][m];
            while(q--){
                cin >> a >> b >> c >> d;
                ans -= (road[a][b] * road[n - c][m - d]) % mod;
                // 因為是矩形，所以可以把dp[c][d]看成是原點，dp[c][d] ～ dp[n][m]就等於dp[0][0] ～ dp[n - c][m - d]
                ans = (ans + mod) % mod;
            }
            cout << ans << endl;
        }
    }
}