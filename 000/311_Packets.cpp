#include<iostream>
#include<vector>
using namespace std;
//https://yuihuang.com/zj-c110/
//https://hackmd.io/@bensoncoding/BJZ6mES7D
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=247

int main(){
    vector<int> num(7, 0);

    while(true){
        int count = 0;
        for(int i = 1; i < 7; i++){
            cin >> num[i];
            count += num[i];
        }
        if(count == 0) break;
        int tmp[2] = { 0,0 };
        int sum = 0;
        if(num[6]){
            sum += num[6];
        }
        if(num[5]){
            sum += num[5];
            tmp[0] += num[5] * 11;
        }
        if(num[4]){
            sum += num[4];
            tmp[1] += num[4] * 5;
        }
        if(num[3]){
            sum += num[3] / 4;
            int remain = num[3] % 4, lea = 0;
            if(remain != 0){
                sum++;
                tmp[1] += 7 - (remain) * 2;
                tmp[0] += 8 - remain;
            }
        }
        if(num[2] > tmp[1]){
            num[2] -= tmp[1];
            if(num[2] % 9 == 0){
                sum += num[2] / 9;
            }
            else{
                sum += num[2] / 9 + 1;
                tmp[0] += (9 - num[2] % 9) * 4;
            }
        }
        else if(num[2] < tmp[1]){
            tmp[0] += (tmp[1] - num[2]) * 4;
        }

        if(num[1] > tmp[0]){
            num[1] -= tmp[0];
            if(num[1] % 36 == 0){
                sum += num[1] / 36;
            }
            else{
                sum += num[1] / 36 + 1;
            }
        }
        cout << sum << endl;
    }

}