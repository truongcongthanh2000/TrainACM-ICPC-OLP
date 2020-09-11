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

const int maxN = 2e5 + 10;

typedef pair<int, int> i2;
typedef pair<long long, int> i2LL;
typedef pair<long long, i2> i3;

int n, m;
vector<i2> adj[maxN];
int numPath[maxN];
long long dist[2][maxN];
int numFlight[2][maxN];

bool Bigger(int a, int b) {
    return a > b;
}

bool Weak(int a, int b) {
    return a < b;
}
void Dijkstra(int S, bool compare(int, int), int baseNumFlight, long long dist[maxN], int numFlight[maxN]) {
    priority_queue<i3, vector<i3>, greater<i3> > Q;
    for (int i = 1; i <= n; i++) {
        dist[i] = INF_LL;
        numPath[i] = 0;
        numFlight[i] = baseNumFlight;
    }
    dist[S] = 0;
    numPath[S] = 1;
    numFlight[S] = 0;
    Q.push({0, {S, 0}});
    while ((int)Q.size() != 0) {
        i3 A = Q.top(); Q.pop();
        long long du = A.first;
        int u = A.second.first;
        int nFlight = A.second.second;
        if (du != dist[u]) continue;
        if (numFlight[u] != nFlight) continue;
        for (auto it : adj[u]) {
            int v = it.first;
            int w = it.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                numPath[v] = numPath[u];
                numFlight[v] = numFlight[u] + 1;
                Q.push({dist[v], {v, numFlight[v]}});
            }
            else {
                if (dist[v] == dist[u] + w) {
                    numPath[v] = (numPath[u] + numPath[v]) % MOD;
                    if (compare(nFlight + 1, numFlight[v])) {
                        numFlight[v] = nFlight + 1;
                        Q.push({dist[v], {v, numFlight[v]}});
                    }
                }
            }
        }
    }
}

void sol() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    Dijkstra(1, Weak, INF, dist[0], numFlight[0]);
    Dijkstra(n, Weak, INF, dist[1], numFlight[1]);
    vector<int> res;
    for (int i = 1; i <= n; i++) {
        if (dist[0][i] + dist[1][i] != d || numFlight[0][i] + numFlight[1][i] != numF) res.push_back(i);
    }
    cout << (int)res.size() << '\n';
    for (int x : res) cout << x << ' ';
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
