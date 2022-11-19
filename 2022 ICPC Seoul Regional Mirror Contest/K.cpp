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
    int n, p, q;
    cin >> n >> p >> q;
    vector<string> a(n), b(p), c(q);
    cin >> a >> b >> c;

    vector<vector<int> > dp(p + 1, vector<int>(q + 1, 0));
    for (string s : a) {
        vector<vector<int> > ndp = dp;
        for (int i = 0; i <= p; i++) {
            for (int j = 0; j <= q; j++) {
                if (i < p) {
                    if (b[i] == s) {
                        ndp[i + 1][j] = max(ndp[i + 1][j], dp[i][j] + 1);
                    }
                    ndp[i + 1][j] = max(ndp[i + 1][j], ndp[i][j]);
                }
                if (j < q) {
                    if (c[j] == s) {
                        ndp[i][j + 1] = max(ndp[i][j + 1], dp[i][j] + 1);
                    }
                    ndp[i][j + 1] = max(ndp[i][j + 1], ndp[i][j]);
                }
            }
        }
        swap(ndp, dp);
    }

    cout << dp[p][q];
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
