#include<iostream>
#include<vector>

using namespace std;

// https://github.com/ajahuang/UVa/blob/master/UVa%2010690%20-%20Expression%20Again.cpp
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1631

int main(){
    int N, M;
    while(cin >> N >> M){
        int sum = 0, plus = 0;
        vector<int> table(N + M + 1, 0);
        for(int i = 1; i <= N + M; i++){
            cin >> table[i];
            sum += table[i];
            table[i] += 50; // -50 ~ 50
        }
        vector<vector<bool> > dp(N + M + 1, vector<bool>(5000 + 1, 0)); //幾個數字，和為多少
        dp[0][0] = 1;
        for(int i = 1; i <= N + M; i++){
            for(int j = min(i, N); j >= 1; j--){    //只算x_i的和 0<i<=N
                for(int k = 0; k <= 5000; k++){ // 0 ~ 5000 應該改道10000 好像也不用，因為就最多50個值可以放而已
                    if(dp[j - 1][k])
                        dp[j][k + table[i]] = 1;
                }
            }
        }
        int maxi = INT_MIN, mini = INT_MAX;
        for(int i = 0; i <= 5000; i++){
            if(dp[N][i]){
                int tmp = i - 50 * N;
                maxi = max(maxi, tmp * (sum - tmp));
                mini = min(mini, tmp * (sum - tmp));
            }
        }
        cout << maxi << " " << mini << endl;
    }
}