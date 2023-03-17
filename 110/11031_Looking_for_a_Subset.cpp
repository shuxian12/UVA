#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

// https://morris821028.github.io/2014/06/12/oj/uva/uva-11031/
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1972
// 做LDS，再做greedy，而不是LIS

bool cmp(const int &a,const int &b){
    return a > b;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int set = 1, subset = 1, num, in, task;
    while(cin >> num >> task){
        if(num == 0 && task == 0) break;
        vector<int> a;
        while(num--){
            cin >> in;
            a.insert(a.begin(), in);
        }

        int N = (int)a.size(), maxLDS = 1, L = 1;
        vector<int> v, dp(N + 1, 1);
        v.push_back(a[0]);

        for(int i = 1; i < N; i++){
            if(a[i] < v.back()){
                v.push_back(a[i]);
                dp[i] = ++L;
                maxLDS = max(maxLDS, L);
            }
            else{
                auto it = lower_bound(v.begin(), v.end(), a[i], cmp);
                *it = a[i];
                dp[i] = (int)(it - v.begin() + 1);
                // int mid = (0 + L) / 2;
                // if(a[i] < v[mid]){
                //     for(int j = mid; j < L; j++){
                //         if(a[i] >= v[j]){
                //             v[j] = a[i];
                //             dp[i] = j + 1;
                //             break;
                //         }
                //     }
                // }
                // else{
                //     for(int j = 0; j <= mid; j++){
                //         if(a[i] >= v[j]){
                //             v[j] = a[i];
                //             dp[i] = j + 1;
                //             break;
                //         }
                //     }
                // }
            }

        }

        printf("Set %d:\n", set++);
        subset = 1;

        while(task--){
            printf("  Subset %d:\n", subset++);
            vector<int> ans;
            cin >> num;

            if(num > maxLDS){
                printf("    Impossible\n");
                continue;
            }
            
            printf("   ");
            int prevA = -0x3f3f3f3f;    //INT_MIN???
            for(int j = N - 1; j >= 0 && num; j--){
                if(dp[j] >= num && prevA < a[j]){
                    printf(" %d", a[j]);
                    num--, prevA = a[j];
                }
            }
            printf("\n");
        }
    }
}
