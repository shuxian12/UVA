#include<iostream>
#include<vector>
using namespace std;

// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=99999999&page=show_problem&category=0&problem=1239
// https://blog.csdn.net/dark_cy/article/details/88698736

int main() {
    string s;
    while (cin >> s && s != ".") {
        vector<int> next(s.length() + 1, 0);
        int j = 0, k = -1;
        next[0] = -1;
        while (j < s.length()) {
            if (k == -1 || s[j] == s[k]) {
                j++, k++;
                // next[j] = s[j] == s[k] ? next[k] : k;
                next[j] = k;
            }
            else {
                k = next[k];
            }
        }

        // for (int i = 0; i < next.size(); i++) {
        //     cout << next[i] << " ";
        // }
        // cout << endl;

        cout << (s.length() % (s.length() - next[s.length()]) == 0 ? s.length() / (s.length() - next[s.length()]) : 1) << endl;
    }
}