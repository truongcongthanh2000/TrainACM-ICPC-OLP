#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e5 + 1000;

struct Point {
    long double x, y, z;
    Point(){};
    Point(long double _x, long double _y, long double _z) {
        x = _x;
        y = _y;
        z = _z;
    }
    void normal() {
        long double len = sqrtl(x * x + y * y + z * z);
        x /= len;
        y /= len;
        z /= len;
    }
};

void print(Point A) {
    cout << fixed << setprecision(10);
    cout << A.x << " " << A.y << " " << A.z << '\n';
}
long double dot(Point A, Point B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

#define EPS 1e-12
typedef long double T;
typedef vector<T> ROW;
typedef vector<ROW> MATRIX;

inline int sign(T x) {return x < -EPS ? -1 : x > +EPS;}
MATRIX MatrixInverse(MATRIX a) {
    int i, j, k, n = a.size();
    MATRIX res;
    res.resize(n);
    for (i = 0; i < n; i++) {
        res[i].resize(n);
        for (j = 0; j < n; j++) res[i][j] = 0;
        res[i][i] = 1;
    }
    for (i = 0; i < n; i++) {
        if (!sign(a[i][i])) {
            for (j = i + 1; j < n; j++) {
                if (sign(a[j][i])) {
                    for (k = 0; k < n; k++) {
                        a[i][k] += a[j][k];
                        res[i][k] += res[j][k];
                    }
                    break;
                }
            }
            if (j == n) {
                assert(false);
                res.clear();
                return res;
            }
        }
        T tmp = a[i][i];
        for (k = 0; k < n; k++) {
            a[i][k] /= tmp;
            res[i][k] /= tmp;
        }
        for (j = 0; j < n; j++) {
            if (j == i) continue;
            tmp = a[j][i];
            for (k = 0; k < n; k++) {
                a[j][k] -= a[i][k] * tmp;
                res[j][k] -= res[i][k] * tmp;
            }
        }
    }
    return res;
}

MATRIX nhan(MATRIX a, MATRIX b) {
    //cerr << (int)a.size() << " " << (int)a[0].size() << " " << (int)b.size() << " " << (int)b[0].size() << '\n';
    int n = (int)a.size();
    int m = (int)a[0].size();
    //assert((int)b.size() == m);
    int K = (int)b[0].size();
    MATRIX res;
    res.resize(n);
    for (int i = 0; i < n; i++) {
        res[i].resize(K);
        for (int j = 0; j < K; j++) res[i][j] = 0;
    }
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < K; j++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

MATRIX init(vector<long double> value) {
    MATRIX res;
    res.resize(3);
    for (int i = 0; i < 3; i++) {
        res[i].resize(3);
        for (int j = 0; j < 3; j++) res[i][j] = value[i * 3 + j];
    }
    return res;
}

Point kPoint(long double K, Point A) {
    Point res(K * A.x, K * A.y, K * A.z);
    return res;
}

bool Equal(Point A, Point B) {
    bool ok = abs(A.x - B.x) < EPS;
    ok &= abs(A.y - B.y) < EPS;
    ok &= abs(A.z - B.z) < EPS;
    return ok;
}
void sol(){
    Point A, B, C;
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
    if (A.x * A.x + A.y * A.y >= 1.0 - EPS) A.z = 0;
    else A.z = sqrt(1.0 - A.x * A.x - A.y * A.y);
    if (B.x * B.x + B.y * B.y >= 1.0 - EPS) B.z = 0;
    else B.z = sqrt(1.0 - B.x * B.x - B.y * B.y);
    if (C.x * C.x + C.y * C.y >= 1.0 - EPS) C.z = 0;
    else C.z = sqrt(1.0 - C.x * C.x - C.y * C.y);
    int sa, sb, sc;
    cin >> sa >> sb >> sc;
    if (sa == 0) A.z *= -1;
    if (sb == 0) B.z *= -1;
    if (sc == 0) C.z *= -1;
    long double l = dot(B, C) / dot(B, B);
    //cout << fixed << setprecision(10) << l << '\n';
    Point v(B.y * C.z - B.z * C.y, B.z * C.x - B.x * C.z, B.x * C.y - B.y * C.x);
    v.normal();
    //print(v);
    if (Equal(B, Point(-C.x, -C.y, -C.z))) {
        long double ab = dot(A, B) / dot(B, B);
        //cerr << dot(A, B) << '\n';
        //cerr << ab << '\n';
        v = Point(A.x - ab * B.x, A.y - ab * B.y, A.z - ab * B.z);
        v.normal();
        long double k = dot(v, A) / dot(v, v);
        //cerr << k << '\n';
        Point OH = kPoint(k, v);
        Point res(OH.x * 2 - A.x, OH.y * 2 - A.y, OH.z * 2 - A.z);
        print(res);
        return;
    }
    if (Equal(B, C)) {
        print(A);
        return;
    }
   long double theta = acos(dot(B, C) / sqrtl(dot(B, B) * dot(C, C)));
   vector<long double> value(9);
   value[0] = cos(theta) + v.x * v.x * (1.0 - cos(theta));
   value[1] = v.x * v.y * (1.0 - cos(theta)) - v.z * sin(theta);
   value[2] = v.x * v.z * (1.0 - cos(theta)) + v.y * sin(theta);
   value[3] = v.y * v.x * (1.0 - cos(theta)) + v.z * sin(theta);
   value[4] = cos(theta) + v.y * v.y * (1.0 - cos(theta));
   value[5] = v.y * v.z * (1.0 - cos(theta)) - v.x * sin(theta);
   value[6] = v.z * v.x * (1.0 - cos(theta)) - v.y * sin(theta);
   value[7] = v.z * v.y * (1.0 - cos(theta)) + v.x * sin(theta);
   value[8] = cos(theta) + v.z * v.z * (1.0 - cos(theta));
    MATRIX res = init(value);
    MATRIX tmp;
    tmp.resize(3);
   // cerr << (int)tmp.size() << '\n';
    for (int i = 0; i < 3; i++) tmp[i].resize(1);
    tmp[0] = {A.x};
    tmp[1] = {A.y};
    tmp[2] = {A.z};
    res = nhan(res, tmp);
    cout << fixed << setprecision(10);
    cout << res[0][0] << " " << res[1][0] << " " << res[2][0] << '\n';
}

void solve() {
    int T;
    cin >> T;
    //T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}
int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
