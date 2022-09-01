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
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T> >& a) {
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
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
#ifdef THEMIS
    freopen(INP ".txt", "r", stdin);
    freopen(OUT ".txt", "w", stdout);
#endif  // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    string p, s;
    cin >> p >> s;
    int n = (int)s.size();
    set<string> ms;
    for (int i = 0; i < n; i++) {
        ms.insert(s);
        s += s[0];
        s.erase(s.begin());
    }
    
    auto dp_subsequence = [&](string s, string pattern) {
        int n = (int)s.size();
        int m = (int)pattern.size();
        if (n < m) return 0;
        vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= n; i++) dp[0][i] = 1;
        for (int j = 1; j <= m; j++) {
            for (int i = 1; i <= n; i++) {
                dp[j][i] = dp[j][i - 1];
                if (s[i - 1] == pattern[j - 1]) {
                    dp[j][i] = (dp[j - 1][i - 1] + dp[j][i]) % MOD;
                }
            }
        }
        return dp[m][n];
    };

    int ans = 0;
    for (string s : ms) {
        int dp = dp_subsequence(p, s);
        ans = (ans + dp) % MOD;
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
        cerr << "Processing test = " << TestCase << '\n';
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
    open_file();
    solve();
    return 0;
}
