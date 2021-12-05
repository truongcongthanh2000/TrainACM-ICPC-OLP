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

void solve() {
    int a, h; cin >> a >> h;
    long double res = 5.0 * h * a / 6;
    res = max(res, (long double)(200.0 * h / 3));
    if (a != 100) {
        long double x = 1.0 * h / 12 * (700 - 8 * a) / (100 - a);
        if (x * 3 <= h && x * 6 >= h) {
            long double y = a + 6.0 * (x - h / 6.0) / h * (100 - a);
            res = max(res, y * (h - x));
        }
    }
    cout << fixed << setprecision(10) << res;
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
