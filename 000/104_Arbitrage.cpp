#include<iostream>
#include<cstring>
#include<vector>
#include<stack>

using namespace std;

// https://github.com/NaiveRed/Problem-solving/blob/master/UVa/104%20-%20Arbitrage.cpp
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=40

double D[25][25][25];
int path[25][25][25];

void FW(int n){
    for(int step = 2; step <= n; step++){
        for(int k = 1; k <= n; k++){
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= n; j++){
                    // print D
                    // cout<<"D["<<i<<"]["<<j<<"]["<<step<<"] = "<<D[i][k][step - 1] * D[k][j][1]<<endl;
                    if(D[i][j][step] < D[i][k][step - 1] * D[k][j][1]){
                        D[i][j][step] = D[i][k][step - 1] * D[k][j][1];
                        path[i][j][step] = k;
                    }
                }
            }
        }

        //print D
        // for(int i = 1; i <= n; i++){
        //     for(int j = 1; j <= n; j++){
        //         cout << D[i][j][step] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl<< endl;

        vector<int> ans;
        for(int i = 1; i <= n; i++){
            if(D[i][i][step] > 1.01){
                int cur = i;
                for(int j = step; j >= 2; j--){
                    cur = path[i][cur][j];
                    ans.push_back(cur);
                }
                cout << i;
                for(int j = ans.size() - 1; j >= 0; j--){
                    cout << " " << ans[j];
                }
                cout << " " << i << endl;
                return;
            }
        }
    }
    cout << "no arbitrage sequence exists" << endl;
}

int main(){
    int n;
    while(cin >> n){
        memset(D, 0, sizeof(D));
        memset(path, 0, sizeof(path));
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(i == j)  D[i][j][1] = 1;
                else        cin >> D[i][j][1];
                // path[i][j][1] = i;
            }
        }
        FW(n);
    }
}