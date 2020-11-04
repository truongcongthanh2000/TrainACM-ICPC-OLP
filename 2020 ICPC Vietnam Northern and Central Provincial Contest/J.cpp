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
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e5 + 1000;

typedef pair<int, int> i2;
vector<i2> adj[maxN];
typedef pair<long long, int> i2LL;
long long d[maxN];
long long path[20][maxN];

int used[maxN];
#define MF Maxflow
#define flow_t int
const flow_t foo = (flow_t) 1e9;
namespace Maxflow {
    const int maxv = 1e5 + 5;
    const int maxe = 2e6 + 5;
    int n, s, t, E;
    int adj[maxe], nxt[maxe], lst[maxv], ptr[maxv], lev[maxv], que[maxv];
    flow_t flw[maxe], cap[maxe];
    void init(int nn, int ss, int tt) {
        n = nn, s = ss, t = tt, E = 0;
        fill_n(lst, n, -1);
    }
    void add(int u, int v, flow_t c1, flow_t c2 = 0) {
        adj[E] = v, flw[E] = 0, cap[E] = c1, nxt[E] = lst[u], lst[u] = E++;
        adj[E] = u, flw[E] = 0, cap[E] = c2, nxt[E] = lst[v], lst[v] = E++;
    }
    int bfs() {
        fill_n(lev, n, 0), lev[s] = 1;
        int qsize = 0;
        que[qsize++] = s;
        for (int i = 0; i < qsize; i++) {
            for (int u = que[i], e = lst[u]; ~e; e = nxt[e]) {
                int v = adj[e];
                if (flw[e] < cap[e] && !lev[v]) {
                    lev[v] = lev[u] + 1;
                    que[qsize++] = v;
                }
            }
        }
        return lev[t];
    }
    flow_t dfs(int u, flow_t bot) {
        if (u == t) return bot;
        for (int& e = ptr[u]; ~e; e = nxt[e]) {
            int v = adj[e];
            flow_t delta = 0;
            if (lev[v] == lev[u] + 1 && flw[e] < cap[e] && (delta = dfs(v, min(bot, cap[e] - flw[e]))) > 0) {
                flw[e] += delta; flw[e ^ 1] -= delta;
                return delta;
            }
        }
        return 0;
    }
    flow_t maxflow(int ss = -1, int tt = -1) {
        if (~ss) s = ss;
        if (~tt) t = tt;
        fill_n(flw, E, 0);
        flow_t total = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++) ptr[i] = lst[i];
            for (flow_t delta = dfs(s, foo); delta > 0; delta = dfs(s, foo)) total += delta;
        }
        return total;
    }
}
int x[20], cap[20];
long long dp[maxN];

void sol(){
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    auto Dijkstra = [&](int s) {
        priority_queue<i2LL, vector<i2LL>, greater<i2LL> > Q;
        for (int i = 1; i <= n; i++) d[i] = INF_LL;
        d[s] = 0;
        Q.push({0, s});
        while ((int)Q.size() != 0) {
            i2LL A = Q.top(); Q.pop();
            long long du = A.first;
            int u = A.second;
            if (d[u] != du) continue;
            for (auto [v, w] : adj[u]) {
                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    Q.push({d[v], v});
                }
            }
        }
    };
    for (int i = 0; i < k; i++) {
        cin >> x[i] >> cap[i];
        Dijkstra(x[i]);
        for (int j = 1; j <= n; j++) path[i][j] = d[j];
    };
    auto check = [&](long long cost) {
        memset(dp, 0, sizeof dp);
        for (int i = 1; i <= n; i++) {
            int mask = 0;
            for (int j = 0; j < k; j++) {
                if (path[j][i] <= cost) {
                    mask |= 1 << j;
                }
            }
            dp[mask]++;
        }
        for (int i = 0; i < k; ++i)
            for (int j = 1; j < (1 << k); ++j) {
                int bit = (j >> i) & 1;
                if (bit) {
                    dp[j] += dp[j ^ (1 << i)];
                }
            }
        for (int j = 0; j < (1 << k); ++j) {
            long long need = 0;
            for (int i = 0; i < k; ++i) {
                int bit = (j >> i) & 1;
                if (bit) {
                    need += cap[i];
                }
            }
            if (need < dp[j])
                return false;
        }
        return true;
    };
    long long L = 0;
    long long R = 1e16;
    long long res = R;
    while (L <= R) {
        long long mid = (L + R) >> 1;
        if (check(mid)) {
            res = mid;
            R = mid - 1;
        }
        else L = mid + 1;
    }
    cout << res;
}

void solve() {
    int T;
//    cin >> T;
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
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
