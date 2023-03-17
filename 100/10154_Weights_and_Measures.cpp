#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

// https://nicknick0630.github.io/2019/03/07/UVa-10154-Weights-and-Measures/
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1095

using namespace std;

struct turtle{
    int weight, strength;
};

bool cmp(turtle a, turtle b){
    if(a.strength == b.strength)    return a.weight < b.weight;
    return a.strength < b.strength;
}

int main(){
    vector<turtle> v;
    turtle t;
    while(cin >> t.weight >> t.strength){
        v.push_back(t);
    }
    sort(v.begin(), v.end(), cmp);
    priority_queue<int> q;
    int sum = 0;
    for(int i = 0; i < v.size(); i++){
        sum += v[i].weight;
        q.push(v[i].weight);
        if(sum > v[i].strength){
            sum -= q.top();
            q.pop();
        }
    }
    cout << q.size() << endl;
}