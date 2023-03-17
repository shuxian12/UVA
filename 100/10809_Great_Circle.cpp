// # include <bits/stdc++.h>
#include <iostream>
#include <cmath>
using namespace std;
// #define M_PI 3.14159265358979323846
#define _USE_MATH_DEFINES
#define EPSILON 1e-10


double pos[4];
double& lat1 = pos[0], & lon1 = pos[1], & lat2 = pos[2], & lon2 = pos[3];
double alpha, delta;

typedef struct Vector {
    double x, y, z;
    Vector() {}
    Vector(double lat, double lon) { // lat 緯度, lon 經度
        double lambda, phi;
        phi = lat / 180 * M_PI;
        lambda = lon / 180 * M_PI;
        x = cos(phi) * cos(lambda);
        y = cos(phi) * sin(lambda);
        z = sin(phi);
    }
    Vector operator*(double scalar) {
        Vector ret = *this;
        ret.x *= scalar;
        ret.y *= scalar;
        ret.z *= scalar;
        return ret;
    }
    Vector operator+(Vector vec) {
        Vector ret = *this;
        ret.x += vec.x;
        ret.y += vec.y;
        ret.z += vec.z;
        return ret;
    }
    void Normalize() {
        double len = sqrt(x * x + y * y + z * z);
        x /= len;
        y /= len;
        z /= len;
    }
}Vector;

Vector city1, city2, norther, mid;

void calWeightedMid(double s) {     // 更新 norther 和 alpha
    if (s < 0 || s > 1) return;
    mid = city1 * s + city2 * (1 - s);
    mid.Normalize();
    if (mid.z > norther.z) {
        norther = mid;
        alpha = s;
    }
    return;
}

double calDegree(int d, int m, char dir) {
    double deg = m;
    deg /= 60.0;
    deg += d;
    if (dir == 'S' || dir == 'W') deg = -deg;
    return deg;
}

int main() {
    int N;
    cin >> N;
    while (N--) {
        int d, m;
        char dir;
        for (int i = 0; i < 4; i++) {
            cin >> d >> dir >> m >> dir;
            pos[i] = calDegree(d, m, dir);
        }

        // if city1 and city2 are antipodes, then print undefined
        if ((lat1 == -lat2) && (fabs(lon1 - lon2) == 180)) {
            cout << "undefined" << endl;
            continue;
        }

        city1 = Vector(lat1, lon1);
        city2 = Vector(lat2, lon2);

        if (city1.z > 1 - EPSILON || city2.z > 1 - EPSILON) {
            cout << "90,0N" << endl;
            continue;
        }
        if (city1.z < -1 + EPSILON || city2.z < -1 + EPSILON) {
            cout << "90,0S" << endl;
            continue;
        }

        norther.z = -2;
        calWeightedMid(0);  //前中後三點最北邊的點
        calWeightedMid(.5);
        calWeightedMid(1);
        for (double delta = .5; delta > EPSILON; delta /= 2) {
            calWeightedMid(alpha - delta);
            calWeightedMid(alpha + delta);
        }

        dir = (norther.z >= 0 ? 'N' : 'S');
        norther.z = fabs(norther.z);
        double ans = (int)floor(asin(norther.z) / M_PI * 180 * 60 + 0.5);   // 四捨五入
        cout << (int)ans / 60 << "," << (int)ans % 60 << dir << endl;
    }
    return 0;
}