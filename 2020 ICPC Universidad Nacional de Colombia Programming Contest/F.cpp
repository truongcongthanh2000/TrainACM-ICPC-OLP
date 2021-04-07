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

const int maxN = 2e4 + 100;

typedef pair<int, int> i2;
typedef pair<long long, i2> i3;
int n, m, k;
int A, B;
vector<i2> adj[maxN], adj_reverse[maxN];
long long dist[4][maxN][12];

void Dijkstra(int s, vector<i2> adj[maxN], long long dist[maxN][12]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) dist[i][j] = INF_LL;
    }
    for (int i = 0; i <= k; i++) dist[s][i] = 0;
    priority_queue<i3, vector<i3>, greater<i3> > Q;
    Q.push({0, {s, 0}});
    while ((int)Q.size() != 0) {
        i3 A = Q.top(); Q.pop();
        long long du = A.first;
        int u = A.second.first;
        int x = A.second.second;
        if (dist[u][x] != du) continue;
        for (auto it : adj[u]) {
            int v = it.first;
            int w = it.second;
            if (dist[v][x] > dist[u][x] + w) {
                dist[v][x] = dist[u][x] + w;
                Q.push({dist[v][x], {v, x}});
            }
            if (x < k && dist[v][x + 1] > dist[u][x]) {
                dist[v][x + 1] = dist[u][x];
                Q.push({dist[v][x + 1], {v, x + 1}});
            }
        }
    }
}

void sol() {
    cin >> n >> m;
    cin >> A >> B >> k;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj_reverse[v].push_back({u, w});
    }
    Dijkstra(A, adj, dist[0]);
    Dijkstra(A, adj_reverse, dist[1]);
    Dijkstra(B, adj, dist[2]);
    Dijkstra(B, adj_reverse, dist[3]);
    long long res = INF_LL;
    //cout << dist[1][2][1] << '\n';
    int res_x = -1;
    for (int x = 0; x < n; x++) {
        if (x == A || x == B) continue;
        long long cost = INF_LL;
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j + i <= k; j++) {
                for (int u = 0; u <= k; u++) {
                    for (int v = 0; u + v <= k; v++) {
                        cost = min(cost, dist[0][x][i] + dist[1][x][j] + dist[2][x][u] + dist[3][x][v]);
                    }
                }
            }
        }
        if (cost < res) {
            res = cost;
            res_x = x;
        }
    }
    if (res_x == -1) cout << ">:(";
    else cout << res_x << " " << res << '\n';
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
 
