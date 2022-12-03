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

// multiply matrix and power(a ^ n)
template <typename T>
vector<vector<T>> operator*(const vector<vector<T>>& a, const vector<vector<T>>& b) {
    if ((int)a.size() == 0 || (int)b.size() == 0) {
        return {{}};
    }
    int m = (int)a.size();
    int n = (int)a[0].size();
    assert(n == (int)b.size());
    int p = (int)b[0].size();
    vector<vector<T>> c(m, vector<T>(p));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                // update: c[i][j]
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

template <typename T>
vector<vector<T>>& operator*=(vector<vector<T>>& a, vector<vector<T>>& b) {
    return a = a * b;
}

template <typename T, typename U>
vector<vector<T>> power(vector<vector<T>>& a, U n) {
    assert(n >= 0);
    int sz = (int)a.size();
    assert(sz == (int)a[0].size());
    vector<vector<T>> ans(sz, vector<T>(sz, 0));
    for (int i = 0; i < sz; i++) {
        ans[i][i] = 1;
    }

    for (; n; n >>= 1, a *= a) {
        if (n & 1) {
            ans *= a;
        }
    }
    return ans;
}
void sol() {
    int n;
    cin >> n;
    vector<vector<double> > a = {{0.5, 0.5}, {1, 0}};
    vector<vector<double> > b = {{0, 100}, {100, 0}};

    auto c = power(a, n - 1);
    c *= b;

    cout << fixed << setprecision(10) << c[1][0] << " " << c[1][1] << endl;
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
