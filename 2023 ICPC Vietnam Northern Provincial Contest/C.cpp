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

const int maxN = 2e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    int n, m;
    cin >> n >> m;
    vector<int> a;
    int x;
    cin >> x;
    if (x != 1) {
        a.push_back(x);
    }
    for (int i = 1; i < m; i++) {
        int y;
        cin >> y;
        a.push_back(y);
    }
    m = (int)a.size();
    vector<int> d(m, 0);

    map<vector<int>, int> dp[n + 1];
    function<int(int, vector<int>)> f = [&](int pos, const vector<int>& state) {
        if (pos == n) {
            return 1;
        }
        if (dp[pos].count(state)) {
            return dp[pos][state];
        }
        int &ans = dp[pos][state];
        ans = 0;
        vector<int> nstate = state;
        for (int i = 0; i < m; i++) {
            if (nstate[i]) {
                nstate[i] = (nstate[i] + 1) % a[i];
            }
        }
        if (x == 1) {
            ans = (ans + f(pos + 1, nstate)) % MOD;
        }
        for (int i = 0; i < m; i++) {
            if (state[i] == 0 || a[i] <= state[i]) {
                nstate[i] = 1;
                ans = (ans + f(pos + 1, nstate)) % MOD;
                if (state[i] == 0) {
                    nstate[i] = 0;
                } else {
                    nstate[i] = (state[i] + 1) % a[i];
                }
            }
        }
        return ans;
    };
    cout << f(0, d) << '\n';
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
