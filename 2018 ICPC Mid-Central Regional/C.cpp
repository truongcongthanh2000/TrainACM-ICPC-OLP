#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "OB"
#define OUT "OB"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-7;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 3e5 + 10;

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
                if (delta != 0) {
                    flow[i] += delta;
                    flow[i ^ 1] -= delta;
                    return delta;
                }
            }
        }
        return 0;
    }

    long long maxFlow(int s, int t) {
        long long res = 0;
        while (BFS(s, t)) {
            for (int i = 0; i <= n; i++) work[i] = head[i];
            while (true) {
                int delta = DFS(s, t, INF);
                if (delta == 0) break;
                res += delta;
            }
        }
        return res;
    }
};

string mp[101];
int p[101][101];
void sol() {
    int n, m, c;
    cin >> m >> n >> c;
    int s = 0, t = n * m * 2;
    DinicFlow df(t);
    auto in = [&](int x, int y) {
        return x * m + y + n * m;
    };

    auto out = [&](int x, int y) {
        return x * m + y;
    };
    for (int i = 0; i < n; i++) {
        cin >> mp[i];
        for (int j = 0; j < m; j++) {
            if (mp[i][j] == 'B') s = out(i, j);
        }
    }
    vector<int> value(c);
    for (int i = 0; i < c; i++) cin >> value[i];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mp[i][j] == '.') {
                df.addEdge(in(i, j), out(i, j), INF);
            }
            if (mp[i][j] >= 'a' && mp[i][j] <= 'z') {
                df.addEdge(in(i, j), out(i, j), value[mp[i][j] - 'a']);
            }
            for (int h = 0; h < 4; h++) {
                int x = i + dx[h];
                int y = j + dy[h];
                if (x >= 0 && x < n && y >= 0 && y < m) {
                    df.addEdge(out(i, j), in(x, y), INF);
                }
                else {
                    df.addEdge(out(i, j), t, INF);
                }
            }
        }
    }
    cerr << "OK" << '\n';
    long long res = df.maxFlow(s, t);
    if (res >= INF) cout << -1;
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
