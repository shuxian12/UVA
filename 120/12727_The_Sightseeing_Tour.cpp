#include<iostream>
#include<cstring>
#define ll long long
using namespace std;

// https://github.com/morris821028/UVa/blob/master/volume127/12727%20-%20The%20Sightseeing%20Tour.cpp
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4579

// struct binocular{
//     int a, b, c;    // a: left, b: right, c: cost
//     binocular(int a, int b, int c) :a(a), b(b), c(c){}
//     bool operator < (const binocular& x)const{  // sort by right，if right is same, sort by left
//         if(b != x.b)    return b < x.b;
//         return a < x.a;
//     }
// };

struct binocular{
    int a, b, c;
    binocular(int a = 0, int b = 0, int c = 0) :
        a(a), b(b), c(c){
    }
    bool operator<(const binocular& x) const{
        if(b != x.b)	return b < x.b;
        return a < x.a;
    }
};

int n, m, k, a, b, c;   // n = tourist place, m = binocular, k = groups of tourists
binocular bin[32];
int cost[305];

void dfs(int l, int r, int idx, int c){ //c : cost, idx : binocular index
    if(r == n){
        cost[c] = 1;    // 如果r已經到達最後一個觀光景點，就把cost[c]設為1
        return;
    }
    for(int i = idx; i < m; i++){
        if(r + 1 >= bin[i].a && bin[i].a > l && bin[i].b > r)     // 如果binocular的左邊界在l和r之間，且右邊界大於r
            dfs(r + 1, bin[i].b, i, c + bin[i].c);  // 就從binocular的右邊界開始dfs
    }
}

ll f(int x){
    if(x <= 300)    // 30隻binocular，一隻最多10元，所以最多花300元
        return cost[x];
    return cost[300] + (ll)(x - 300) * (cost[300] - cost[299]);     // 如果x大於300，就把300~x的cost算出來
}

int main(){
    int total_task, task = 1, pre;
    cin >> total_task;
    while(total_task--){
        cin >> n >> m >> k;
        for(int i = 0; i < m; i++){
            cin >> a >> b >> c;
            bin[i] = binocular(a, b, c);
        }
        sort(bin, bin + m);
        memset(cost, 0, sizeof(cost));

        dfs(0, 0, 0, 0);

        for(int i = 1, pre = 0; i <= 300; i++){     // cost一開始只是先代表可不可以花到錢，所以要把cost[i]變成會花的錢的累積
            if(cost[i] == 1){   // 看cost[i]是否可以被花到錢，如果可以，cost就等於 前一個cost加 i ，i 是花的錢
                pre = i;
                cost[i] = cost[i - 1] + i;
            }
            else{
                cost[i] = cost[i - 1] + pre;    // 如果cost[i]不可以被花到錢，就把cost[i]設為前一個cost加上前一個(pre)可以花的錢
            }
        }
        ll ans = 0;
        for(int i = 0; i < k; i++){     // 計算每個group的cost
            int x, y;
            cin >> x >> y;
            ans += f(y) - f(x - 1);   // f(y) - f(x-1) = y~x的cost
        }
        cout << "Case #" << task++ << ": " << ans << endl;
    }
}