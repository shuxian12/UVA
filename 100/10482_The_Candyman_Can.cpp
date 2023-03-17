#include<iostream>
#include<vector>
using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1423
// https://blog.csdn.net/J_Dark/article/details/8736920

int main() {
    int task = 0, n = 1;
    cin >> task;
    while (task--) {
        int candy_num, sum = 0;
        cin >> candy_num;
        vector<int> candy(candy_num + 1, 0);
        for (int i = 1; i <= candy_num; i++) {
            cin >> candy[i];
            sum += candy[i];
        }
        vector<vector<bool> > dp(sum + 1, vector<bool>(sum + 1, 0));
        dp[0][0] = 1;   //第三個人拿走全部的candy
        for (int i = 1; i <= candy_num; i++) {
            for (int j = sum; j >= 0; j--) {
                for (int k = sum-j; k >= 0; k--) {
                    if (dp[j][k]) {
                        dp[j + candy[i]][k] = 1;
                        dp[j][k + candy[i]] = 1;
                    }
                }
            }
        }
        cout<<sum<<endl;
        for(int i = 0; i <= sum; i++){
            for(int j = 0; j <= sum; j++){
                cout<<dp[i][j]<<" ";
            }
            cout<<endl;
        }

        int ans = INT_MAX;
        for (int j = sum; j >= 0; j--) {
            for (int k = sum-j; k >= 0; k--) {
                if (dp[j][k]) {
                    ans = min(ans, max(j, max(k, sum - j - k)) - min(j, min(k, sum - j - k)));
                }
            }
        }
        cout << "Case " << n++ << ": " << ans << endl;
    }

}


// function<bool(int, int)> solve = [&](int j, int k) {
//     // Check if the solution to this subproblem has already been computed
//     if (dp.count(j) && dp[j].count(k)) return dp[j][k];

//     // Otherwise, try to solve the subproblem using smaller subproblems
//     for (int i = 1; i <= candy_num; i++) {
//         // If the smaller subproblem can be solved, then this subproblem can also be solved
//         if (dp[j][k] = solve(j, k)) {
//             // Store the solution to this subproblem in the map for future reference
//             dp[j + candy[i]][k] = 1;
//             dp[j][k + candy[i]] = 1;
//         }
//     }
//     // Return the solution to this subproblem
//     return dp[j][k];
// };
