#include <bits/stdc++.h>

using namespace std;

void open_file() {
    #ifdef THEMIS
        freopen("sol.inp", "r", stdin);
        freopen("sol.out", "w", stdout);
    #endif // THEMIS
}

void sol() {
    string s;
    string T = "ICPC";
    while (cin >> s) {
        if (s == "$") return;
        int n = (int)s.size();
        vector<vector<long long> > dp(n + 1, vector<long long>(4, 0));

        for (int i = 1; i <= n; i++) {
            if (s[i - 1] == 'I') dp[i][0] = 1;
        }
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j < 4; j++) {
                if (s[i - 1] == T[j]) {
                    dp[i][j] = dp[i - 2][j - 1] + dp[i][j];
                }
                dp[i][j] += dp[i - 1][j];
            }
            dp[i][0] += dp[i - 1][0];
        }

        cout << dp[n][3] << '\n';
    }

}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    int t = 1;
//    cin >> t;
    while (t--) sol();
}
