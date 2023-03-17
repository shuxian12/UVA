#include<iostream>
#include<vector>
#include<cstring>

// https://www.larrysprognotes.com/UVa-10721/
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1662

using namespace std;

long long int bc[51][51][51]; //int64

int main(){
    memset(bc, 0, sizeof(bc));
    for(int i = 1; i <= 50; i++){   // 當只有一個 bar 時，對於 m >= n，dp[n][1][m] = 1 ( 只有一個黑色的 bar )
        for(int h = i; h <= 50; h++){
            bc[i][1][h] = 1;
        }
    }
    for(int n = 1; n <= 50; n++){
        for(int k = 1; k <= 50; k++){
            for(int m = 1; m <= 50; m++){
                if(m > n){
                    bc[n][k][m] = bc[n][k][n];
                    continue;
                }
                for(int i = 1; i <= m; i++){  //  bar的寬度最多只能到m
                    bc[n][k][m] += bc[n - i][k - 1][m];
                }
            }
        }
    }

    int n, k, m;
    while(cin >> n >> k >> m)
        cout << bc[n][k][m] << endl;
}