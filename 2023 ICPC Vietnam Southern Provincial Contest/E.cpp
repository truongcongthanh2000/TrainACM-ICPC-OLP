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

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e5 + 100;
const int MOD = 1e9 + 7;

int dp[2010][2010];
// số lượng dãy ngoặc đúng có tổng là sum và số ( là nopens
int f(int sum, int nopen) {
    if (sum == 0 && nopen == 0) return 1;
    if (dp[sum][nopen] != -1) {
        return dp[sum][nopen];
    }
    int& res = dp[sum][nopen];
    res = 0;
    // chọn (
    if (nopen > 0) res += f(sum + 1, nopen - 1);
    // chọn )
    if (sum > 0) res += f(sum - 1, nopen);
    res = min(res, INF);
    return res;
}
void sol() {
    memset(dp, -1, sizeof(dp));
    auto sol1 = [&](int n, int k) {
        int sum = 0, nopen = 0, nclosed = 0;
        vector<int> ans(2 * n);
        for (int i = 0; i < 2 * n; i++) {
            if (nopen < n && f(sum + 1, n - nopen - 1) >= k) {
                ans[nopen] = i + 1;
                nopen++;
                sum++;
            } else {
                if (nopen < n) k -= f(sum + 1, n - nopen - 1);
                ans[n + nclosed] = i + 1;
                nclosed++;
                sum--;
            }
        }
        for (int i = 0; i < 2 * n; i++) cout << ans[i] << ' ';
        cout << '\n';
    };
    auto sol2 = [&](int n, const vector<int>& a) {
        int sum = 0, nopen = 0;
        int k = 1;
        for (int i = 0; i < 2 * n; i++) {
            if (a[nopen] != i + 1) {
                k += f(sum + 1, n - nopen - 1);
                sum--;
            } else {
                nopen++;
                sum++;
            }
        }
        cout << k << '\n';
    };
    int t;
    while (cin >> t) {
        if (t == 1) {
            int n, k;
            cin >> n >> k;
            sol1(n, k);
        } else {
            int n;
            cin >> n;
            vector<int> a(2 * n);
            for (int i = 0; i < 2 * n; i++) cin >> a[i];
            sol2(n, a);
        }
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
