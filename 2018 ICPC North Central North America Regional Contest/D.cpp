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
const int dx[6] = {0, 0, 1, -1, 1, -1};
const int dy[6] = {1, -1, 0, 0, 1, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e3 + 10;

struct DinicFlow {
    int n;
    int numEdge = 0;
    vector<int> head, work, dist;
    vector<int> points, next;
    vector<int> flow, cap;

    DinicFlow(int _n = 0) {
        numEdge = 0;
        n = _n;
        head.assign(n + 7, -1);
        dist.assign(n + 7, -1);
        work.assign(n + 7, -1);
    }
    void addEdge(int u, int v, int c1, int c2 = 0) {
        ///u -> v
        points.push_back(v); flow.push_back(0); cap.push_back(c1); next.push_back(head[u]); head[u] = numEdge++;
        ///v -> u
        points.push_back(u); flow.push_back(0); cap.push_back(c2); next.push_back(head[v]); head[v] = numEdge++;
    }

    bool BFS(int s, int t) {
        for (int i = 0; i <= n; i++) dist[i] = -1;
        dist[s] = 0;
        queue<int> Q;
        Q.push(s);
        while ((int)Q.size()) {
            int u = Q.front(); Q.pop();
            for (int i = head[u]; i >= 0; i = next[i]) {
                int v = points[i];
                if (flow[i] < cap[i] && dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    if (v == t) return true;
                    Q.push(v);
                }
            }
        }
        return false;
    }

    int DFS(int s, int t, int f) {
        if (s == t) return f;
        for (int &i = work[s]; i >= 0; i = next[i]) {
            int v = points[i];
            if (flow[i] < cap[i] && dist[v] == dist[s] + 1) {
                int delta = DFS(v, t, min(f, cap[i] - flow[i]));
                if (delta != INF) {
                    flow[i] += delta;
                    flow[i ^ 1] -= delta;
                    return delta;
                }
            }
        }
        return INF;
    }

    long long maxFlow(int s, int t) {
        long long res = 0;
        while (BFS(s, t)) {
            for (int i = 0; i <= n; i++) work[i] = head[i];
            while (true) {
                int delta = DFS(s, t, INF);
                if (delta == INF) break;
                res += delta;
            }
        }
        return res;
    }
};

int e[20][20][20];
int c[20][20];
void sol() {
    int k, n, m;
    cin >> k >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, d, w;
        cin >> u >> v >> d >> w;
        e[u][v][d] += w;
    }
    for (int i = 1; i <= k * n; i++) {
        int u, d, w;
        cin >> u >> d >> w;
        c[u][d] += w;
    }
    for (int d = 1; d <= n; d++) {
        int s = 0, t = 2 * k + 1;
        DinicFlow df(t);
        for (int i = 1; i <= k; i++) {
            int cap = 0;
            for (int k = 1; k <= d; k++) cap += c[i][k];
            for (int j = 1; j <= k; j++) {
                cap += e[j][i][d - 1];
            }
            df.addEdge(s, i, cap);
        }
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= k; j++) {
                if (e[i][j][d]) df.addEdge(i, j + k, e[i][j][d]);
            }
        }
        int cost = 0;
        for (int i = 1; i <= k; i++) {
            int cap = 0;
            for (int j = 1; j <= k; j++) cap += e[j][i][d];
            df.addEdge(i + k, t, cap);
            cost += cap;
        }
        int flow = df.maxFlow(s, t);
        if (flow != cost) {
            cout << "suboptimal";
            return;
        }
    }
    cout << "optimal";
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
