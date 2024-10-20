#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<vector<T>> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) {
        for (const auto &value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (auto &x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-9;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 1e5 + 100;
const int MOD = 998244353;

void sol() {
    int n;
    long long k;
    cin >> n >> k;
    vector<int> a(n);
    cin >> a;
    vector<int> c(1 << 20, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) c[a[i] & a[j]]++;
    }
    vector<long long> dp(1 << 20, 0); // dp[mask] = sum(c(sub_mask), sub_mask & mask == sub_mask)
    for (int i = 0; i < (1 << 20); i++) dp[i] = c[i];
    for (int i = 0; i < 20; i++) {
        for (int mask = 0; mask < (1 << 20); mask++){
            if ((mask >> i) & 1) {
                dp[mask] += dp[mask ^ (1 << i)];
            }
        }
    }

    int all_mask = (1 << 20) - 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int mask0 = all_mask ^ (a[i] & a[j]);
            if (k > dp[mask0]) {
                k -= dp[mask0];
            } else {
                for (int u = 0; u < n; u++) {
                    for (int v = 0; v < n; v++) {
                        if ((a[i] & a[j] & a[u] & a[v]) == 0) {
                            k--;
                            if (k == 0) {
                                cout << i + 1 << " " << j + 1 << " " << u + 1 << " " << v + 1 << '\n';
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << -1 << '\n';
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

int main(int argc, char *argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
