#include<iostream>
#include<string>
using namespace std;

// https://blog.csdn.net/remember_your_dream/article/details/70669867
// https://blog.csdn.net/tianyuhang123/article/details/54919715
// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=99999999&page=show_problem&category=0&problem=660

int main() {
    int task;
    cin >> task;
    while (task--) {
        string line;
        cin >> line;
        int len = line.length();
        int i = 0, j = 1, k = 0;
        while (i < len && j < len) {
            while (k < len && line[(i + k) % len] == line[(j + k) % len])
                k++;
            if (k == len)    break;
            if (line[(i + k) % len] > line[(j + k) % len])
                i = i + k + 1;
            else
                j = j + k + 1;

            if (i == j)  j++;
            k = 0;
        }
        cout << i + 1 << endl;
    }
}