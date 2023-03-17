#include<iostream>
#include<vector>

using namespace std;

vector<int> fib;

void Fib(int num){
    bool flag = false;
    cout<< num << " = ";
    for(int i = 43; i >= 1; i--){
        if(num >= fib[i]){
            num -= fib[i];
            cout << 1;
            flag = true;
        }
        else if(flag)
            cout << 0;
    }
    cout<< " (fib)" << endl;
}

int main(){
    for(int i = 0; i < 44; i++){
        if(i == 0 || i == 1){
            fib.push_back(1);
        }
        else{
            fib.push_back(fib[i-1] + fib[i-2]);
        }
    }
    
    int N, num;
    cin >> N;
    while(N--){
        cin >> num;
        Fib(num);
    }
}