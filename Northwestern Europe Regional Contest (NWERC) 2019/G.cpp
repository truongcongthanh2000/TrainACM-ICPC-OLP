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

const int maxN = 5e2 + 10;

long double C[maxN][maxN];

void precalc() {
    C[0][0] = 1;
    for (int i = 1; i < maxN; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
//    for (int i = 0; i <= 10; i++) {
//        for (int j = 0; j <= 10; j++) cout << C[i][j] << ' ';
//        cout << '\n';
//    }
}

long double a[maxN];
void sol() {
    precalc();
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    auto S = [&](int t, int i) -> long double {
        int j = (i - t + n) % n;
        long double res = 0;
        for (int k = 0; k <= t; k++) res += a[(j + k) % n];
        return res;
    };
    cout << fixed << setprecision(10);
    if (k == 1) {
        for (int i = 0; i < n; i++) {
            long double res = 100.0 / n;
            cout << res << ' ';
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        long double res = 0;
        for (int t = 0; t <= n - k; t++) {
            res += C[n - t - 2][k - 2] * S(t, i);
        }
        res /= C[n][k];
        cout << res << ' ';
    }
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
