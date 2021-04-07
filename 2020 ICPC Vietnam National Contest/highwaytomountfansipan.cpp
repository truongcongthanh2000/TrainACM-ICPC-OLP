#include <bits/stdc++.h>

using namespace std;

void doc() {
    #ifdef THEMIS
        freopen("solve.inp", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif
}

const int maxN = 2e5 + 100;
const int MOD = 1e9 + 7;
const int INF = 1e6 + 100;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

int w[maxN];
string s[maxN];
int fact[maxN];

int power(int a, int n) {
    int res = 1;
    for (; n; n >>= 1, a = 1LL * a * a % MOD) {
        if (n & 1) {
            res = 1LL * res * a % MOD;
        }
    }
    return res;
}
int inverse(int a) {
    return power(a, MOD - 2);
}

void precalc() {
    fact[0] = 1;
    for (int i = 1; i < maxN; i++) fact[i] = (1LL * fact[i - 1] * i) % MOD;
}

int dp[100][26];
int need[100][26];
void sol() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
    int d;
    cin >> d;
    memset(dp, 0, sizeof(dp));
    memset(need, 0, sizeof(dp));
    for (int i = 1; i <= d; i++) {
        cin >> s[i];
        int len = (int)s[i].size();
        int c = s[i][0] - 'a';
        dp[len][c]++;
    }
    if (n > 50) {
        cout << 0 << '\n';
        return;
    }
    int res = 0;
    for (int i = 1; i <= d; i++) {
        int len = (int)s[i].size();
        int c = s[i][0] - 'a';
        if (len != n) continue;
        dp[len][c]--;
        int cost = 1;
        for (int j = 1; j <= n; j++) {
            int len = w[j];
            int c = s[i][j - 1] - 'a';
            if (dp[len][c] > 0) cost = 1LL * cost * dp[len][c] % MOD;
            else cost = 0;
            dp[len][c]--;
        }
        res = (res + cost) % MOD;
        dp[len][c]++;
        for (int j = 1; j <= n; j++) {
            int len = w[j];
            int c = s[i][j - 1] - 'a';
            dp[len][c]++;
        }
    }
    cout << res << '\n';
}

void solve() {
    int T;
    cin >> T;
    //T = 1;
    while (T--) {
        sol();
    }
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
