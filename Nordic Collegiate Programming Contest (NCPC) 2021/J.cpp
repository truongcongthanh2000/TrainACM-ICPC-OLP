#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".txt","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

struct Point {
    double x, y;
};

double dist(Point A, Point B) {
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt(x * x + y * y);
}

void sol() {
    Point A, B, C, D;
    cin >> A.x >> A.y >> C.x >> C.y >> B.x >> B.y >> D.x >> D.y;
    auto f = [&](double t) {
        Point I;
        I.x = A.x + (B.x - A.x) * t;
        I.y = A.y + (B.y - A.y) * t;
        Point J;
        J.x = C.x + (D.x - C.x) * t;
        J.y = C.y + (D.y - C.y) * t;
        return dist(I, J);
    };
    double L = 0, R = 1;
    for (int iter = 0; iter < 100; iter++) {
        double t1 = L + (R - L) / 3.0;
        double t2 = R - (R - L) / 3.0;
        if (f(t1) > f(t2)) R = t2; 
        else L = t1;
    }
    double ans = f((L + R) / 2.0);
    cout << fixed << setprecision(10) << ans;
}

void solve() {
    int T = 1;
    //cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
