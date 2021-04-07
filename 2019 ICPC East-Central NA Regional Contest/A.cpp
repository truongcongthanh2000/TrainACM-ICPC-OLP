#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e5 + 10;

struct Point {
    int x, y;
    Point(){};
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

int Dist(Point A, Point B) {
    int x = A.x - B.x;
    int y = A.y - B.y;
    return x * x + y * y;
}
Point a[maxN], b[maxN], c[maxN];
int ok[maxN], ok2[maxN];

vector<int> adj[maxN];
vector<int> adj_reverse[maxN];
typedef pair<int, int> i2;
typedef pair<int, i2> i3;
double get(int n, int m, Point a[], Point b[]) {
    set<i3> S;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int d = Dist(a[i], b[j]);
            S.insert({d, {i, j}});
        }
    }
    double res = 0;
    for (int _ = 1; _ <= n; _++) {
        //cerr << "OK" << '\n';
        i3 A = *S.begin();
        int d = A.first;
        int i = A.second.first;
        int j = A.second.second;
        //cerr << i << " " << j << " " << d << '\n';
        res += sqrt(d);
        for (int k = 1; k <= m; k++) {
            int d = Dist(a[i], b[k]);
            S.erase(i3(d, i2(i, k)));
        }
        for (int k = 1; k <= n; k++) {
            int d = Dist(a[k], b[j]);
            S.erase(i3(d, i2(k, j)));
        }
    }
    return res;
}
void sol() {
    int n, m, p;
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
    for (int i = 1; i <= m; i++) cin >> b[i].x >> b[i].y;
    for (int i = 1; i <= p; i++) cin >> c[i].x >> c[i].y;
    double res = get(n, m, a, b) + get(n, p, a, c);
    cout << fixed << setprecision(10) << res;
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
