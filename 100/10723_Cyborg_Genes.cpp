#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
//最長子字串
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1664
//https://www.cnblogs.com/scau20110726/archive/2012/10/01/2709781.html
unsigned int cnt[32][32], dp[32][32];

int main() {
    int t, p = 1;
    cin >> t;
    cin.ignore();
    while (t--) {
        string s1, s2;
        getline(cin, s1), getline(cin, s2);
        int n = s1.size(), m = s2.size();
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                cnt[i][j] = dp[i][j] = 0;

        for (int i = 0; i <= n; i++) cnt[i][0] = 1;
        for (int j = 0; j <= m; j++) cnt[0][j] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;   //長度
                    cnt[i][j] = cnt[i - 1][j - 1];     //次數
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    if (dp[i - 1][j] > dp[i][j - 1]) {
                        cnt[i][j] = cnt[i - 1][j];
                    }
                    else if (dp[i - 1][j] < dp[i][j - 1]) {
                        cnt[i][j] = cnt[i][j - 1];
                    }
                    else {
                        cnt[i][j] = cnt[i - 1][j] + cnt[i][j - 1];
                    }
                }
            }
        }
        cout << "Case #" << p++ << ": " << n + m - dp[n][m] << " " << cnt[n][m] << endl;

    }
}
