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

void sol() {
    string T = "RPS";
    string s;
    cin >> s;
    int n = (int)s.size();
    vector<vector<int> > sum(3, vector<int>(n + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            sum[j][i + 1] = sum[j][i];
            if (s[i] == T[j]) sum[j][i + 1]++;
        }
    }
    int ans = 0, pk = 0;
    for (int k = 2; k <= n; k++) {
        int d = 0;
        for (int i = 1; i <= n; i += k) {
            int j = min(i + k - 1, n);
            int mx = 0;
            for (int u = 0; u < 3; u++) {
                mx = max(mx, sum[u][j] - sum[u][i - 1]);
            }
            d += mx;
        }
        if (ans <= d) {
            ans = d;
            pk = k;
        }
    }
    cout << pk << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    cin >> T;
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
