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
const int N = 1e5 + 5;

struct Trace {
    int ta, tb, end0, digit;
};
string L, R;
double dp[N][2][2][2];
bool vis[N][2][2][2];
Trace trace[N][2][2][2];

bool umax(double& a, double b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}
double solve(int pos, int ta, int tb, int end0) {
    if (pos == (int)R.size()) {
        return 0;
    }
    double& res = dp[pos][ta][tb][end0];
    if (vis[pos][ta][tb][end0]) {
        return res;
    }

    vis[pos][ta][tb][end0] = 1;
    res = -INF;

    for (int i = (ta ? 0 : L[pos] - '0'); i <= (tb ? 9 : R[pos] - '0'); ++i) {
        int nta = (ta || (i > L[pos] - '0'));
        int ntb = (tb || (i < R[pos] - '0'));
        int nend0 = end0 || (i > 0);
        double ndp = solve(pos + 1, nta, ntb, nend0);

        if (nend0) {
            if (i > 0)
                ndp += log2(i);
            else
                ndp = -INF;
        }

        if (umax(res, ndp)) {
            trace[pos][ta][tb][end0] = {nta, ntb, nend0, i};
        }
    }
    return res;
}
void sol() {
    cin >> L >> R;
    while (L.size() < R.size()) {
        L = '0' + L;
    }
    solve(0, 0, 0, 0);

    if (dp[0][0][0][0] < EPS) {
        cout << 0;
        return;
    }

    int i = 0, j = 0, k = 0, end0 = 0, ans = 1;
    while (i < R.size()) {
        if (end0 || trace[i][j][k][end0].digit > 0) {
            ans = 1LL * ans * trace[i][j][k][end0].digit % MOD;
        }
        Trace temp = trace[i][j][k][end0];
        i++;
        j = temp.ta;
        k = temp.tb;
        end0 = temp.end0;
    }
    cout << ans;
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
