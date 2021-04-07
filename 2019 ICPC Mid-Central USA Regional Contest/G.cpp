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
const double EPS = 1e-7;
const int BLOCK = 100;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

typedef pair<int, int> i2;
typedef pair<int, i2> i3;
vector<i2> adj[maxN];
vector<int> id[maxN];
int a[maxN];
int rd[maxN];
int dist[1234][150];

void sol() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    for (int i = 1; i <= k; i++) {
        int c, d;
        cin >> c >> d;
        id[c].push_back(d);
    }

    int limits = 1000;
    int res = INF;
    bool ok = false;
    for (int step = 0; step < limits; step++) {
        for (int i = 1; i <= n; i++) rd[i] = rng() % 7;
        for (int i = 1; i <= n; i++) {
            for (int mask = 0; mask < (1 << 7); mask++) dist[i][mask] = INF;
        }
        priority_queue<i3, vector<i3>, greater<i3> > Q;
        Q.push({0, {1, 0}});
        dist[1][0] = 0;
        while ((int)Q.size() != 0) {
            i3 A = Q.top(); Q.pop();
            int du = A.first;
            int u = A.second.first;
            int mask = A.second.second;
            if (du != dist[u][mask]) continue;
            for (int d : id[u]) mask |= 1 << rd[d];
            if (mask == (1 << 7) - 1) {
                ok = true;
                res = min(res, du);
                break;
            }
            for (auto [v, w] : adj[u]) {
                if (dist[v][mask] > du + w) {
                    dist[v][mask] = du + w;
                    Q.push({dist[v][mask], {v, mask}});
                }
            }
        }
    }
    if (ok == false) cout << -1;
    else cout << res;
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
