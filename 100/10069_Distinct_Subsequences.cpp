#include<iostream>
#include<string>
#include<cstring>
#include<stdio.h>
#include<vector>

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1010

using namespace std;

string add(string a, string b){
    if(a.length() < b.length()) swap(a, b);
    int lena = a.length(), lenb = b.length(), i;
    vector<int> table(lena + 1, 0);
    for(i = 0; i < lenb; i++){
        table[i] += (a[lena - 1 - i] - '0') + (b[lenb - 1 - i] - '0');
        // cout<<table[i]<<" = "<< (a[lena-1-i] - '0') << " + " << (b[lenb-1-i] - '0') << endl;
        table[i + 1] += table[i] / 10;
        table[i] %= 10;
    }
    for(; i < lena; i++){
        // cout<<table[i]<<" = "<< (a[lena-1-i] - '0')<< endl;
        table[i] += (a[lena - 1 - i] - '0');
        table[i + 1] += table[i] / 10;
        table[i] %= 10;
    }
    string ans = "";
    int p = lena;
    while(table[p] == 0)    p--;
    for(int i = p; i >= 0; i--){
        ans += to_string(table[i]);
    }
    return ans;
}

// int dp[105][10005][35];
string dp[105][10005];
int main(){
    string s1, s2;
    int num;
    cin >> num;
    while(num--){
        cin >> s2 >> s1;
        int n = s1.length(), m = s2.length();
        for(int i = 0; i <= n; i++){
            dp[i][0] = "0";
        }
        for(int j = 0; j <= m; j++){
            // dp[0][j][0] = 1;
            dp[0][j] = "1";
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(s1[i - 1] == s2[j - 1]){
                    // for(int k = 0; k < 35; k++){
                    //     dp[i][j][k] = dp[i-1][j-1][k] + dp[i][j-1][k];
                    // }
                    // for(int k = 0; k < 35; k++){
                    //     dp[i][j][k+1] += dp[i][j][k]/1000000;
                    //     dp[i][j][k] %= 1000000;
                    // }
                    // dp[i][j] = dp[i][j-1] + dp[i-1][j-1];
                    dp[i][j] = add(dp[i][j - 1], dp[i - 1][j - 1]);
                }
                else{
                    // for(int k = 0; k < 35; k++){
                    //     dp[i][j][k] = dp[i][j-1][k];
                    // }
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }

        // int tmp = 34;
        // while(dp[n][m][tmp] == 0 && tmp > 0) tmp--;
        // cout<<dp[n][m][tmp--];
        // for(int i = tmp; i >= 0; i--){
        //     printf("%06d", dp[n][m][i]);
        // }
        // cout<<endl;

        cout << dp[n][m] << endl;
    }
}