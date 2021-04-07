#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e6 + 10;

struct DisjointSetUnion { ///Base 1th or Base 0th
    ///if u is root then p[u] < 0 and |p[u]| is size of the Set that u is root
    ///if u is not root then p[u] = x and x, u are belong the same Set
    int n;
    vector <int> p;
    DisjointSetUnion(){};
    DisjointSetUnion(int _n) {
        n = _n;
        p.assign(n + 7, -1); ///p[i] = -1 for all i
    }

    int find_root(int u) { ///find the root in the Set contain u
        if (p[u] < 0) return u; ///u is root
        return p[u] = find_root(p[u]); ///get the root and jump
    }

    void Union(int u, int v) {
        int x = find_root(u);
        int y = find_root(v);
        if (x == y) return;
        if (p[x] > p[y]) swap(x, y); ///small Set point to big Set, p[x] > p[y] so |p[x]| < |p[y]|
        p[x] += p[y];
        p[y] = x;
    }

    bool sameSet(int u, int v) {
        return find_root(u) == find_root(v);
    }

    int numSet() {
        int res = 0;
        for (int i = 0; i < n; i++) res += p[i] < 0;
        return res;
    }
};

vector<int> adj[maxN];
int used[maxN];
int dp[maxN];
void DFS(int u) {
    used[u] = 1;
    for (int v : adj[u]) {
        if (used[v] == 0) DFS(v);
        dp[u] = max(dp[u], dp[v] + 1);
    }
}
void sol() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > a(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> a[i][j];
    }

    auto id = [&](int i, int j) {
        return i * m + j;
    };
    DisjointSetUnion df(n * m);
    for (int num = 0; num < 2; num++) {
        for (int i = 0; i < n; i++) {
            vector<pair<int, int> > c;
            for (int j = 0; j < m; j++) c.push_back({a[i][j], j});
            sort(c.begin(), c.end());
            for (int j = 0; j < m; ){
                int k = j;
                while (k < m && c[k].first == c[j].first) k++;
                for (int u = j; u < k - 1; u++) {
                    int x = id(i, c[u].second);
                    int y = id(i, c[u + 1].second);
                    df.Union(x, y);
                }
                j = k;
            }
        }
        for (int i = 0; i < m; i++) {
            vector<pair<int, int> > c;
            for (int j = 0; j < n; j++) c.push_back({a[j][i], j});
            sort(c.begin(), c.end());
            for (int j = 0; j < n; ){
                int k = j;
                while (k < n && c[k].first == c[j].first) k++;
                for (int u = j; u < k - 1; u++) {
                    int x = id(c[u].second, i);
                    int y = id(c[u + 1].second, i);
                    df.Union(x, y);
                }
                j = k;
            }
        }
        for (int i = 0; i < n; i++) {
            vector<pair<int, int> > c;
            for (int j = 0; j < m; j++) c.push_back({a[i][j], j});
            sort(c.begin(), c.end());
            int old = -1;
            for (int j = 0; j < m; ){
                int k = j;
                if (old != -1) {
                    int u = old;
                    int v = df.find_root(id(i, c[j].second));
                    adj[u].push_back(v);
                }
                old = df.find_root(id(i, c[j].second));
                while (k < m && c[k].first == c[j].first) k++;
                j = k;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        vector<pair<int, int> > c;
        for (int j = 0; j < n; j++) c.push_back({a[j][i], j});
        sort(c.begin(), c.end());
        int old = -1;
        for (int j = 0; j < n; ){
            int k = j;
            if (old != -1) {
                int u = old;
                int v = df.find_root(id(c[j].second, i));
                adj[u].push_back(v);
            }
            old = df.find_root(id(c[j].second, i));
            while (k < n && c[k].first == c[j].first) k++;
            j = k;
        }
    }
    int sz = n * m;
    for (int i = 0; i < sz; i++) adj[sz].push_back(i);
    DFS(sz);
    cout << dp[sz];
}

void solve() {
    int T;
    //cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
