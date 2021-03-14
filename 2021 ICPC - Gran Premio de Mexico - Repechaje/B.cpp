#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 8e18;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
//const int Base = 311;
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

const int maxN = 1e6 + 100;

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

bool Line(point O, point A, point B) {
    sub(A, O);
    sub(B, O);
    return 1LL * A.x * B.y == 1LL * A.y * B.x;
}

int gcd(int x, int y) {
    return y == 0 ? abs(x) : gcd(y, x % y);
}

void sol() {
    int n;
    cin >> n;
    vector<point> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;

    //map<pair<int, int>, int> M;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        map<pair<int, int>, int> M;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            int x = a[j].x - a[i].x;
            int y = a[j].y - a[i].y;
            int g = gcd(x, y);
            x /= g;
            y /= g;
            if (y < 0) {
                y *= -1;
                x *= -1;
            }
            //if (y == 0) x = 1;
            ans = max(ans, ++M[{x, y}]);
        }
    }
    int m = ans + 1;
    if (m / 2 > n - m) cout << n - m << '\n';
    else cout << n / 3 << '\n';
}

void solve() {
    clock_t begin = clock();
    int T;
   // cin >> T;
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
