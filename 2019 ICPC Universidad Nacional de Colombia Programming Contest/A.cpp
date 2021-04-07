#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

int gcd(int x, int y) {
    return y == 0 ? abs(x) : gcd(y, x % y);
}

int lcm(int x, int y) {
    return x / gcd(x, y) * y;
}
struct Point {
    int x, y;
    Point(){};
    void normal() {
        int z = gcd(x, y);
        x /= z;
        y /= z;
        if (y < 0) {
            x *= -1;
            y *= -1;
        }
        if (y == 0) x = 1;
    }
    Point(int _x, int _y) : x(_x), y(_y) {
        normal();
    }
    bool operator == (const Point &A) const {
        return make_pair(x, y) == make_pair(A.x, A.y);
    }
    bool operator < (const Point &A) const {
        return make_pair(x, y) < make_pair(A.x, A.y);
    }
};

void sol() {
    int n;
    cin >> n;
    vector<pair<Point, int> > a;
    for (int i = 1; i <= n; i++) {
        int xL, yL, xR, yR;
        cin >> xL >> yL >> xR >> yR;
        int x = xL - xR;
        int y = yL - yR;
        Point t(x, y);
        a.push_back({t, t.x * yL - t.y * xL});
    }
    sort(a.begin(), a.end());
    a.resize(unique(a.begin(), a.end()) - a.begin());
    map<Point, int> M;
    long long ans = 0;
    for (auto it : a) {
        Point t = it.first;
        ans += M[Point(-t.y, t.x)];
        M[t]++;
    }
    cout << ans << '\n';
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
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
