#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const int QQ = 3e5 + 10;
const int maxN = 2e3 + 100;
const int maxM = 3e5 + 100;
const long long oo = 4e18;
const int INF = 2e9 + 100;
const int MOD = 998244353;
const int Base = 30;
const long double du = 1e-9;
const string YES = "YES";
const string NO = "NO";
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void doc() {
    freopen(INP ".inp","r",stdin);
    freopen(OUT ".out","w",stdout);
}

void sol() {
    int n;
    cin >> n;
    long long s1 = 0, s2 = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (i % 2 == 1) s1 += x;
        else s2 += x;
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int L, R, x;
        cin >> L >> R >> x;
        if (L % 2 == 1) s1 += 1LL * (R - L + 2) / 2 * x;
        else s1 += 1LL * (R - L + 1) / 2 * x;
        if (L % 2 == 0) s2 += 1LL * (R - L + 2) / 2 * x;
        else s2 += 1LL * (R - L + 1) / 2 * x;
        if (n & 1) cout << s1 - s2 << '\n';
        else cout << s2 - s1 << '\n';
    }
}
void solve() {
    int T;
    ///cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        ///cout << "Case #" << TestCase << ": ";
        sol();
    }
}

int main(int argc,char *argv[]) {
    srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
}
