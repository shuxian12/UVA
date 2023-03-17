#include<iostream>

using namespace std;

// http://kos74185foracm.blogspot.com/2011/12/10127-ones.html
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1068

int main() {
    int q, r, num;
    while (cin >> num) {
        q = 1;
        r = 1;
        while (r % num) {
            r = r * 10 + 1;
            r %= num;
            // cout<<r<<endl;
            q++;
        }
        cout << q << endl;
    }
}

