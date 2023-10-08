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

const int maxN = 2e6 + 100;
const int MOD = 123456789;

void sol() {
    int n, m, k;
    cin >> n >> m >> k;
    if (n > m) {
        swap(n, m);
    }
    auto check_valid = [&](int mask) {
        bool valid = true;
        for (int i = 0; i < n - 1; i++) {
            if ((mask >> i) & 1) {
                int bit = (mask >> (i + 1)) & 1;
                if (bit) {
                    valid = false;
                    break;
                }
            }
        }
        return valid;
    };
    vector<int> mask_can_used, n1;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (check_valid(mask)) {
            mask_can_used.push_back(mask);
            n1.push_back(__builtin_popcount(mask_can_used.back()));
        }
    }
    vector<vector<int>> adj(mask_can_used.size());
    for (int idx = 0; idx < mask_can_used.size(); idx++) {
        int mask = mask_can_used[idx];
        vector<int> bits(n, 1);
        for (int i = 0; i < n; i++) {
            int bit = (mask >> i) & 1;
            if (bit) {
                for (int d = -1; d <= 1; d++) {
                    if (i + d >= 0 && i + d < n) {
                        bits[i + d] = 0;
                    }
                }
            }
        }
        vector<int> can_used;
        for (int i = 0; i < n; i++) {
            if (bits[i]) {
                can_used.push_back(i);
            }
        }
        for (int mask2 = 0; mask2 < (1 << can_used.size()); mask2++) {
            int calc_mask = 0;
            for (int i = 0; i < (int)can_used.size(); i++) {
                int bit = (mask2 >> i) & 1;
                if (bit) {
                    calc_mask ^= 1 << can_used[i];
                }
            }
            if (check_valid(calc_mask)) {
                int idx2 = lower_bound(mask_can_used.begin(), mask_can_used.end(), calc_mask) - mask_can_used.begin();
                adj[idx].push_back(idx2);
            }
        }
        sort(adj[idx].begin(), adj[idx].end(), [&](int a, int b) {
            return n1[a] < n1[b];
        });
    }
    auto add = [&](int& a, int b) {
        a += b;
        if (a >= MOD) {
            a -= MOD;
        }
    };
    vector<vector<int>> dp(mask_can_used.size(), vector<int>(k + 1, 0));
    for (int i = 0; i < mask_can_used.size(); i++) {
        if (n1[i] <= k) {
            dp[i][n1[i]] = 1;
        }
    }
    for (int c = 1; c < m; c++) {
        vector<vector<int>> ndp(mask_can_used.size(), vector<int>(k + 1, 0));
        for (int u = 0; u < mask_can_used.size(); u++) {
            for (int s = 0; s <= k; s++) {
                if (dp[u][s]) {
                    for (int v : adj[u]) {
                        if (s + n1[v] > k) {
                            break;
                        }
                        add(ndp[v][s + n1[v]], dp[u][s]);
                    }
                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int i = 0; i < mask_can_used.size(); i++) {
        add(ans, dp[i][k]);
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
