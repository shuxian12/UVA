#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=964
// https://blog.csdn.net/synapse7/article/details/12125411
// https://blog.csdn.net/csuhoward/article/details/37764411

string mul(string a, string b){
    if(a == "0" || b == "0")    return "0";
    vector<int> table(a.size() + b.size(), 0);
    int n = a.size(), m = b.size();
    for(int i = n-1; i >= 0; i--){
        for(int j = m-1; j >= 0; j--){
            int k = n+m-2-i-j;
            table[k] += (a[i] - '0') * (b[j] - '0');
            table[k+1] += table[k] / 10;
            table[k] %= 10;
            // cout<<table[k]<<" "<<table[k+1]<<endl;
        }
    }
    int q = n+m-1;
    string ans = "";
    while(table[q] == 0)    q--;
    for(int i = q; i >= 0; i--){
        // cout<<table[i];
        ans += to_string(table[i]);
    }
    // cout<<endl;
    // cout<<ans<<endl;;
    return ans;
}

string add(string a, string b){
    int n = a.size(), m = b.size(), carry, i, j, k;
    if(n < m){
        string tmp = b;
        b = a, a = tmp;
        n = a.size(), m = b.size();
    }
    vector<int> table(n+1, 0);
    for(i = m-1, k = n-1,j = 0; i >= 0; i--, j++, k--){
        table[j] += (a[k] - '0') + (b[i] - '0');
        table[j+1] += table[j] / 10;
        table[j] %= 10;
    }
    // cout<<j<<endl;
    for(; k >= 0; k--, j++){
        table[j] += a[k] - '0';
        table[j+1] += table[j] / 10;
        table[j] %= 10;
    }
    int q = n;
    string ans = "";
    while(table[q] == 0)    q--;
    for(int i = q; i >= 0; i--){
        // cout<<table[i];
        ans += to_string(table[i]);
    }
    // cout<<endl<<ans<<endl;
    return ans;
}

string sub(string a, string b){
    int n = a.size(), m = b.size(), i, j, k;
    vector<int> table(n, 0);
    for(i = m-1, k = n-1, j = 0; i >= 0; i--, j++, k--){
        table[j] += (a[k] - '0') - (b[i] - '0');
        if(table[j] < 0){
            table[j] += 10;
            table[j+1]--;
        }
    }
    for(; k >= 0; k--, j++){
        table[j] += a[k] - '0';
        if(table[j] < 0){
            table[j] += 10;
            table[j+1]--;
        }
    }
    int q = n-1;
    string ans = "";
    while(table[q] == 0 && q > -1)    q--;
    if(q == -1) return "0";
    for(int i = q; i >= 0; i--){
        // cout<<table[i];
        ans += to_string(table[i]);
    }
    // cout<<endl<<ans<<endl;
    return ans;
}

// string div(string a, string b){
//     int n = a.size(), m = b.size(), dividend = 0, div = stoi(b),i, j, r;
//     vector<int> table;
//     for(i = 0, j = 0; i < n; i++, j++){
//         dividend = dividend * 10 + (a[i] - '0');
//         // cout<<dividend<<"/"<<a[i]<<endl;
//         if(dividend < div){
//             if(j>0) table.push_back(0);
//             else j--;
//             continue;
//         }
//         // cout<<dividend/div<<" "<<dividend%div<<endl;
//         table.push_back(dividend / div);
//         dividend %= div;
//     }
//     // for(int i = 0; i < n; i++){
//     //     cout<<table[i];
//     // }
//     // cout<<endl;
//     // cout<<j<<endl;
//     int q = 0;
//     string ans = "";
//     while(table[q] == 0)    q++;
//     for(int i = q; i < table.size(); i++){
//         // cout<<table[i];
//         ans += to_string(table[i]);
//     }  
//     // cout<<endl<<ans<<endl;
//     return ans;
// }

// bool cmp(string a, string b){
//     int n = a.size(), m = b.size();
//     if(n < m)   return true;
//     else if(n > m)  return false;
//     else return a < b;
// }

// void square(string a, string b, string target){
//     // if(b.length()>26)   return;
//     string mid = div(add(a, b), "2"), q = mul(mid, mid);
//     // string x = mul(a, a), y = mul(b, b);
//     // cout<<a<<" "<<b<<" "<<mid<<" "<<q<<endl;
//     // if(cmp(b, q))
//     // if(x == target)  cout<<a<<endl<<endl;
//     // else if(y == target)   cout<<b<<endl<<endl;
//     if(q == target)  cout<<mid<<endl;
//     else if(cmp(q, target)) square(mid, b, target);
//     else   square(a, mid, target);
// }

bool cmp2(string a, string b){
    int n = a.size(), m = b.size();
    if(a == b)  return true;
    if(n < m)   return true;
    else if(n > m)  return false;
    else return a < b;
}

void sqrt(string a){
    string re = "0", left;
    int n = a.size(), i, j;
    if(n % 2 == 0){
        left = a.substr(0, 2);
        i = 2;
    }
    else{
        left = a.substr(0, 1);
        i = 1;
    }
    while(i <= n){
        string tmp = mul(re, "20") , tmp2 = "";
        // cout<<tmp<<endl;
        int m = tmp.size();
        for(j = 9; j >= 0; j--){
            tmp[m-1] = j + '0';
            // cout<<tmp<<endl;
            tmp2 = mul(tmp, to_string(j));
            // tmp = mul(tmp, to_string(j));
            if(cmp2(tmp2, left)){
                break;
            }
        }
        // cout<<"tmp "<<tmp<<": "<<tmp2<<endl;
        if(re != "0")   re += to_string(j);
        else    re = to_string(j);
        left = sub(left, tmp2);
        // cout<<"left: "<<left<<endl;
        left = i < n ? add(a.substr(i, 2), mul(left,"100")) : left;
        if(left == "")  left = "0";
        // cout<<"left: "<<left<<endl;
        i += 2;
    }
    cout<<re<<endl;
}

int main() {
    int num;
    // cout<<div(add("12","9"),"2")<<endl;
    cin >> num;
    while (num--) {
        string target;
        cin >> target;
        // cout<<target<<endl;
        sqrt(target);
        // square("1", target, target);
        if(num) cout<<endl;
    }
}