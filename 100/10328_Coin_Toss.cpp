#include<iostream>
#include<stdio.h>
using namespace std;

// https://slidesplayer.com/slide/16929946/
// https://blog.csdn.net/pibaixinghei/article/details/52231462
// https://wyg1997.blog.csdn.net/article/details/52214919
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1269

int dp[101][101][12] = { 0 };   //31位

int main(){
    for(int i = 0; i < 101; i++){
        dp[i][0][0] = dp[0][i][0] = 1;
    }
    for(int i = 1; i < 101; i++){
        for(int j = 1; j < 101; j++){
            for(int p = 0; p < 11; p++){
                dp[i][j][p] = dp[i - 1][j][p] * 2;
            }

            if(i == j + 1){
                dp[i][j][0] -= 1;
            }
            else if(i > j + 1){
                for(int p = 0; p < 11; p++){
                    dp[i][j][p] -= dp[i - 1 - j - 1][j][p]; //[最多j次][反][j次 正][正]
                }
            }

            for(int p = 0; p < 11; p++){
                while(dp[i][j][p] < 0){
                    dp[i][j][p] += 1000;
                    dp[i][j][p + 1]--;
                }
                dp[i][j][p + 1] += dp[i][j][p] / 1000;
                dp[i][j][p] %= 1000;
            }
        }
    }

    int n, k;
    while(cin >> n >> k){
        int ans[12] = { 0 };
        for(int i = 0; i < 11; i++){
            ans[i] = dp[n][n][i] - dp[n][k - 1][i];
        }
        for(int i = 0; i < 11; i++){
            while(ans[i] < 0){
                ans[i] += 1000;
                ans[i + 1]--;
            }
        }
        int i = 11;
        while(!ans[i] && i > 0)  i--;
        cout << ans[i--];
        while(i >= 0){
            printf("%03d", ans[i--]);
        }
        cout << endl;
    }
}