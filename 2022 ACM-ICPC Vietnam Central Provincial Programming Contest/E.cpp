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

void sol() {
    int R, C, n;
    cin >> R >> C >> n;

    vector<vector<int>> s(R + 1, vector<int>(C + 1, 0));
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> s[i][j];
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    }

    auto sum = [&](int x, int y, int u, int v) {
        return s[u][v] - s[x - 1][v] - s[u][y - 1] + s[x - 1][y - 1];
    };

    vector<int> p(n);
    cin >> p;

    vector<vector<vector<int>>> dp(R + 1, vector<vector<int>>(C + 1, vector<int>(n, -1)));

    function<int(int, int, int)> f = [&](int x, int y, int i) {
        if (dp[x][y][i] != -1) {
            return dp[x][y][i];
        }

        if (i == n - 1) {
            if (sum(x, y, R, C) <= p[i])
                return dp[x][y][i] = 1;
            else
                return dp[x][y][i] = 0;
        }

        int& ans = dp[x][y][i];
        ans = 0;

        for (int r = x; r < R; r++) {
            if (sum(x, y, r, C) <= p[i]) {
                ans = (ans + f(r + 1, y, i + 1)) % MOD;
            }
        }

        for (int c = y; c < C; c++) {
            if (sum(x, y, R, c) <= p[i]) {
                ans = (ans + f(x, c + 1, i + 1)) % MOD;
            }
        }

        return ans;
    };

    cout << f(1, 1, 0);
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
