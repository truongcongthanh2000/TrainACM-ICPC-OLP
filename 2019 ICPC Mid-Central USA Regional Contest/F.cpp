#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "OB"
#define OUT "OB"

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

const int maxN = 5e5 + 10;

typedef pair<int, int> i2;
typedef pair<long long, int> i2_LL;
typedef pair<long long, i2> i3;
int n, m, k;
vector<i2> adj[maxN];
long long dist[10][maxN];

void Dijkstra(int s, long long dist[maxN]) {
    for (int i = 0; i <= n; i++) dist[i] = INF_LL;
    dist[s] = 0;
    priority_queue<i2_LL, vector<i2_LL>, greater<i2_LL> > Q;
    Q.push({0, s});
    while ((int)Q.size() != 0) {
        i2 A = Q.top(); Q.pop();
        long long du = A.first;
        int u = A.second;
        if (dist[u] != du) continue;
        for (auto it : adj[u]) {
            int v = it.first;
            int w = it.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                Q.push({dist[v], v});
            }
        }
    }
}
int p[10], id[10];
void sol() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    for (int i = 1; i <= 7; i++) cin >> p[i];
    p[0] = 1;
    sort(p, p + 8);
    int m = unique(p, p + 8) - p;
    for (int i = 0; i < m; i++) {
        Dijkstra(p[i], dist[i]);
        id[i] = i;
    }
    long long res = INF_LL;
    do {
        long long cost = 0;
        for (int i = 1; i < m; i++) cost += dist[id[i - 1]][p[id[i]]];
        res = min(res, cost);
    }
    while (next_permutation(id + 1, id + m));
    if (res == INF_LL) cout << -1;
    else cout << res << '\n';
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
