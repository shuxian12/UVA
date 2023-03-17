#include <iostream>
#include <string>
#include <cstring>
using namespace std;

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1620

int main()
{
    int k, n;
    string s, t;

    cin >> k;
    while (k--) {
        cin >> s >> n;
        while (n--) {
            cin >> t;
            cout<<(strstr(s.c_str(), t.c_str()) ? "y\n" : "n\n");
        }
    }

    return 0;
}

// KMP
//
// int prefix_table[1000005];
//
// void failure_function(string pattern){
//   int j = 0, k = -1;
//   prefix_table[0] = -1;
//   while(j < pattern.size()){
//       if(k == -1 || pattern[j] == pattern[k]){
//           j++, k++;
//           prefix_table[j] = k;
//       }
//       else
//         k = prefix_table[k];
//   }
// }
// bool kmp(string st, string pattern){
//   failure_function(pattern);
//   int i = 0, j = 0, n = st.size(), m = pattern.size();
//   while (1){
//     if (i == n)
//       return false;
//     if (st[i] == pattern[j])
//       i++, j++;
//     else if (j != 0)
//       j = prefix_table[j];
//     else
//       i++;
//     if (j == m)
//       return true;
//   }
// }
//
// int main(){
//    int t, idd = 0, line = 0, i, cnt = 0, n, m, j, k, x;
//    string st, pattern;
//    cin >> t;
//    while (t--)
//    {
//      cin >> st;
//      cin >> n;
//      while (n--)
//      {
//        cin >> pattern;
//        if (kmp(st, pattern))
//          printf("y\n");
//        else
//          printf("n\n");
//      }
//    }
//    return 0;
// }



