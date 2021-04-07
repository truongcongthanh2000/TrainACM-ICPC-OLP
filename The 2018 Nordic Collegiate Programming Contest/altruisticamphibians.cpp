#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-9;
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

const int maxN = 2e5 + 1000;

struct frog {
    int l, w, h;
    frog(){};
    bool operator < (const frog &A) {
        return w > A.w;
    }
};

frog a[maxN];

int dp[100000001];
void sol() {
    int n, d;
    cin >> n >> d;
    for (int i = 1; i <= n; i++) cin >> a[i].l >> a[i].w >> a[i].h;
    sort(a + 1, a + 1 + n);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res += a[i].l + dp[a[i].w] > d;
        for (int w = a[i].w - 1; w >= 1; w--) {
            int next_dp = w + a[i].w > (int)1e8 ? 0 : dp[w + a[i].w];
            dp[w] = max(dp[w], min(d + 1, next_dp + a[i].h));
        }
    }
    cout << res;
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
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
