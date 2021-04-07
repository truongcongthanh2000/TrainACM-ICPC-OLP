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

const int maxN = 5e5 + 100;

typedef pair<int, int> i2;
vector<i2> adj[maxN];

long long res[maxN], res2[maxN];
int numNode[maxN], t[maxN];
int n;
long long st[maxN];

void DFS(int u, int pa, long long d) {
    res[1] += d;
    res2[1] += d * t[u];
    numNode[u] = 1;
    st[u] = t[u];
    for (auto [v, w] : adj[u]) {
        if (v != pa) {
            DFS(v, u, d + w);
            st[u] += st[v];
            numNode[u] += numNode[v];
        }
    }
}

void DFS2(int u, int pa) {
    for (auto [v, w] : adj[u]) {
        if (v != pa) {
            res[v] = res[u] + (n - numNode[v]) * w - numNode[v] * w;
            res2[v] = res2[u] + (st[1] - st[v]) * w - st[v] * w;
            DFS2(v, u);
        }
    }
}
void sol() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> t[i];
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    DFS(1, 0, 0);
    DFS2(1, 0);
    for (int i = 1; i <= n; i++) cout << res[i] * t[i] + res2[i] << '\n';
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
