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

const int maxN = 1e6 + 100;

struct Point {
    int x, y;
    Point(){};
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

long long Area(vector<Point> &a) {
    long long res = 0;
    int n = (int)a.size();
    a.push_back(a[0]);
    for (int i = 0; i < n; i++) {
        res += 1LL * (a[i + 1].x - a[i].x) * (a[i + 1].y + a[i].y);
    }
    return abs(res);
}
void sol() {
    int n;
    cin >> n;
    long long res = 0;
    while (n--) {
        int k;
        cin >> k;
        vector<Point> a(k);
        for (int i = 0; i < k; i++) {
            cin >> a[i].x >> a[i].y;
        }
        res += Area(a);
    }
    cout << res / 2;
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
