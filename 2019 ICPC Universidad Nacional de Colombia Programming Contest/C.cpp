#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
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
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

int dp[1005][1005];

void sol() {
    string s, t;
    cin >> s >> t;
    int n = (int)s.size();
    int m = min(1000, n);
    int res = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++) {
            while (i + dp[i][j] < n && j + dp[i][j] < n && s[i + dp[i][j]] == t[j + dp[i][j]]) dp[i][j]++;
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
            res = max(res, dp[i][j]);
        }
    }
    if (res * 100 >= 99 * n) cout << "Long lost brothers D:";
    else cout << "Not brothers :(";
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
