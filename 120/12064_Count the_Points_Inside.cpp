#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
// #include<bits/stdc++.h>
# define eps 1e-6
#define eps2 1e-3
using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3216
// https://github.com/morris821028/UVa/blob/master/volume120/12064%20-%20Count%20the%20Points%20Inside.cpp

struct p{
    double x;
    double y;
};
double dis(p& a, p& b){
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

p cal_center(p& a, p& b, p& c){    // 圓心，用兩線的垂線求答案
    p ab, ac, o;
    double a1, b1, c1, a2, b2, c2, d1, d2, d;
    ab.x = (a.x + b.x) / 2, ab.y = (a.y + b.y) / 2;
    ac.x = (a.x + c.x) / 2, ac.y = (a.y + c.y) / 2;
    a1 = a.x - b.x, b1 = a.y - b.y, c1 = a1 * ab.x + b1 * ab.y;     //所以這裡的a1, b1, c1, a2, b2, c2和之前的不太一樣
    a2 = a.x - c.x, b2 = a.y - c.y, c2 = a2 * ac.x + b2 * ac.y;

    d1 = c1 * b2 - c2 * b1, d2 = a1 * c2 - a2 * c1, d = a1 * b2 - a2 * b1;
    o.x = d1 / d, o.y = d2 / d;
    return o;
    // static p ab, ac, o;
    // static double a1, b1, c1, a2, b2, c2, D, D1, D2;
}

p point[50005];
p A, B, C, mAB;

int main(){
    int n, q, task = 1;

    while(cin >> A.x >> A.y >> B.x >> B.y >> n >> q){
        if(n == 0 && q == 0)    break;
        for(int i = 0; i < n; i++){
            cin >> point[i].x >> point[i].y;
        }

        double a, b, c;     // ax + by = c
        a = A.y - B.y, b = B.x - A.x;   // a, b是直線的法向量
        if(a < 0)   a = -a, b = -b;
        c = a * A.x + b * A.y;
        mAB.x = (A.x + B.x) / 2, mAB.y = (A.y + B.y) / 2;
        double na = a, nb = b;      //單位法向量
        na /= sqrt(a * a + b * b);
        nb /= sqrt(a * a + b * b);
        if(na < 0)  na = -na, nb = -nb;

        int base = 0;
        vector<double> r_same, r_diff, l_same, l_diff;  // r: right, l: left
        for(int i = 0; i < n; i++){     // 先對每一點計算可能的圓心半徑
            double check = a * point[i].x + b * point[i].y - c;
            if(fabs((A.x - B.x) * (A.y - point[i].y) - (A.y - B.y) * (A.x - point[i].x)) < eps){    // 三點共線
                if(min(A.x, B.x) <= point[i].x && point[i].x <= max(A.x, B.x) && min(A.y, B.y) <= point[i].y && point[i].y <= max(A.y, B.y))
                    base++;
                continue;
            }

            if(check > 0){      // right
                // circle center in right side
                double l = 0, r = 150000, m, circle;
                p C;
                int count = 0;
                while(l <= r && count < 50){
                    m = (l + r) / 2;
                    C.x = mAB.x + m * na, C.y = mAB.y + m * nb;     // c是圓心
                    circle = dis(C, A);     //  circle = r^2

                    if(dis(C, point[i]) <= circle)  // 半徑太長
                        r = m;
                    else
                        l = m;
                    count++;
                }
                r_same.push_back(circle);

                l = 0, r = 150000, count = 0;      // circle center in left side
                while(l <= r && count < 50){
                    m = (l + r) / 2;
                    C.x = mAB.x - m * na, C.y = mAB.y - m * nb;     // 
                    circle = dis(C, A);     //

                    if(dis(C, point[i]) <= circle)  // 半徑太長
                        l = m;
                    else
                        r = m;
                    count++;
                }
                r_diff.push_back(circle);

            }
            else{       // left
                double l = 0, r = 150000, m, circle;
                p C;
                int count = 0;
                while(l <= r && count < 50){
                    m = (l + r) / 2;
                    C.x = mAB.x + m * na, C.y = mAB.y + m * nb;
                    circle = dis(C, A);

                    if(dis(C, point[i]) <= circle)
                        l = m;
                    else
                        r = m;
                    count++;
                }
                l_diff.push_back(circle);

                l = 0, r = 150000, count = 0;      // circle center in left side
                while(l <= r && count < 50){
                    m = (l + r) / 2;
                    C.x = mAB.x - m * na, C.y = mAB.y - m * nb;
                    circle = dis(C, A);

                    if(dis(C, point[i]) <= circle)
                        r = m;
                    else
                        l = m;
                    count++;
                }
                l_same.push_back(circle);
            }
        }

        sort(r_same.begin(), r_same.end());
        sort(r_diff.begin(), r_diff.end());
        sort(l_same.begin(), l_same.end());
        sort(l_diff.begin(), l_diff.end());

        cout << "Case " << task++ << ":\n";
        while(q--){
            int idx;
            cin >> idx;

            C = point[idx - 1];
            if(fabs((A.x - B.x) * (C.y - A.y) - (A.y - B.y) * (C.x - A.x)) < eps){    //在線上無法形成一個圓    //共線
                cout << "Impossible\n";
                continue;
            }

            C = cal_center(A, B, C);
            double check = a * C.x + b * C.y - c, circle = dis(C, A);
            if(circle > (100000 - eps) * (100000.0 - eps)){  //超出radius範圍
                cout << "Impossible\n";
                continue;
            }

            int v1, v2;
            if(check > 0){  //center in right hand side
                v1 = upper_bound(r_same.begin(), r_same.end(), circle + eps2) - r_same.begin();     // find the first circle that is larger than cr2
                v2 = upper_bound(l_diff.begin(), l_diff.end(), circle - eps2) - l_diff.begin();     // find the first circle that is in left side and bigger than cr2
                v2 = l_diff.size() - v2;        // v2 is the number of circle that is in left side and bigger than cr2
            }
            else{   // center in left hand side
                v1 = upper_bound(l_same.begin(), l_same.end(), circle + eps2) - l_same.begin();     // find the first circle that is larger than cr2
                v2 = upper_bound(r_diff.begin(), r_diff.end(), circle - eps2) - r_diff.begin();     // find the first circle that is in right side and bigger than cr2
                v2 = r_diff.size() - v2;        // v2 is the number of circle that is in right side and bigger than cr2
            }
            cout << v1 + v2 + 2 + base << "\n";   // +2 is the two point A and B, +base is the number of point that is on the line
        }
    }
}
