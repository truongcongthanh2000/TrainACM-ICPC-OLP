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
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    for (int j = 0; j < m; j++) {
        vector<int> nen;
        for (int i = 0; i < n; i++) nen.push_back(a[i][j]);
        sort(nen.begin(), nen.end());
        nen.resize(unique(nen.begin(), nen.end()) - nen.begin());

        for (int i = 0; i < n; i++) {
            a[i][j] = lower_bound(nen.begin(), nen.end(), a[i][j]) - nen.begin();
        }
    }

    vector<vector<int>> adj(n);
    auto trans = [&](vector<int> p, vector<int> op) -> vector<int> {
        for (int col : op) {
            for (int i = 0; i < n; i++) {
                int row = p[i];
                adj[a[row][col]].push_back(i);
            }

            vector<int> q;

            for (int v = 0; v < n; v++) {
                for (int i : adj[v]) {
                    q.push_back(p[i]);
                }
                adj[v].clear();
            }

            swap(p, q);
        }
        return p;
    };

    vector<int> op(s);
    for (int i = 0; i < s; i++) {
        cin >> op[i];
        op[i] -= 1;
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);

    auto p_b = trans(p, op);

    if (p == p_b) {
        cout << 0 << '\n';
        return;
    }

    vector<vector<int>> adj_mask(m + 1);
    for (int i = 0; i < (1 << m); i++) {
        adj_mask[__builtin_popcount(i)].push_back(i);
    }

    vector<int> ans(m + 2, INF);

    for (int len = 1; len <= m; len++) {
        bool has = false;
        for (int mask : adj_mask[len]) {
            vector<int> op;
            for (int i = 0; i < m; i++) {
                int bit = (mask >> i) & 1;
                if (bit) {
                    op.push_back(i);
                }
            }
            do {
                auto p_b2 = trans(p, op);
                if (p_b == p_b2) {
                    has = true;
                    ans = min(ans, op);
                }
            } while (next_permutation(op.begin(), op.end()));
        }
        if (has) {
            cout << len << '\n';
            for (int x : ans) cout << x + 1 << ' ';
            return;
        }
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
