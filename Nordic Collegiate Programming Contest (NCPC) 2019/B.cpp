#pragma GCC diagnostic ignored "-Wunused-parameter"

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
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 10;

struct Point {
    long long x, y;
    Point(){};
};

long long Ngang(vector<Point> &A) {
    long long x = A[0].x + A[1].x + A[2].x;
    long long y = max(A[0].y, max(A[1].y, A[2].y));
    return x * y;
}

long long Chong(vector<Point> &A) {
    long long x = max(A[0].x + A[1].x, A[2].x);
    long long y = max(A[0].y, A[1].y) + A[2].y;
    return x * y;
}

void sol() {
    vector<Point> a(3);
    cin >> a[0].x >> a[0].y >> a[1].x >> a[1].y >> a[2].x >> a[2].y;
    vector<int> p(3);
    iota(p.begin(), p.end(), 0);
    long long res = 8e18;
    do {
        vector<Point> b(3);
        for (int i = 0; i < 3; i++) b[i] = a[p[i]];
        for (int mask = 0; mask < (1 << 3); mask++) {
            vector<Point> c = b;
            for (int i = 0; i < 3; i++) {
                int bit = (mask >> i) & 1;
                if (bit) swap(c[i].x, c[i].y);
            }
            res = min(res, Ngang(c));
            res = min(res, Chong(c));
        }
    }
    while (next_permutation(p.begin(), p.end()));
    cout << res << '\n';
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
