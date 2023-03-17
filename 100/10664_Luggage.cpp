#include<iostream>
#include<vector>
#include<sstream>
using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1605
// https://knightzone.studio/2020/04/16/4816/uva：10664－luggage/

int main() {
    int task;
    cin >> task;
    cin.ignore();
    while (task--) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        int num = 0, sum = 0;
        vector<int> luggage;
        luggage.push_back(0);
        while (iss >> num) {
            luggage.push_back(num);
            sum += num;
        }
        if (sum % 2 == 1) {
            cout << "NO" << endl;
            continue;
        }

        vector<bool> dp(sum + 1, false);
        dp[0] = true;
        for (int i = 1; i < luggage.size(); i++) {
            for (int j = sum; j >= luggage[i]; j--) {
                if (dp[j - luggage[i]]) {
                    dp[j] = true;
                }
            }
        }

        if (dp[sum / 2]) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

}