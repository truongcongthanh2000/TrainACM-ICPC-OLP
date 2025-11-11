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

void sol() {
    long long n, m, a; cin >> n >> m >> a;
    if (a % n == 0 || a % m == 0) {
        cout << 1;
        return;
    }
    if (a < n || a < m) {
        cout << 2;
        return;
    }
    int res = 1e9;
    for (int i = 1; i < m; ++i) {
        long long tmp = a - i * n;
        ///if (tmp < 0) break;
        if ((tmp >= 0 && tmp % (m - i) == 0) || (a % i == 0 && a <= n * i)) {
            cout << 2;
            return;
        }
    }
    swap(n, m);
    for (int i = 1; i < m; ++i) {
        long long tmp = a - i * n;
        ///if (tmp < 0) break;
        if ((tmp >= 0 && tmp % (m - i) == 0) || (a % i == 0 && a <= n * i)) {
            cout << 2;
            return;
        }
    }
    cout << 3;
}

void solve() {
    int T;
    //cin >> T;
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
