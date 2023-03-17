#include<iostream>
#include<sstream>
#include<cmath>
using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1077
// https://blog.csdn.net/XiaoSoulDeng/article/details/7993222?spm=1001.2101.3001.6650.4

struct p{
    double x;
    double y;
};

double dist(p a, p b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

p point[202], c[40100];

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
        if(count == 0){
            cout << 0 << endl;
            continue;
        }
        double dx, dy, dz;
        int k = 0;
        for(int i = 1; i < count; i++){     //先找所有可能的圓心，再遍歷所有圓心，查看巧克力數量最多的圓
            for(int j = 0; j < i; j++){
                double dis = dist(point[i], point[j]);
                if(dis <= 5){
                    dis = sqrt(6.25 - dis * dis / 4.0);     // 和圓心連接的三角形的高
                    dx = point[j].y - point[i].y;
                    dy = point[i].x - point[j].x;
                    dz = sqrt(dx * dx + dy * dy);
                    dx = dx / dz * dis;     // 求垂直標準法向量
                    dy = dy / dz * dis;

                    c[k].x = (point[i].x + point[j].x) / 2.0 + dx;  // 求圓心
                    c[k++].y = (point[i].y + point[j].y) / 2.0 + dy;
                    c[k].x = (point[i].x + point[j].x) / 2.0 - dx;
                    c[k++].y = (point[i].y + point[j].y) / 2.0 - dy;
                }
            }
        }
        int max = 1;
        for(int i = 0; i < k; i++){
            int temp = 0;
            for(int j = 0; j < count; j++){
                // cout<<c[i].x<<" "<<c[i].y<<" "<<point[j].x<<" "<<point[j].y<<endl;
                // double a = sqrt((c[i].x - point[j].x) * (c[i].x - point[j].x) + (c[i].y - point[j].y) * (c[i].y - point[j].y));
                // cout<<a<<endl;
                double a = dist(c[i], point[j]);
                if(a - 1e-6 <= 2.5){  //1e-6 ~ 1e-10
                    temp++;
                    // cout<<i<<" "<<j<<" "<<temp<<endl;
                }

            }
            if(temp > max) max = temp;
        }
        cout << max << endl;
        if(task)    cout << endl;
    }
}