#include<iostream>
#include<vector>
#include<string>

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1265

using namespace std;

int main(){
    string input, q;
    int a1, a2, num, sum, caseCount = 1;
    while(cin >> input){
        cout << "Case " << caseCount++ << ":" << endl;

        q = input;
        if(input.length() > 1){
            for(int i = 1; i < input.length(); i++){
                // char a = input[i] - '0';
                // char b = input[i-1] - '0';
                if(input[i] != input[i - 1]){
                    q[i] = q[i - 1] + 1;
                }
                else{
                    q[i] = q[i - 1];
                }
            }
        }

        cin >> num;
        for(int i = 0; i < num; i++){
            cin >> a1 >> a2;
            if(q[a1] == q[a2]){
                cout << "Yes" << endl;
                // cout<<q[big]<<q[small]<<endl;
            }
            else{
                cout << "No" << endl;
                // cout<<q[big]<<q[small]<<endl;
            }
        }
    }
    // cin>>input;
    // cin>>num;
    // cin>>a1>>a2;
    // q = input;
    // if(input.length() > 1){
    //     for(int i = 1; i < input.length(); i++){
    //         // char a = input[i] - '0';
    //         // char b = input[i-1] - '0';
    //         if(input[i] != input[i-1]){
    //             q[i] = q[i-1] + 1;
    //         }
    //         else{
    //             q[i] = q[i-1];
    //         }
    //     }
    // }
    // int big = max(a1, a2), small = min(a1, a2);
    // cout<<q<<endl;
    // if(q[big] == q[small]){
    //     cout<<"Yes"<<endl;
    //     cout<<q[big]<<q[small]<<endl;
    // }
    // else{
    //     cout<<"No"<<endl;
    //     cout<<q[big]<<q[small]<<endl;
    // }
}