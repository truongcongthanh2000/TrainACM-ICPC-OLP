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

long double a[maxN];
long double pre[maxN], suf[maxN];
void sol() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    auto ok = [&](long double mid) {
        long double s = 0;
        pre[0] = -1e18;
        for (int i = 1; i <= n; i++) {
            s += a[i] - mid;
            pre[i] = max(pre[i - 1], s);
        }
        suf[n + 1] = -1e18;
        s = 0;
        for (int i = n; i >= 1; i--) {
            s += a[i] - mid;
            suf[i] = max(suf[i + 1], s);
        }
        long double cost = s;
        long double s_suf = 0;
        s = 0;
        for (int i = n; cost < 0 && i >= 1; i--) {
            s += a[i] - mid;
            s_suf = max(s_suf, s);
            cost = max(cost, pre[i - 1] + s_suf);
        }
        s = 0;
        long double s_pre = 0;
        for (int i = 1; cost < 0 && i <= n; i++) {
            s += a[i] - mid;
            s_pre = max(s_pre, s);
            cost = max(cost, suf[i + 1] + s_pre);
        }
        return cost >= 0;
    };
    long double L = 0, R = 1e9 + 100;
    long double res = 0;
    for (int steps = 0; steps <= 100; steps++) {
        long double mid = (L + R) / 2.0;
        if (ok(mid)) {
            res = mid;
            L = mid;
        }
        else R = mid;
    }
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
