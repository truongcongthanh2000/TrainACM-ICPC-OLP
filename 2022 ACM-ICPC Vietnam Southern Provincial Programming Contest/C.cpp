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

const int maxN = 5e3 + 10;
const int MOD = 1e9 + 7;

pair<int, int> a[maxN];
long long sxw[maxN], sw[maxN];
long long F[maxN][maxN];
long long dp[maxN][maxN];
int p[maxN][maxN];

void sol() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a + 1, a + 1 + n);

    for (int i = 1; i <= n; i++) {
        sxw[i] = sxw[i - 1] + 1LL * a[i].first * a[i].second;
        sw[i] = sw[i - 1] + a[i].second;
    }

    auto get = [&](int L, int R, int j) {
        long long left = 1LL * a[j].first * (sw[j] - sw[L - 1]) - (sxw[j] - sxw[L - 1]);
        long long right = (sxw[R] - sxw[j]) - 1LL * a[j].first * (sw[R] - sw[j]);
        return left + right;
    };

    for (int L = 1; L <= n; L++) {
        int j = L;
        for (int R = L; R <= n; R++) {
            while (j < R && get(L, R, j) > get(L, R, j + 1)) j++;
            F[L][R] = get(L, R, j);
        }
    }

    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) dp[i][j] = INF_LL;
    }

    for (int i = 1; i <= n; i++) {
        dp[1][i] = F[1][i];
        p[1][i] = 1;
    }

    auto get_dp = [&](int i, int j, int k) {
        return dp[k - 1][i] + F[i + 1][j];
    };

    for (int u = 2; u <= k; u++) {
        for (int j = n; j >= u; j--) {
            for (int i = p[u - 1][j], lim = (j < n ? p[u][j + 1] : j - 1); i <= lim; i++) {
                if (dp[u][j] > get_dp(i, j, u)) {
                    dp[u][j] = get_dp(i, j, u);
                    p[u][j] = i;
                }
            }
        }
    }

    cout << dp[k][n];
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
