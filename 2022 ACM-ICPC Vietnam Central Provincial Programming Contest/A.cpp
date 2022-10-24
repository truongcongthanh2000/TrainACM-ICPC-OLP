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

bool visit[305][305][305];
bool dp[305][305][305];

int n, k;
string s;

bool f(int L, int R, int k1, int k2, int d) {
    if (visit[L][R][k1]) {
        return dp[L][R][k1];
    }

    if (k1 == 0) {
        return true;
    }

    if (k2 == 0) {
        return false;
    }

    visit[L][R][k1] = true;
    bool& ans = dp[L][R][k1];

    if (d == 0) {
        if (f(L + 1, R, k1 - (s[L] == 'B'), k2, 1) == 0) return ans = false;
        if (f(L, R - 1, k1 - (s[R] == 'B'), k2, 1) == 0) return ans = false;
        return ans = true;
    } else {
        if (f(L + 1, R, k1, k2 - (s[L] == 'B'), 0) == 1) return ans = true;
        if (f(L, R - 1, k1, k2 - (s[R] == 'B'), 0) == 1) return ans = true;
        return ans = false;
    }
}

void sol() {
    cin >> n >> k;
    cin >> s;

    if (f(0, n - 1, k, k, 0) == false)
        cout << "YES" << '\n';
    else
        cout << "NO" << '\n';
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
