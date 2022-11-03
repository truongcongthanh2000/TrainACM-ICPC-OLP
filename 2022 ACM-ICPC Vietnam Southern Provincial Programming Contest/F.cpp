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
    int n, k, x;
    while (cin >> n >> k >> x) {
        if (n == 0 && k == 0 && x == 0) return;

        vector<int> a(n);
        vector<double> l(n), p(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> l[i] >> p[i];
            l[i] /= 100.0;
            p[i] /= 100.0;
        }

        vector<int> h(n);
        iota(h.begin(), h.end(), 0);

        // a[i] * p[i] / (l[i] * (1 - p[i])) increase
        sort(h.begin(), h.end(), [&](int i, int j) {
            return p[i] * a[i] * (l[j] * (1 - p[j])) < p[j] * a[j] * (l[i] * (1 - p[i]));
        });

        vector<double> dp(n + 1, x);

        for (int i = 0; i < k; i++) {
            vector<double> ndp(n + 1, 0);
            for (int j = i; j < n; j++) {
                int id = h[j];
                ndp[j + 1] = max(ndp[j + 1], dp[j] * (1 - l[id] + p[id] * l[id]) + p[id] * a[id]);
                ndp[j + 1] = max(ndp[j + 1], ndp[j]);
            }
            swap(dp, ndp);
        }

        cout << fixed << setprecision(2) << dp[n] << '\n';
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
