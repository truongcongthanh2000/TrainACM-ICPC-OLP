#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 8e18;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
//const int Base = 311;9
const long double EPS = 1e-10;
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

const int maxN = 1e6 + 100;

struct DinicFlow { ///Base 0-th, The vertices are numbered from 0 to n - 1
    const int oo = 2e9; ///if flow > int, use long long
    int n, numEdge;
    vector <int> point, next, head, Dist, work;
    vector <int> flow, cap; ///if flow > int, use long long

    DinicFlow(int _n = 0) {
        n = _n; numEdge = 0;
        head.assign(n + 7, -1);
        work.assign(n + 7, -1);
        Dist.assign(n + 7, 0);
    }

    void add_Edge(int u, int v, int c1, int c2 = 0) {///if flow > int, use long long c1, c2
        ///u -> v: c1
        point.push_back(v); flow.push_back(0); cap.push_back(c1); next.push_back(head[u]); head[u] = numEdge++;
        ///v -> u: c2
        point.push_back(u); flow.push_back(0); cap.push_back(c2); next.push_back(head[v]); head[v] = numEdge++;
    }

    bool BFS(int s, int t) { ///check has path from s to t
        queue <int> Q;
        for (int i = 0; i <= n; i++) Dist[i] = -1;
        Dist[s] = 0;
        Q.push(s);
        while ((int)Q.size() != 0) {
            int u = Q.front(); Q.pop();
            for (int i = head[u]; i >= 0; i = next[i]) {
                int v = point[i];
                if (flow[i] < cap[i] && Dist[v] == -1) {
                    Dist[v] = Dist[u] + 1;
                    if (v == t) return true;
                    Q.push(v);
                }
            }
        }
        return false;
    }

    int DFS(int s, int t, int f) { ///if flow > int, use long long
        if (f == 0) ///Min F always >= 0 so if f = 0 break recursive
            return f;
        if (s == t)
            return f;
        for (int &i = work[s]; i >= 0; i = next[i]) { ///&i so important, don't use i = work[s] because it's maybe TLE
            int v = point[i];
            if (flow[i] < cap[i] && Dist[v] == Dist[s] + 1) {
                int D = DFS(v, t, min(f, cap[i] - flow[i]));
                if (D > 0) {
                    flow[i] += D;
                    flow[i ^ 1] -= D;
                    return D;
                }
            }
        }
        return 0;
    }

    int maxFlow(int s, int t) { ///if flow > int, use long long
        int Flow = 0;
        while (BFS(s, t)) {
            for (int i = 0; i <= n; i++) work[i] = head[i];
            while (true) {
                int d = DFS(s, t, oo);
                if (d == 0) break;
                Flow += d;
            }
        }
        return Flow;
    }

    int GetFlow(int idEdge) {
        return flow[idEdge];
    }
};

vector<pair<int, int> > adj[maxN];
void sol(){
    int n, m;
    cin >> n >> m;
    int t, s1, s2;
    cin >> t >> s1 >> s2;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, 2 * w});
        adj[v].push_back({u, 2 * w});
    }

    auto ok = [&](int x) {
        int s = 0, tt = n + 1;
        DinicFlow df(n + 2);
        df.add_Edge(t, tt, 2 * x);
        df.add_Edge(s, s1, x);
        df.add_Edge(s, s2, x);
        for (int u = 1; u <= n; u++) {
            for (auto [v, w] : adj[u]) {
                df.add_Edge(u, v, w);
            }
        }
        return df.maxFlow(s, t) == 2 * x;
    };
    int L = 0, R = 3e6, ans = 0;
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (ok(mid)) {
            ans = mid;
            L = mid + 1;
        }
        else R = mid - 1;
    }
    cout << ans;
}

void solve() {
    clock_t begin = clock();
    int T;
//    cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        //cout << "Test " << TestCase << ": ";
        sol();
    }
    clock_t end = clock();
    cerr << "Time: " << fixed << setprecision(10) << (double)(end - begin) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
