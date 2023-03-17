#include<iostream>
#include<vector>

using namespace std;
// https://gist.github.com/quickgrid/640bca78dccc392a5586af9e3fdc56b7
// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=400

vector<vector<char> > v;
vector<int> V_rank;
vector<int> p;

int disjointSetCount;
// void makeset(int x){
//     disjointSetCount = x;
// }

int findset(int x){
    if(x != p[x])
        p[x] = findset(p[x]);
    return p[x];
}

bool sameset(int x, int y){
    return findset(x) == findset(y);
}

void link(int x, int y){
    if(x != y){
        if(V_rank[x] > V_rank[y])
            p[y] = p[x];
        else{
            p[x] = p[y];
            if(V_rank[x] == V_rank[y])
                V_rank[y]++;
        }
        disjointSetCount--;
    }
}

void Union(int x, int y){
    return link(findset(x), findset(y));
}

// void visit(vector<vector<char> > &v, vector<bool> &visited, int i){
//     if(visited[i]) return;
//     visited[i] = true;
//     for(int j = 0; j < v[i].size(); j++){
//         if(!visited[v[i][j] - 'A'])
//             visit(v, visited, v[i][j] - 'A');
//     }
// }

int main(){
    string c;
    int num;
    cin >> num;
    for(int i = 0; i < num; i++){
        if(i > 0)    cout << endl;
        cin >> c;
        int n = c[0] - 'A' + 1;
        V_rank.clear(), p.clear();
        V_rank.resize(n, 0);
        p.resize(n);
        disjointSetCount = n;
        for(int j = 0; j < n; j++){
            p[j] = j;
        }
        string t;
        getline(cin, t);
        while(getline(cin, t)){
            if(t == "") break;
            Union(t[0] - 'A', t[1] - 'A');
        }
        cout << disjointSetCount << endl;
    }
}

// int main(){
//     string c;
//     int num;
//     cin>>num;
//     for(int i = 0; i < num; i++){
//         if(i > 0)   // 這邊要注意，不然會多一個空行
//             cout<<endl;

//         cin>>c;
//         int n = c[0] - 'A' + 1;
//         vector<vector<char> > v(n);
//         vector<bool> visited(n, false);
//         vector<int> p(n, -1);
//         string t;
//         getline(cin, t);
//         while(getline(cin, t)){
//             if(t == "")
//                 break;
//             v[t[0] - 'A'].push_back(t[1]);
//             v[t[1] - 'A'].push_back(t[0]);
//         }
//         int count = 0;
//         for(int i = 0; i < n; i++){
//             if(!visited[i]){
//                 // cout<<char(i + 'A')<<" visited, count++\n";
//                 count++;
//                 visited[i] = true;
//                 for(int j = 0; j < v[i].size(); j++){
//                     visit(v, visited, v[i][j] - 'A');
//                     // cout<<v[i][j]<<" visited\n";
//                 }
//             }
//         }
//         cout<<count<<endl;
//     }
// }