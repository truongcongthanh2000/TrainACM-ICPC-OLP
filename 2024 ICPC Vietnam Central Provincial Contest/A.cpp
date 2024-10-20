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

int dp[105][maxN][2];
void sol() {
    int n, w, h;
    cin >> n >> w >> h;
    vector<vector<int>> a(n + 1, vector<int>(2));
    int sum_c = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i][0] >> a[i][1];
        sum_c += a[i][1];
    }
    // dp[i][c][used] = min total_w with total_c = c with put item i in the other hand or not
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= sum_c; j++) {
            for (int k = 0; k < 2; k++) {
                dp[i][j][k] = INF;
            }
        }
    }
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= sum_c; j++) {
            dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][0]);
            dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j][1]);
            if (j >= a[i][1]) {
                dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j - a[i][1]][0] + a[i][0]);
                dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j - a[i][1]][1] + a[i][0]);
                if (a[i][0] <= h) {
                    dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j - a[i][1]][0]);
                }
            }
        }
    }
    int ans = sum_c;
    while (ans >= 0 && min(dp[n][ans][0], dp[n][ans][1]) > w) ans--;
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
