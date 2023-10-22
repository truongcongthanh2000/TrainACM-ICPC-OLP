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

int b[maxN][20], F[maxN], Res[maxN], d[maxN];
vector <int> a[maxN], bb[maxN];
void DFS(int u, int pa) {
    for (int i = 0; i <= 18; i++) {
        int v = b[u][i];
        if (b[v][i] == 0) {
            break;
        }
        b[u][i + 1] = b[v][i];
    }
    for (int v : a[u]) {
        if (v != pa) {
            b[v][0] = u;
            d[v] = d[u] + 1;
            DFS(v, u);
        }
    }
}

int LCA(int u, int v) {
    if (d[u] < d[v]) {
        swap(u, v);
    }
    int k = d[u] - d[v];
    for (int i = 18; i >= 0; i--) {
        if (k >= (1 << i)) {
            k -= (1 << i);
            u = b[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    int res = 0;
    for (int i = 18; i >= 0; i--) {
        if (b[u][i] != b[v][i]) {
            u = b[u][i];
            v = b[v][i];
        } else {
            res = b[u][i];
        }
    }
    return res;
}

void TruyVan(int u, int v) {
    int root = LCA(u, v);
    F[u]++;
    F[v]++;
    F[root] -= 2;
}

void visit(int u, int pa) {
    for (int i = 0; i < a[u].size(); i++) {
        int v = a[u][i];
        int pos = bb[u][i];
        if (v != pa) {
            visit(v, u);
            Res[pos] = F[v];
            F[u] += F[v];
        }
    }
}
void sol() {
    int n;
    cin >> n;
    vector<int> c1(n), c2(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v >> c1[i] >> c2[i];
        u--;
        v--;
        a[u].push_back(v);
        a[v].push_back(u);
        bb[u].push_back(i);
        bb[v].push_back(i);
    }
    DFS(0, -1);
    for (int i = 0; i < n - 1; i++) TruyVan(i, i + 1);
    visit(0, -1);
    long long ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans += min(1LL * Res[i] * c1[i], 1LL * c2[i]);
    }
    cout << ans << '\n';
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
