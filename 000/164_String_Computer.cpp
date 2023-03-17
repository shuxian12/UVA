#include<iostream>
#include<vector>
#include<string>
#include<cstring>

//https://blog.csdn.net/mobius_strip/article/details/38306789
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=100

using namespace std;
int dp[21][21], op[21][21];
string s1, s2;
void path(int a, int b){
    if(a == 0 && b == 0) return;
    if(op[a][b] == 1){  // delete 刪掉s1[a] 位置為j+1
        path(a - 1, b);
        cout << "D" << s1[a - 1] << (b + 1 > 9 ? to_string(b + 1) : "0" + to_string(b + 1));
    }
    else if(op[a][b] == 2){ // insert 在s1的b位置插入s2的b位置的字元
        path(a, b - 1);
        cout << "I" << s2[b - 1] << (b > 9 ? to_string(b) : "0" + to_string(b));
    }
    else if(op[a][b] == 3){
        path(a - 1, b - 1);
        cout << "C" << s2[b - 1] << (b > 9 ? to_string(b) : "0" + to_string(b));
    }
    else path(a - 1, b - 1);
}

int main(){
    while(cin >> s1 && s1 != "#"){
        cin >> s2;
        memset(dp, 0, sizeof(dp));
        memset(op, 0, sizeof(op));
        int n = s1.length(), m = s2.length();

        for(int i = 0; i <= n; i++){
            dp[i][0] = i;
            op[i][0] = 1;
        }
        for(int j = 0; j <= m; j++){
            dp[0][j] = j;
            op[0][j] = 2;
        }
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(s1[i - 1] != s2[j - 1]){
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    op[i][j] = 3;   //change
                }
                else{
                    dp[i][j] = dp[i - 1][j - 1];
                    op[i][j] = 0;   //啥都不幹
                }

                if(dp[i - 1][j] + 1 < dp[i][j]){
                    dp[i][j] = dp[i - 1][j] + 1;
                    op[i][j] = 1;   //delete
                }
                else if(dp[i][j - 1] + 1 < dp[i][j]){   //這裡應該用if，而不是else if!!!!
                    dp[i][j] = dp[i][j - 1] + 1;
                    op[i][j] = 2;   //insert
                }
            }
        }
        path(n, m);
        cout << "E" << endl;
    }
}