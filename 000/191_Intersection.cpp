#include<iostream>
#include<cmath>

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=127
// https://blog.csdn.net/FXXKI/article/details/43233949?spm=1001.2101.3001.6650.4
// https://blog.csdn.net/clover_hxy/article/details/53966405?spm=1001.2101.3001.6650.3

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

using namespace std;

struct point{
    double x, y;
    point(double x, double y){
        this->x = x;
        this->y = y;
    }
    point(){}
};

struct line{
    double x, y, dx, dy;
    line(point a, point b){     // a 起點 b 終點
        x = a.x, y = a.y;
        dx = b.x - a.x, dy = b.y - a.y;     //向量 a -> b = (b.x - a.x, b.y - a.y)
    }
    line(){}
};

bool in(point p, point a, point b){ // a 左上 b 右下
    return (p.x >= a.x && p.x <= b.x && p.y >= b.y && p.y <= a.y);
}

bool across(line a, line b){    //dx = x1 - x0, dy = y1 - y0
    double t1 = a.dx * (b.y - a.y) - a.dy * (b.x - a.x);    // 法向量公式 (x1-x0, y1-y0) x (x2-x0, y2-y0) = (x1-x0)(y2-y0) - (x2-x0)(y1-y0)
    double t2 = a.dx * (b.y + b.dy - a.y) - a.dy * (b.x + b.dx - a.x);
    double t3 = b.dx * (a.y - b.y) - b.dy * (a.x - b.x);
    double t4 = b.dx * (a.y + a.dy - b.y) - b.dy * (a.x + a.dx - b.x);

    if(t1 * t2 == 0 || t3 * t4 == 0){   // 兩線平行
        point a1 = point(a.x, a.y), a2 = point(a.x + a.dx, a.y + a.dy);
        point b1 = point(b.x, b.y), b2 = point(b.x + b.dx, b.y + b.dy);
        point a_left_top = point(min(a1.x, a2.x), max(a1.y, a2.y));
        point a_right_bottom = point(max(a1.x, a2.x), min(a1.y, a2.y));
        if(in(a1, b1, b2) || in(a2, b1, b2) || in(b1, a_left_top, a_right_bottom) || in(b2, a_left_top, a_right_bottom))
            return true;
        else{
            return false;
        }
    }
    return (t1 * t2 < 0 && t3 * t4 < 0);    // 兩線交叉 ，不相交就會是正的
}

int main(){
    int n;
    double point_s_x, point_s_y, point_e_x, point_e_y;
    point line_s, line_e;
    cin >> n;
    while(n--){
        cin >> line_s.x >> line_s.y >> line_e.x >> line_e.y;
        cin >> point_s_x >> point_s_y >> point_e_x >> point_e_y;
        point p_left_top = point(min(point_s_x, point_e_x), max(point_s_y, point_e_y));  //做長方形左上右下的點
        point p_right_bottom = point(max(point_s_x, point_e_x), min(point_s_y, point_e_y)); //做長方形左上右下的點

        line l = line(line_s, line_e);
        line p1 = line(p_left_top, point(p_left_top.x, p_right_bottom.y));  //做長方形四個邊的線
        line p2 = line(point(p_left_top.x, p_right_bottom.y), p_right_bottom);
        line p3 = line(p_right_bottom, point(p_right_bottom.x, p_left_top.y));
        line p4 = line(point(p_right_bottom.x, p_left_top.y), p_left_top);

        if(in(line_s, p_left_top, p_right_bottom) || in(line_e, p_left_top, p_right_bottom))    //判斷線段是否在長方形內
            cout << "T" << endl;
        else if(across(l, p1) || across(l, p2) || across(l, p3) || across(l, p4))   //判斷線段是否與長方形邊相交
            cout << "T" << endl;
        else
            cout << "F" << endl;
    }
}

