#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1161

using namespace std;

int main(){
    int num, digit = 1;
    vector<int> table(3000, 0), ans(1001, 0);
    // vector<string> mul(1000, "");   //mul[0]="1", mul[1]="1", mul[2]="2";
    ans[0] = ans[1] = 1, ans[2] = 2, table[0] = 2;  
    for(int i = 3; i <= 1000; i++){
        for(int j = 0; j < digit; j++){
            table[j] *= i;
            // cout<<"i"<<i<<": "<<table[j]<<endl;
        }
        for(int j = 0; j < digit; j++){
            table[j + 1] += table[j] / 10;
            if(j >= digit - 1 && table[j + 1] != 0) digit++;
            table[j] %= 10;
            ans[i] += table[j];
        }
        // for(int j = digit-1; j >= 0; j--){
        //     mul[i] += to_string(table[j]);
        // }
        // cout<<"mul "<<i<<" : "<< mul[i]<<endl;
    }
    while(cin>>num)
        cout<<ans[num]<<endl;
}