#include<iostream>
#include<vector>

using namespace std;

string sub(string a, string b){
    int n = a.length(), m = b.length(), i, j, k, carry = 0;
    vector<int> table(n, 0);
    for(i = m-1, j = 0, k = n-1; i >= 0; i--, j++, k--){
        table[j] += a[k] - b[i];
        // cout<<table[j]<<endl;
        if(table[j] < 0){
            table[j] += 10;
            table[j+1] = -1;
        }
    }
    for(; k >= 0; k--, j++){
        table[j] += a[k] - '0';
        if(table[j] < 0){
            table[j] += 10;
            table[j+1] = -1;
        }
    }
    string ans = "";
    int q = n-1;
    while(table[q] == 0) q--;
    for(; q >= 0; q--){
        ans += table[q] + '0';
    }
    if(ans == "") ans = "0";
    // cout<<ans<<endl;
    return ans;
}

vector<string> div(string a, string b){
    int n = a.length(), m = b.length(), div = stoi(b.data()),i, j = 0, k, dividend = stoi(a.substr(0, m));
    vector<string> ans(2, "");
    if(n < m || (n == m && dividend < div)){
        ans[0] = "0";
        ans[1] = a;
        // cout<<ans[0]<<" "<<ans[1]<<endl;
        return ans;
    }
    vector<int> table;
    if(dividend < div){
        dividend = dividend * 10 + a[m] - '0';
        i = m+1;
    }
    else i = m;
    cout<<dividend<<" "<<div<<" "<<i<<j<<endl;
    while(i <= n){
        if(dividend < div){
            table.push_back(0);
            dividend = i < n ? dividend * 10 + a[i] - '0' : dividend;
            i++, j++;
            continue;
        }
        table.push_back(dividend/div);
        dividend = dividend % div;
        // cout<<i<<" "<<j<<" "<<table[j-1]<< " "<< dividend<<endl;
        dividend = i < n ? dividend * 10 + a[i] - '0' : dividend;
        // cout<<dividend<<endl;
        i++, j++;
    }
    // for(int a : table){
    //     cout<<(char)(a+'0');
    // }
    // cout<<endl;
    // cout<<j<<endl;
    ans[1] = to_string(dividend);
    for(i = 0; i < j; i++){
        ans[0] += table[i] + '0';
    }
    // cout<<ans[0]<<" "<<ans[1]<<endl;
    return ans;
}

int main(){
    string a, b;
    int num = 1;
    while(cin>>a>>b && a != "0" && b != "0"){
        cout<<"Case "<<num++<<":\n"<<a<<" / "<<b<<"\n";
        vector<string> p;
        while(true){
            vector<string> ans = div(a, b);
            a = b, b = ans[1], p.push_back(ans[0]);
            cout<<ans[0]<<" "<<ans[1]<<endl;
            if(ans[1] == "0") break;
        }
        int k = p.size();
        vector<int> dash(k, 0);
        dash[k-1] = 1;
        // cout<<p[k-1]<<" "<<sub(p[k-1], "1").length()<<endl;
        dash[k-2] = sub(p[k-1], "1").length() + 3 + dash[k-1];
        for(int i = p.size()-3; i >= 0; i--){
            dash[i] = dash[i+1] + p[i+1].length() + 3;
        }
        p[p.size()-1] = sub(p[p.size()-1], "1");
        // for(int t : dash) cout<<t<<" ";
        // cout<<endl;
        // for(string a : p){
        //     cout<<a<<" ";
        // }
        // cout<<endl;

        int d = p[0].length() + 3 + dash[0];
        
        for(int i = 0; i < k; i++){
            string ans1 = "", ans2 = "";
            int t;
            if(dash[i] % 2 == 0) t = dash[i] / 2;
            else t = dash[i] / 2;
            for(int j = 0; j < t; j++) ans1 += ".";
            ans1 += "1";
            for(int j = 0; j < d - t -1; j++) ans1 += ".";
            for(int j = 0; j < dash[i]; j++) ans2 += "-";
            ans2 += ".+.";
            for(int j = p[i].length()-1; j>=0; j--){
                ans2 += p[i][j];
            }
            for(int j = 0; d - ans2.length(); j++) ans2 += ".";
            for(int j = d-1; j >= 0; j--){
                cout<<ans1[j];
            }
            cout<<endl;
            for(int j = d-1; j >= 0; j--){
                cout<<ans2[j];
            }
            cout<<endl;
        }
        for(int i = 0; i < d-1; i++) cout<<".";
        cout<<"1\n";

    //     bool flag = false;
    //     for(int i = 0; i < k; i++){
    //         if(i != 0) d += p[i].length() + 3;
    //         for(int j = 0; j < d; j++){
    //             cout<<".";
    //         }
    //         int t;
    //         if(dash[i] % 2 == 0) t = dash[i] / 2 - 1;
    //         else t = dash[i] / 2;
    //         for(int j = 0; j < dash[i]; j++){
    //             if(j == t) cout<<"1";
    //             else cout<<".";
    //         }
    //         cout<<endl;
    //         if(i > 0){
    //             if(p[i].length()>1){
    //                 for(int j = 0; j < d-4-p[i].length()+1; j++)
    //                 cout<<".";
    //             }
    //             else{
    //                 for(int j = 0; j < d-4; j++)
    //                 cout<<".";
    //             }
                
    //             cout<<p[i]<<".+.";
    //         }
    //         else{
    //             cout<<p[i]<<".+.";
    //         }
    //         for(int j = 0; j < dash[i]; j++)  cout<<"-";
    //         cout<<endl;
    //     }
    //     for(int j = 0; j < d; j++){
    //         cout<<".";
    //     }
    //     cout<<"1\n";
    }
    

}