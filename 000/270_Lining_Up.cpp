#include<iostream>
#include<sstream>
using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=206
// https://blog.csdn.net/mobius_strip/article/details/44159451
// 求有幾點共線

struct p{
    double x;
    double y;
};

p point[705];
double slope[705];

int main(){
    int task, count = 0;
    string line;
    cin >> task;
    cin.ignore();
    cin.ignore();
    while(task--){
        count = 0;
        while(getline(cin, line) && line != ""){
            istringstream iss(line);
            iss >> point[count].x >> point[count].y;
            count++;
        }
        int max = 0;
        for(int i = 0, k = 0; i < count; i++, k = 0){
            for(int j = 0; j < count; j++, k++){
                if(i == j){
                    k--;
                    continue;
                }
                if(point[i].x == point[j].x) slope[k] = 1e10;
                else
                    slope[k] = (point[j].y - point[i].y) / (point[j].x - point[i].x);
            }
            sort(slope, slope + k);
            int temp = 1;
            for(int j = 1; j < k; j++){
                if(slope[j] == slope[j - 1]) temp++;
                else{
                    if(temp > max) max = temp;
                    temp = 1;
                }
            }
            if(temp > max) max = temp;
        }
        cout << max + 1 << endl;
        if(task) cout << endl;
    }
}