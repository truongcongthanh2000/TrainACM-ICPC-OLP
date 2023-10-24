#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T>>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) {
        for (const auto& value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for (auto& x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 2e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e5 + 100;
const int MOD = 1e9 + 7;

void sol() {
    int n;
    cin >> n;
    vector<int> l(n);
    cin >> l;
    sort(l.begin(), l.end());
    int max_l = 5000;
    vector<vector<int> > dp(n + 1, vector<int>(max_l + 2, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= max_l + 1; j++) {
            if (dp[i][j]) {
                dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % MOD;
                int nj = min(max_l + 1, j + l[i]);
                dp[i + 1][nj] = (dp[i + 1][nj] + dp[i][j]) % MOD;
            }
        }
    }
    vector<vector<int> > sdp(n + 1, vector<int>(max_l + 2, 0));
    for (int i = 0; i <= max_l + 1; i++) sdp[0][i] = 1;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int cost = (sdp[i - 1][max_l + 1] - sdp[i - 1][l[i - 1]] + MOD) % MOD;
        ans = (ans + cost) % MOD;
        sdp[i][0] = dp[i][0];
        for (int j = 1; j <= max_l + 1; j++) {
            sdp[i][j] = (sdp[i][j - 1] + dp[i][j]) % MOD;
        }
    }
    cout << ans << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    // cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        // cerr << "Processing test = " << TestCase << '\n';
        // cout << "Case #" << TestCase << ": ";
        sol();
        // if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc, char* argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
