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
const int MOD = 998244353;

void sol() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(m);
    cin >> a;
    for (int &x : a) x--;
    vector<int> ans(n, 1);
    for (int L = 0; L < m; L++) {
        vector<int> c(n, 0);
        vector<int> sc(k + 2, 0); // sc[i] = number of j that c(j) >= i
        sc[0] = n;
        for (int R = L; R < min(m, L + k); R++) {
            int i = a[R];
            ans[i] = max(ans[i], sc[c[i] + 1] + 1);
            c[i]++;
            sc[c[i]]++;
        }
        for (int i = 0; i < n; i++) {
            ans[i] = max(ans[i], sc[c[i] + 1] + 1);
        }
    }
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
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
