#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1078

int main() {
    cin.tie(0);
    int n;
    double x;
    while (cin >> n) {
        if (n == 0) break;
        int a[n];
        int sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> x;

            //因為為了避免浮點數的誤差，所以先乘以100，再四捨五入
            a[i] = (int)round(x * 100);
            sum += a[i];
        }
        sort(a, a + n, less<int>());
        int avg = sum / n;
        int remain = sum - avg * n; //平均無法整除的餘數
        double ans = 0.0;
        //付較多錢的人，多支付無法整除的部分，ans為付錢和拿錢的總和，所以最後要除以2
        for (int i = n - 1; i >= n - remain; i--) {
            ans += abs(a[i] - avg - 1);
        }
        for (int i = n - remain - 1; i >= 0; i--) {
            ans += abs(a[i] - avg);
        }
        //因為答案只能小數點後兩位，所以要 fix<<setprecision(2)
        cout << "$" << fixed << setprecision(2) << ans / 200.0 << "\n";
    }
}