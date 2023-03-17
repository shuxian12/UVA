#include<iostream>
#include<stdio.h>
using namespace std;

// https://blog.csdn.net/metaphysis/article/details/6525829?spm=1001.2101.3001.6650.5
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1098
// https://blog.csdn.net/mobius_strip/article/details/39269541

int t[151][151][51] = { 0 };    //"累積和" 括號對數n，括號深度最高可以到達m //題目要算括號對數n，深度為m的括號組合數
// ans[n][m] = t[n][m] - t[n][m-1]
int main(){
    for(int i = 0; i < 151; i++){
        t[0][i][0] = 1;
    }
    for(int j = 1; j <= 150; j++){
        for(int i = 1; i <= 150; i++){
            for(int k = 0; k < i; k++){
                for(int p = 0; p < 25; p++){
                    for(int q = 0; q < 25; q++){
                        t[i][j][p + q] += t[k][j - 1][p] * t[i - k - 1][j][q];
                    }
                }
                for(int p = 0; p < 50; p++){
                    t[i][j][p + 1] += t[i][j][p] / 10000;
                    t[i][j][p] %= 10000;
                }
            }
        }
    }

    int n, m;
    while(cin >> n >> m){
        if(n % 2 == 1){
            cout << 0 << endl;
            continue;
        }
        int ans[51];
        for(int i = 0; i < 50; i++){
            ans[i] = t[n / 2][m][i] - t[n / 2][m - 1][i]; //要記得除以2才會是括號對數
        }
        for(int i = 0; i < 50; i++){
            while(ans[i] < 0){
                ans[i] += 10000;
                ans[i + 1]--;
            }
        }
        int i = 49;
        while(i > 0 && !ans[i]) i--;
        cout << ans[i--];
        while(i >= 0){
            printf("%04d", ans[i--]);
        }
        cout << endl;
    }

}
