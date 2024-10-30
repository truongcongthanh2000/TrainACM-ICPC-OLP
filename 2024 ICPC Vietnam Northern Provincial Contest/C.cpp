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

template <typename T>
struct sum_2D {
    int n, m;
    vector<vector<T>> a;
    sum_2D(int _n, int _m) {
        n = _n;
        m = _m;
        a = vector<vector<T>>(n + 1, vector<T>(m + 1, 0));
    }

    void set_value(int x, int y, T value) {
        a[x][y] = value;
    }

    void precalc() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }

    T get(int xL, int yL, int xR, int yR) {
        return a[xR][yR] - a[xL - 1][yR] - a[xR][yL - 1] + a[xL - 1][yL - 1];
    }
};

void sol() {
    // TL: 6s, assume n <= m we can do a solution O(n * (n + 1) / 2 * m) ~ 5 x 10^8
    // for n > m, we can rotate to the table m x n instead
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) cin >> a[i];
    if (n > m) {
        vector<vector<int>> b(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) b[i][j] = a[j][i];
        }
        swap(a, b);
        swap(n, m);
    }
    sum_2D<long long> s2d(n, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) s2d.set_value(i, j, a[i - 1][j - 1]);
    }
    s2d.precalc();
    // To find (r1, c1) -> (r2, c2) that sum_2d is maximum and divisible by k
    // We can loop (r1, r2) in O(n * (n + 1) / 2) and do Kadane (with modular) to find (c1, c2) in O(m)
    // Note: sum of all elements from L to R is prefix_sum[R] - prefix_sum[L - 1], so prefix_sum[R] = prefix_sum[L - 1] (mod k)
    // And prefix_sum[L] <= prefix_sum[L + 1] due a[i][j] >= 0, so just keep track the first value of prefix_sum[L - 1] mod k
    vector<int> idx(k, 0);
    vector<long long> first_value(k, 0);
    int time = 0;
    long long ans = 0;
    for (int r1 = 1; r1 <= n; r1++) {
        for (int r2 = r1; r2 <= n; r2++) {
            time++;
            idx[0] = time;
            for (int c = 1; c <= m; c++) {
                long long value = s2d.get(r1, 1, r2, c);
                int value_mod = value % k;
                if (idx[value_mod] == time) {
                    ans = max(ans, value - first_value[value_mod]);
                } else {
                    idx[value_mod] = time;
                    first_value[value_mod] = value;
                }
            }
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
