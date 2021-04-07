#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
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
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e3 + 10;

struct MaxBipartiteMatching { ///base 1th; X -> Y
    int n, m;
    vector <int> link, match, stk, Used;
    bool Found;
    vector <vector<int> > adj;
    MaxBipartiteMatching(){};
    MaxBipartiteMatching(int _n, int _m) {
        n = _n; ///Size(X)
        m = _m; ///Size(Y)
        link.assign(n + 7, 0); ///X
        match.assign(m + 7, 0); ///match[y] = x, if have x -> y in MaxBipartiteMatching or 0 if not
        Used.assign(m + 7, 0);
        stk.clear();
        adj.resize(n + 7);
    }

    void addEdge(int u, int v) { ///u in X and v in Y
        adj[u].push_back(v);
    }

    void DFS(int u) {
        for (int v : adj[u]) {
            if (Used[v] == 0) {
                Used[v] = 1;
                stk.push_back(v);
                if (match[v] == 0) Found = true;
                else DFS(match[v]);
                if (Found) {
                    match[v] = u;
                    return;
                }
            }
        }
    }

    int getCost() { ///get size MaxBipartiteMatching
        int Nlink = n;
        for (int i = 1; i <= n; i++) link[i] = i;
        for (int i = 1; i <= m; i++) match[i] = 0;
        int old;
        do {
            old = Nlink;
            for (int x : stk) Used[x] = 0;
            stk.clear();
            for (int i = Nlink; i >= 1; i--) {
                Found = false;
                DFS(link[i]);
                if (Found) {
                    link[i] = link[Nlink--];
                }
            }
        }
        while (old != Nlink);
        return n - old;
    }

    int getX(int y) { ///match[y] = x, if have x -> y in MaxBipartiteMatching or 0 if not
        return match[y];
    }
};

int res[maxN][maxN];
int c[maxN][maxN], h[maxN][maxN];
bool solve(int row, int n) {
    MaxBipartiteMatching df(n, n);
    for (int col = 1; col <= n; col++) {
        for (int val = 1; val <= n; val++) {
            if (c[col][val] == 0) df.addEdge(val, col);
        }
    }
    int resGhep = df.getCost();
    for (int col = 1; col <= n; col++) {
        int val = df.getX(col);
        res[row][col] = val;
        c[col][val]++;
    }
    return resGhep == n;
}
void sol() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            int w;
            cin >> w;
            res[i][j] = w;
            if (h[i][w]++ || c[j][w]++) {
                cout << "no";
                return;
            }
        }
    }
    bool Ok = true;
    for (int i = k + 1; i <= n; i++) {
        bool cost = solve(i, n);
        Ok &= cost;
        //cerr << i << " " << cost << '\n';
    }
    assert(Ok == true);
    cout << "yes" << '\n';
    for (int i = 1; i <= n; i++) {
        cout << res[i][1];
        for (int j = 2; j <= n; j++) cout << " " << res[i][j];
        if (i != n) cout << '\n';
    }
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
