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
const int INF = 2e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e5 + 100;
const int MOD = 1e9 + 7;

int dp[maxN];
int mex(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> c(n + 2, 0);
    for (int x : a) {
        if (x <= n + 1) c[x]++;
    }
    int ans = 0;
    while (c[ans]) ans++;
    return ans;
}

void init_grundy() {
    int n = 10000;
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        vector<int> x;
        for (int j = 1; j * 2 <= i; j++) {
            x.push_back(dp[j] ^ dp[i - j]);
        }
        for (int j = 0; j < i; ++j) x.push_back(dp[j]);
        dp[i] = mex(x);
    }
}
void sol() {
    init_grundy();
    int n;
    cin >> n;
    int sxor = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        sxor ^= dp[x];
    }
    if (sxor) {
        cout << "Alice" << '\n';
    } else {
        cout << "Bob" << '\n';
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
