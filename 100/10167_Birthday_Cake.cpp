#include<iostream>

using namespace std;

// https://blog.csdn.net/mobius_strip/article/details/37559921
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1108

struct p{
    double x;
    double y;
};

p point[10000];

int main(){
    int n;
    while(cin >> n && n){
        for(int i = 0; i < 2 * n; i++){
            cin >> point[i].x >> point[i].y;
        }

        int flag = 1;
        for(int i = -500; flag && i <= 500; i++){   //i可以從0開始
            for(int j = -500; flag && j <= 500; j++){
                int l = 0, r = 0;
                for(int k = 0; k < 2 * n; k++){
                    if(point[k].x * i + point[k].y * j > 0){
                        l++;
                    }
                    else if(point[k].x * i + point[k].y * j < 0){
                        r++;
                    }
                }
                if(l == n && r == n){
                    cout << i << " " << j << endl;
                    flag = 0;
                }
            }
        }
    }
}