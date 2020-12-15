#include <bits/stdc++.h>

using namespace std;

void doc() {
    #ifdef THEMIS
        freopen("solve.inp", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 100;
const long long INF = 1e18 + 100;

vector<pair<int, int> > adj[maxN];
long long dist[4][maxN];
int n, m;
void sol() {
    int s1, t1, s2, t2;
    cin >> s1 >> t1 >> s2 >> t2;
    for (int i = 1; i <= n; i++) adj[i].clear();
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    auto dijkstra = [&](int s, long long dist[maxN]) {
        for (int i = 1; i <= n; i++) dist[i] = INF;
        typedef pair<long long, int> i2;
        priority_queue <i2, vector<i2>, greater<i2> > Q;
        dist[s] = 0;
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
    };
    dijkstra(s1, dist[0]);
    dijkstra(t1, dist[1]);
    dijkstra(s2, dist[2]);
    dijkstra(t2, dist[3]);
    //cout << dist[0][t1] << " " << dist[2][t2] << '\n';
    int ans = 0;
    for (int u = 1; u <= n; u++) {
        if (dist[0][u] == dist[2][u] && dist[0][u] + dist[1][u] == dist[0][t1] && dist[2][u] + dist[3][u] == dist[2][t2]) {
            for (auto it : adj[u]) {
                int v = it.first;
                int w = it.second;
                if (dist[0][u] < dist[0][v] && dist[2][u] < dist[2][v] && dist[0][u] + dist[1][v] + w == dist[0][t1] && dist[2][u] + dist[3][v] + w == dist[2][t2]) {
                    cout << -1 << '\n';
                    return;
                }
            }
            ans++;
        }
        else {
            for (auto it : adj[u]) {
                int v = it.first;
                int w = it.second;
                if (dist[0][u] > dist[0][v]) continue;
                if (dist[0][u] + dist[1][v] + w == dist[0][t1] && dist[2][v] + dist[3][u] + w == dist[2][t2]) {
                    long long a = dist[0][u];
                    long long b = dist[0][v];
                    long long c = dist[2][v];
                    long long d = dist[2][u];
                    //cout << a << " " << b << " " << c << " " << d << '\n';
                    if (c < d && max(a, c) < min(b, d)) ans++;
                }
            }
            if (u == t1 && dist[2][u] + dist[3][u] == dist[2][t2] && dist[2][t1] >= dist[0][t1]) ans++;
            else {
                if (u == t2 && dist[0][u] + dist[1][u] == dist[0][t1] && dist[0][t2] >= dist[2][t2]) ans++;
            }
        }
    }
    cout << ans << '\n';
}

void solve() {
    int T;
    //T = 1;
    //cin >> T;
    T = 1e9;
    while (T--) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        sol();
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
