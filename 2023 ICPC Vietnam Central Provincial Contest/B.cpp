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
    vector<int> a(n);
    cin >> a;
    sort(a.begin(), a.end());
    vector<int> m(1234567, 0);
    for (int i = 0; i < n; i++) {
        m[a[i]] = i;
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (__gcd(a[i], a[j]) == 1) {
                adj[i].push_back(j);
            }
        }
    }
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n + 1, 0)));
    for (int i = 0; i < n; i++) dp[i][i][0] = 1;
    for (int k = 0; k < n; k++) {
        for (int u = 0; u < n; u++) {
            for (int v = u; v < n; v++) {
                if (dp[u][v][k]) {
                    for (int nv : adj[v]) {
                        dp[u][nv][k + 1] = (dp[u][nv][k + 1] + dp[u][v][k]) % 2023;
                    }
                }
            }
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int ai, aj, k;
        cin >> ai >> aj >> k;
        int s = m[ai], t = m[aj];
        cout << dp[s][t][k] << '\n';
    }
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
