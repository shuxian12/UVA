#include<iostream>

// https://blog.csdn.net/weixin_30457551/article/details/96042210
// https://blog.csdn.net/csg999/article/details/123392423
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3196

using namespace std;

const int MOD = 1000000007;

struct Matrix{
    long long m[2][2];
};

Matrix mul(Matrix a, Matrix b){
    Matrix ans;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            ans.m[i][j] = 0;
            for(int k = 0; k < 2; k++)
                ans.m[i][j] += a.m[i][k] * b.m[k][j];
            ans.m[i][j] %= MOD;     //要記得MOD
        }
    }
    return ans;
}

Matrix pow(int n){
    Matrix ans, a;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            ans.m[i][j] = (i == j); //[1, 0] [0, 1]
            a.m[i][j] = 1;  //[0, 1] [1, 1]
        }
    }
    a.m[0][0] = 0;
    while(n){
        if(n & 1)   ans = mul(ans, a);
        n >>= 1;
        a = mul(a, a);
        // cout<<a.m[0][0]<<" "<<a.m[0][1]<<" "<<a.m[1][0]<<" "<<a.m[1][1]<<endl;
    }
    return ans;
}

long long x, y, X, Y;

bool solve(int n, int m){
    Matrix m1, m2;
    // cout<<"n = "<<n<<", m = "<<m<<endl;
    long long a1, a2, b1, b2;
    if(n != 1){
        m1 = pow(n - 1);
        a1 = m1.m[0][0] + m1.m[1][0];
        a2 = m1.m[0][1] + m1.m[1][1];
    }
    else    a1 = a2 = 1;

    if(m != 1){
        m2 = pow(m - 1);
        b1 = m2.m[0][0] + m2.m[1][0];
        b2 = m2.m[0][1] + m2.m[1][1];
    }
    else    b1 = b2 = 1;
    cout << a1 << " " << a2 << " " << b1 << " " << b2 << endl;
    long long h1 = x * b1 - y * a1;
    long long h2 = a2 * y - x * b2;
    long long h3 = b1 * a2 - b2 * a1;
    if(h2 % h3 != 0 || h1 % h3 != 0)    return false;
    Y = h1 / h3;
    X = h2 / h3;
    if(X < 0 || Y < 0)  return false;
    return true;
}

int main(){
    int N, M, K, T;
    // Matrix b = pow(3);
    // cout<<b.m[0][0]<<" "<<b.m[0][1]<<" "<<b.m[1][0]<<" "<<b.m[1][1]<<endl;
    cin >> T;
    while(T--){
        cin >> N >> x >> M >> y >> K;
        if(!solve(N, M)){
            cout << "Impossible\n";
            continue;
        }
        else{
            cout << X << " " << Y << endl;
            if(K == 1){
                cout << (X + Y) % MOD << endl;
                continue;
            }
            Matrix a = pow(K - 1);
            long long ans = ((a.m[0][0] + a.m[1][0]) * X + (a.m[0][1] + a.m[1][1]) * Y) % MOD;
            cout << ans << endl;
        }
    }
}