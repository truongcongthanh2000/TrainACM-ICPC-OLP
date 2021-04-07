#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e2 + 10;

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

    bool Union(int u, int v) {
        int x = find_root(u);
        int y = find_root(v);
        if (x == y) return false;
        if (p[x] > p[y]) swap(x, y); ///small Set point to big Set, p[x] > p[y] so |p[x]| < |p[y]|
        p[x] += p[y];
        p[y] = x;
        return true;
    }

    bool sameSet(int u, int v) {
        return find_root(u) == find_root(v);
    }

    int numSet() {
        int res = 0;
        for (int i = 1; i <= n; i++) res += p[i] < 0;
        return res;
    }
};

void sol() {
    int n;
    cin >> n;
    DisjointSetUnion df(n);
    map<int, vector<int> > M;
    for (int i = 1; i <= n; i++) {
        int m;
        cin >> m;
        for (int j = 1; j <= m ; j++) {
            int d;
            cin >> d;
            M[d].push_back(i);
        }
    }
    vector<array<int, 3> > res;
    for (auto it : M) {
        int d = it.first;
        vector<int> adj = it.second;
        for (int i = 1; i < (int)adj.size(); i++) {
            int u = adj[i - 1];
            int v = adj[i];
            if (df.Union(u, v)) {
                res.push_back({u, v, d});
            }
        }
    }
    if (df.numSet() > 1) cout << "impossible";
    else {
        for (auto it : res) {
            cout << it[0] << " " << it[1] << " " << it[2] << '\n';
        }
    }
}

void solve() {
    int T;
    ///cin >> T;
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
