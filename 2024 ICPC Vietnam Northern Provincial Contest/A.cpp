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

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    int n, d, h;
    cin >> n >> d >> h;
    vector<int> a(n);
    cin >> a;
    // dp(u) = minimum sum of a(i) sequence from 0 and end at u
    // dp(u) = min(dp[v]) + a[u] for all v sastify |a(u) - a(v)| <= h and u - v <= d, v < u
    vector<int> dp(n, INF);
    dp[0] = a[0];
    for (int i = 0; i < n; i++) {
        if (dp[i] != INF) {
            for (int j = i + 1; j < min(n, i + d + 1); j++) {
                if (abs(a[i] - a[j]) <= h) {
                    dp[j] = min(dp[j], dp[i] + a[j]);
                }
            }
        }
    }
    if (dp[n - 1] != INF)
        cout << dp[n - 1] << '\n';
    else
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
