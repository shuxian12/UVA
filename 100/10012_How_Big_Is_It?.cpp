#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=953
// https://blog.csdn.net/tengfei461807914/article/details/53143336

double circle[9], X[9], ans;
int m;

double dist(double r1, double r2){
    double x = fabs(r1 - r2), y = r1 + r2;
    return sqrt(y * y - x * x);
}

void solve(){
    ans = 0x3f3f3f3f;
    do{
        memset(X, 0, sizeof(X));
        X[1] = circle[1];
        double tmp = -1;
        for(int i = 2; i <= m; i++){
            double x_ = circle[i];
            for(int j = 1; j < i; j++){
                x_ = max(x_, X[j] + dist(circle[i], circle[j]));    // 找距離最遠的那個
                if(x_ + circle[i] > ans) goto NEXT; // 剪枝
            }
            X[i] = x_;
        }

        for(int i = 1; i <= m; i++){
            tmp = max(tmp, X[i] + circle[i]);   // 找最後一個圓的距離
        }
        ans = min(ans, tmp);
    NEXT:;
    } while(next_permutation(circle + 1, circle + m + 1));
}

int main(){
    int task;
    cin >> task;
    while(task--){
        cin >> m;
        for(int i = 1; i <= m; i++){
            cin >> circle[i];
        }
        sort(circle + 1, circle + m + 1);
        solve();
        printf("%.3f\n", ans);
    }
}