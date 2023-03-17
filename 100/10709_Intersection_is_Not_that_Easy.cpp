#include<iostream>
#include<cmath>
#define eps 1e-6
using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1650
// http://morris821028.github.io/2014/06/08/oj/uva/uva-10709/

struct pt{
    int x, y;
    pt(int a = 0, int b = 0){
        x = a;
        y = b;
    }
    bool operator<(const pt& a) const{
        if(fabs(x - a.x) > eps)   // 使用很小值當作0的判斷
            return x < a.x;
        return y < a.y;
    }
    pt operator-(const pt& a) const{
        pt ret;
        ret.x = x - a.x;
        ret.y = y - a.y;
        return ret;
    }
};

enum line_type{ LINE, SEGMENT };
struct Line{
    pt s, e;
    line_type type;
    Line(){}
};

double dist(pt p1, pt p2){
    return hypot(p1.x - p2.x, p1.y - p2.y); //return sqrt(x^2, y^2)
}
double dot(pt v1, pt v2){   //內積
    return v1.x * v2.x + v1.y * v2.y;
}
double cross2(pt v1, pt v2){ //外積
    return v1.x * v2.y - v1.y * v2.x;
}
double cross(pt p1, pt p2, pt p3){   //外積
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}
int between(pt a, pt b, pt c){    //判斷 p3 是否在 p1 p2 之間
    return dot(c - a, b - a) >= 0 && dot(c - b, a - b) >= 0;    // 內積大於等於0，角度小於等於90度，內角小於等於180度，可以想成三角形
}
int intersection(pt as, pt ae, pt bs, pt be){   //判斷兩線段是否相交
    if(cross(as, ae, bs) * cross(as, ae, be) < 0 &&
        cross(ae, as, bs) * cross(ae, as, be) < 0 &&
        cross(bs, be, as) * cross(bs, be, ae) < 0 &&
        cross(be, bs, as) * cross(be, bs, ae) < 0)
        return 1;
    return 0;
}
double distProjection(pt as, pt ae, pt p){
    int a = ae.y - as.y, b = as.x - ae.x, c = -(as.x * a + as.y * b);   // ax + by + c = 0
    // cout<<a<<" "<<b<<" "<<c<<endl;
    return fabs(a * p.x + b * p.y + c) / hypot(a, b);   // |ax + by + c| / sqrt(a^2 + b^2)
}
/*
線段與線段
    - 相交，最鄰近距離 0。
    - 不相交，查閱是否能作投影，否則直接查閱到端點的距離。
線與線
    - 不平行，最鄰近距離 0。
    - 平行，直接調用公式計算兩線距離。 // 當然可以調用投影距離。
線與線段
    - 線段跨過線的兩側，最鄰近距離 0
    - 同側，直接做投影。
*/
double closet(Line l1, Line l2){
    if(l1.type == SEGMENT && l2.type == SEGMENT){
        if(intersection(l1.s, l1.e, l2.s, l2.e))
            return 0;

        double c = 1e30;
        if(between(l1.s, l1.e, l2.s))   // l2.s 在 l1 上，查看是否可投影
            c = min(c, distProjection(l1.s, l1.e, l2.s));
        else    // 直接計算距離，點不在線段上無法投影
            c = min(c, min(dist(l1.s, l2.s), dist(l1.e, l2.s)));

        if(between(l1.s, l1.e, l2.e))   // l2.e 在 l1 上，查看是否可投影
            c = min(c, distProjection(l1.s, l1.e, l2.e));
        else    // 直接計算距離
            c = min(c, min(dist(l1.s, l2.e), dist(l1.e, l2.e)));

        if(between(l2.s, l2.e, l1.s))   // l1.s 在 l2 上，查看是否可投影
            c = min(c, distProjection(l2.s, l2.e, l1.s));
        else    // 直接計算距離
            c = min(c, min(dist(l2.s, l1.s), dist(l2.e, l1.s)));    //這裡要確認看看

        if(between(l2.s, l2.e, l1.e))   // l1.e 在 l2 上，查看是否可投影
            c = min(c, distProjection(l2.s, l2.e, l1.e));
        else    // 直接計算距離
            c = min(c, min(dist(l2.s, l1.e), dist(l2.e, l1.e)));

        return c;
    }
    if(l1.type == LINE && l2.type == LINE){
        int a1, a2, b1, b2;
        a1 = l1.s.y - l1.e.y, a2 = l1.e.x - l1.s.x;
        b1 = l2.s.y - l2.e.y, b2 = l2.e.x - l2.s.x;
        // cout<<a1<<" "<<a2<<" "<<b1<<" "<<b2<<endl;
        // cout<<a1 * b2<<" "<<a2 * b1<<endl;
        if(a1 * b2 == a2 * b1)  // 平行 a1/a2 = b1/b2 -> a1*b2 = a2*b1
            return distProjection(l1.s, l1.e, l2.s);
        return 0;
    }
    if(l1.type != l2.type){
        if(l1.type == SEGMENT)     // 確保 l1 為線, l2 為線段
            swap(l1, l2);
        int a, b, c;
        a = l1.s.y - l1.e.y, b = l1.e.x - l1.s.x, c = -(l1.s.x * a + l1.s.y * b);
        int v1, v2;
        v1 = a * l2.s.x + b * l2.s.y + c;
        v2 = a * l2.e.x + b * l2.e.y + c;
        if(v1 * v2 < 0)     // 線段跨過線的兩側
            return 0;
        return min(distProjection(l1.s, l1.e, l2.s), distProjection(l1.s, l1.e, l2.e));   // 同側，直接做投影
    }
    return -1;
}
int main(){
    int x1, y1, x2, y2;
    Line l1, l2;
    string type;
    while(cin >> x1 >> y1 >> x2 >> y2 >> type && type != "END"){
        l1.s = pt(x1, y1), l1.e = pt(x2, y2);
        if(type == "LS")
            l1.type = SEGMENT;
        else
            l1.type = LINE;

        cin >> x1 >> y1 >> x2 >> y2 >> type;
        l2.s = pt(x1, y1), l2.e = pt(x2, y2);
        if(type == "LS")
            l2.type = SEGMENT;
        else
            l2.type = LINE;

        printf("%.5lf\n", closet(l1, l2));
    }
}