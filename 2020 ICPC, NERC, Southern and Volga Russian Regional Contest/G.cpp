#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 8e18;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
//const int Base = 311;9
const long double EPS = 1e-10;
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

const int maxN = 3e5 + 100;

struct point {
    int x, y;
    point(int _x = 0, int _y = 0) {
        x = _x;
        y = _y;
    }
};

void sub(point &A, point B) {
    A.x -= B.x;
    A.y -= B.y;
}

long double Dist(point A, point B) {
    long double x = A.x - B.x;
    long double y = A.y - B.y;
    return sqrtl(x * x + y * y);
}
bool NguocChieu(point O, point A, point B) {
    sub(A, O);
    sub(B, O);
    return 1LL * A.x * B.y > 1LL * A.y * B.x;
}

bool Line(point O, point A, point B) {
    sub(A, O);
    sub(B, O);
    return 1LL * A.x * B.y == 1LL * A.y * B.x;
}

bool CungChieu(point O, point A, point B) {
    sub(A, O);
    sub(B, O);
    return 1LL * A.x * B.y < 1LL * A.y * B.x;
}

long double S(point A, point B, point C) {
    vector<point> a = {A, B, C};
    a.push_back(A);
    long double S = 0;
    for (int i = 0; i < 3; i++) S += 1LL * (a[i + 1].x - a[i].x) * (a[i + 1].y + a[i].y);
    return abs(S) / 2;
}
void sol(){
    int n, H;
    cin >> n >> H;
    vector<point> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
    vector<point> v;
    v.push_back(point(a[n - 1].x, a[n - 1].y + H));
    v.push_back(point(a[n - 1].x, a[n - 1].y));
    int sz = 2;
    long double ans = 0;
    for (int i = n - 2; i >= 0; i--) {
        if (CungChieu(v[0], v[sz - 1], a[i])) {
            long double S2 = S(v[0], v[sz - 1], a[i + 1]);
            long double S1 = S(v[0], v[sz - 1], a[i]);
            long double L = Dist(a[i], a[i + 1]);
            ans += Dist(a[i], a[i + 1]) * S1 / (S1 + S2);
            v.push_back(a[i]);
            sz++;
            // cout << i << " " << fixed << setprecision(10) << S1 << " " << S2 << " " << L << " " << ans << '\n';
        }
        if (Line(v[0], v[sz - 1], a[i])){
            if (v[sz - 1].x == a[i + 1].x) ans += Dist(v[sz - 1], a[i]);
            //cout << i << " " << fixed << setprecision(10) << Dist(v[sz - 1], a[i]) << " " << ans << '\n';
            v.push_back(a[i]);
            sz++;
        }
    }
    cout << fixed << setprecision(10) << ans;
}

void solve() {
    clock_t begin = clock();
    int T;
    //cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        //cout << "Test " << TestCase << ": ";
        sol();
    }
    clock_t end = clock();
    cerr << "Time: " << fixed << setprecision(10) << (double)(end - begin) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
