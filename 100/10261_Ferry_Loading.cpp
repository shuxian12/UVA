#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1202

vector<int> car, sum;
vector<vector<int> > dp;
queue<int> q;
int length;
void backtrace(int i, int len) {
    if (i == 0) return;
    if (sum[i] - len <= length && dp[i - 1][len] == 1) {
        backtrace(i - 1, len);
        q.push(0);
    }
    else if (len - car[i] >= 0 && dp[i - 1][len - car[i]] == 1) {
        backtrace(i - 1, len - car[i]);
        q.push(1);
    }
}

int main() {
    int task;
    cin >> task;
    while (task--) {
        int num, final_car, final_len;
        cin >> length;
        length *= 100;
        sum.push_back(0), car.push_back(0);
        while (cin >> num && num > 0) {
            car.push_back(num);
            sum.push_back(num);
            sum[sum.size() - 1] += sum[sum.size() - 2];
        }
        // sum.erase(sum.begin());
        // for(int i : sum) cout<<i<<" ";
        dp.resize(sum.size(), vector<int>(length + 1, 0));
        dp[0][0] = 1;
        final_car = final_len = 0;
        for (int i = 1; i < dp.size(); i++) {
            for (int j = 0; j <= length; j++) {
                if ((j - car[i] >= 0 && dp[i - 1][j - car[i]] == 1) || (sum[i] - j <= length && dp[i - 1][j] == 1)) {
                    dp[i][j] = 1;
                    final_car = i;
                    final_len = j;
                }
            }
            if (final_car != i) break;
        }
        cout << final_car << endl;
        backtrace(final_car, final_len);
        // cout<<q.size()<<endl;
        int first;
        if (!q.empty())  first = q.front();
        while (!q.empty()) {
            if (q.front() == first)
                cout << "port\n";
            else
                cout << "starboard\n";
            q.pop();
        }
        if (task) cout << endl;
        car.clear(), sum.clear(), dp.clear();
    }
}
