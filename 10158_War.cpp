#include<iostream>
#include<vector>

using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1099
// https://blog.csdn.net/mobius_strip/article/details/12623357

vector<int> parent, ranks;

int find_set(int x){
    if(x != parent[x])
        parent[x] = find_set(parent[x]);
    return parent[x];
}

// void unoin(int x, int y){
//     if (x == y)
//         return;
    
//     if(ranks[x] > ranks[y])
//         parent[y] = x;
//     else{
//         if(ranks[x] == ranks[y])
//             ranks[y]++;
//         parent[x] = y;
//     }
// }

int main(){
    int num, c = 1, x = 1, y = 1;
    while(cin >> num){
        parent.resize(num * 2);
        for(int i = 0; i < num * 2; i++)
            parent[i] = i;
        ranks.clear();
        ranks.resize(num * 2, 1);

        while(cin >> c >> x >> y){
            if(c == 0 && x == 0 && y == 0)
                break;
            // cout<<c<<x<<y<<endl;
            int x_root = find_set(x), y_root = find_set(y);
            int x_enemy = find_set(x + num), y_enemy = find_set(y + num);
            switch(c){
            case 1:    //set_friend
                if(x_root == y_enemy) cout << -1 << endl;
                else{
                    // unoin(x_root, y_root), unoin(x_enemy, y_enemy);
                    parent[x_root] = y_root;
                    parent[x_enemy] = y_enemy;
                }
                break;
            case 2:    //set_enemy
                if(x_root == y_root) cout << -1 << endl;
                else{
                    parent[x_root] = y_enemy;
                    parent[x_enemy] = y_root;
                    // unoin(x_root, y_enemy), unoin(x_enemy, y_root);
                }
                break;
            case 3:    //is_friend
                if(x_root == y_root) cout << 1 << endl;
                else cout << 0 << endl;
                break;
            case 4:    //is_enemy
                if(x_enemy == y_root) cout << 1 << endl;
                else cout << 0 << endl;
                break;
            }
        }
    }
}