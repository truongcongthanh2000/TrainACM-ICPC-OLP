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
const int MOD = 998244353;

void sol() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<int> par(n, -1);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        par[i] = p - 1;
        adj[p - 1].push_back(i);
    }
    int order = -1;
    vector<int> L(n), R(n);
    function<void(int)> dfs = [&](int u) {
        L[u] = ++order;
        for (int v : adj[u]) {
            dfs(v);
        }
        R[u] = order;
    };
    dfs(0);
    vector<long long> f(n);
    for (int i = 0; i < n; i++) cin >> f[i];

    auto ok = [&](long long limit) {
        // check can assign max stress of u: f(u) * a(u) <= limit
        vector<long long> g(n), c(n);
        for (int i = 0; i < n; i++) g[i] = limit / f[i];
        for (int u = n - 1; u >= 0; u--) {
            long long sum = 1;
            for (int v : adj[u]) {
                sum += c[v];
            }
            c[u] = max(sum - g[u], 0LL);
        }
        return c[0] == 0;
    };
    // find min for all max stress X
    long long left = 0, right = 1e18;
    while (left <= right) {
        long long mid = (left + right) >> 1;
        if (ok(mid)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    // count number of vertex u sastify max stress of u: f(u) * subtree[u] <= X
    int ans = 0;
    for (int i = 0; i < n; i++) {
        long long value = f[i] * (R[i] - L[i] + 1);
        ans += value >= left;
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

int main(int argc, char *argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
