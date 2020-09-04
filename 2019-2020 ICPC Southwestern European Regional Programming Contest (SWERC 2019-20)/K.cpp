#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e5 + 10;

vector<int> adj[maxN], adj_reverse[maxN];
set<int> canChoose[maxN];
void DFS(int u, int root) {
    if (canChoose[u].find(root) != canChoose[u].end()) return;
    if (canChoose[u].size() >= 2) return;
    canChoose[u].insert(root);
    ///cout << u << " " << root << '\n';
    for (int v : adj_reverse[u]) {
        DFS(v, root);
    }
}

void sol() {
    int n, m, s;
    cin >> n >> m >> s;
    vector<int> special;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (v == s) special.push_back(u);
        if (v != s) adj[u].push_back(v);
        if (v != s) adj_reverse[v].push_back(u);
    }
    for (int v : special) {
        DFS(v, v);
    }
    vector<int> res;
    for (int v : special) {
        if ((int)canChoose[v].size() == 1) {
            res.push_back(v);
        }
    }
    cout << (int)res.size() << '\n';
    for (int x : res) cout << x << '\n';
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
