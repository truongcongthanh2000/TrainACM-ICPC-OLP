#include <bits/stdc++.h>

using namespace std;

void open_file() {
    #ifdef THEMIS
        freopen("sol.inp", "r", stdin);
        freopen("sol.out", "w", stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 100;
const long long INF = 2e9 + 100;
const long double EPS = 1e-9;
const long double PI = acos(-1);

struct point {
    long double x, y;
    point(){
        x = 0, y = 0;
    }
    point(long double _x, long double _y) {
        x = _x; y = _y;
    }
    point(const point &other) {
        x = other.x;
        y = other.y;
    }
    long double len() {
        return sqrt(x * x + y * y);
    }
    int operator < (const point &other) { return make_pair(x, y) < make_pair(other.x, other.y); }
    int operator == (const point &other) {
        return abs(x - other.x) < EPS && abs(y - other.y) < EPS;
    }
    int operator != (const point &other) {
        return !(*this == other);
    }
    point operator + (const point &p) const { return point(x + p.x, y + p.y); }
    point operator - (const point &p) const { return point(x - p.x, y - p.y); }
    point operator * (long double c) const { return point(x * c, y * c); }
    point operator / (long double c) const { return point(x / c, y / c); }
};

long double cross(point a, point b) { return a.x * b.y - a.y * b.x; }
long double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
point ProjectOnLine(point a, point b, point c) {
    return a + (b - a) * dot(c - a, b - a) / dot(b - a, b - a);
}

long double angle(point A, point O, point B) {
    point AO = A - O;
    point BO = B - O;
    long double ans = dot(AO, BO) / (AO.len() * BO.len());
    return acos(ans);
}

bool ccw(point a, point b, point c) {
    point ba = b - a;
    point ca = c - a;
    return ba.x * ca.y > ba.y * ca.x;
}

bool cw(point a, point b, point c) {
    point ba = b - a;
    point ca = c - a;
    return ba.x * ca.y < ba.y * ca.x;
}

void sol() {
    int n;
    cin >> n;
    vector<point> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }
    long double x = 0, y = 0, a = 0;
    for (int i = 0; i < n; i++) {
        x += (p[i].x + p[(i + 1) % n].x) * (p[i].x * p[(i + 1) % n].y - p[(i + 1) % n].x * p[i].y);
        y += (p[i].y + p[(i + 1) % n].y) * (p[i].x * p[(i + 1) % n].y - p[(i + 1) % n].x * p[i].y);
        a += p[i].x * p[(i + 1) % n].y - p[(i + 1) % n].x * p[i].y;
    }
    a /= 2; x /= a * 6; y /= a * 6;
    point G(x, y);

    vector<long double> f(n);
    for (int i = 0; i < n; i++) {
        long double goc = angle(p[i], G, p[(i + 1) % n]);
        f[i] = goc / PI / 2;
    }

    vector<int> next(n, 0);
    iota(next.begin(), next.end(), 0);

    for (int i = 0; i < n; i++) {
        point X = ProjectOnLine(p[i], p[(i + 1) % n], G);
        if (ccw(G, X, p[i]) && X != p[i]) {
            next[i] = (i - 1 + n) % n;
        }
        if (cw(G, X, p[(i + 1) % n]) && X != p[(i + 1) % n]) {
            next[i] = (i + 1) % n;
        }
    }

    vector<double> dp(n, 0);
    function<int(int)> find_root = [&](int u) {
        return next[u] == u ? u : next[u] = find_root(next[u]);
    };

    for (int i = 0; i < n; i++) {
        int r = find_root(i);
        dp[r] += f[i];
    }

    cout << fixed << setprecision(10);
    for (int i = 0; i < n; i++) cout << dp[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    int t = 1;
//    cin >> t;
    while (t--) sol();
}
