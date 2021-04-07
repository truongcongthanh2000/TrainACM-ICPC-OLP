#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "OB"
#define OUT "OB"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-7;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 3e5 + 10;

struct Point {
    int x, y;
    Point(){};
    Point(int _x, int _y) : x(_x), y(_y) {};
};

double dist(Point A, Point B) {
    int x = A.x - B.x;
    int y = A.y - B.y;
    return sqrt(x * x + y * y);
}

void sol() {
    Point O, A, B;
    cin >> O.x >> O.y >> A.x >> A.y >> B.x >> B.y;
    double res;
    if (O.x >= B.x) {
        if (O.y >= B.y) res = dist(O, B);
        if (O.y >= A.y && O.y <= B.y) res = dist(O, Point(B.x, O.y));
        if (O.y <= A.y) res = dist(O, Point(B.x, A.y));
    }
    else {
        if (O.x >= A.x) {
            if (O.y >= B.y) res = dist(O, Point(O.x, B.y));
            else res = dist(O, Point(O.x, A.y));
        }
        else {
            if (O.y >= B.y) res = dist(O, Point(A.x, B.y));
            if (O.y >= A.y && O.y <= B.y) res = dist(O, Point(A.x, O.y));
            if (O.y <= A.y) res = dist(O, A);
        }
    }
    cout << fixed << setprecision(3) << res;
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
