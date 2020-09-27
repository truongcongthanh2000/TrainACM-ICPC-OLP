#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "OB"
#define OUT "OB"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-7;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

struct Circle {
    long double x, y, r;
    Circle(long double _x = 0, long double _y = 0, long double _r = 0) : x(_x), y(_y), r(_r) {}
};

Circle a[maxN];
long double L[maxN], R[maxN];
int cost[62831853 + 10];

void sol() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y >> a[i].r;
    long double b, d;
    cin >> b >> d;
    Circle A(0, 0, b);
    for (int i = 1; i <= n; i++) {
        long double dist = sqrtl(a[i].x * a[i].x + a[i].y * a[i].y);
        long double kc = sqrtl(d * d + (b + a[i].r) * (b + a[i].r));
        if (dist <= kc) {
            long double alpha = asin((b + a[i].r) / dist);
            long double nxt = atan2(a[i].y, a[i].x);
            if (nxt < 0) nxt = M_PI * 2 + nxt;
            L[i] = alpha + nxt;
            R[i] = M_PI * 2.0 - alpha + nxt;
            while (L[i] >= M_PI * 2.0) L[i] -= M_PI * 2.0;
            while (L[i] < 0) L[i] += M_PI * 2.0;
            while (R[i] >= M_PI * 2.0) R[i] -= M_PI * 2.0;
            while (R[i] < 0) R[i] += M_PI * 2.0;
        }
        else {
            long double A = b + a[i].r;
            long double B = d;
            long double C = dist;
            long double value = (B * B + C * C - A * A) / (B * C * 2.0);
            if (abs(value) < 1.0) {
                long double alpha = acos(value);
                long double nxt = atan2(a[i].y, a[i].x);
                if (nxt < 0) nxt = M_PI * 2 + nxt;
                L[i] = alpha + nxt;
                R[i] = M_PI * 2.0 - alpha + nxt;
                while (L[i] >= M_PI * 2.0) L[i] -= M_PI * 2.0;
                while (L[i] < 0) L[i] += M_PI * 2.0;
                while (R[i] >= M_PI * 2.0) R[i] -= M_PI * 2.0;
                while (R[i] < 0) R[i] += M_PI * 2.0;
            }
            else {
                L[i] = 0.0;
                R[i] = M_PI * 2.0 - EPS;
            }
        }
    }
    int sz = 62831853;
    for (int i = 1; i <= n; i++) {
        long long a = L[i] * 10000000.0;
        long long b = R[i] * 10000000.0;
        //cout << L[i] << " " << R[i] << '\n';
        //cout << a << " " << b << '\n';
        if (a <= b) {
            cost[a] += 1;
            cost[b + 1] -= 1;
        }
        else {
            cost[a] += 1;
            cost[0] += 1;
            cost[b + 1] -= 1;
        }
    }
    for (int i = 1; i < sz; i++) cost[i] += cost[i - 1];
    int res = 0;
    for (int i = 0; i < sz; i++) {
        if (cost[i] == n) res++;
    }
    //cout << res << '\n';
    cout << fixed << setprecision(10);
    cout << (long double)res / (M_PI * 2.0 * 10000000.0);
}

void solve() {
    int T;
    ///cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
