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
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

typedef pair<int, int> i2;

int log_arr[maxN];
vector<int> divisors[maxN];
int depth[maxN];
vector<i2> adj[maxN];

void precalc() {
    int lg = 0, pw = 1;
    for (int i = 1; i < maxN; i++) {
        log_arr[i] = lg - 1;
        if (pw == i) {
            pw *= 2;
            log_arr[i] = lg++;
        }
    }
    int limits = 5e5;
    for (int i = 1; i <= limits; i++) {
        for (int j = i; j <= limits; j += i) {
            divisors[j].push_back(i);
        }
    }
}

int b[maxN][20];
long long dist[maxN];
int lg(int n) {
    int res = 0;
    while ((1 << (res + 1)) <= n) res++;
    return res;
}
void DFS(int u, int pa) {
    for (int i = 0; i <= 18; i++) {
        int v = b[u][i];
        b[u][i + 1] = b[v][i];
    }
    for (auto [v, w] : adj[u]) {
        if (v == pa) continue;
        depth[v] = depth[u] + 1;
        dist[v] = dist[u] + w;
        b[v][0] = u;
        DFS(v, u);
    }
}

int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int k = depth[u] - depth[v];
    for (int i = 18; i >= 0; i--) {
        if (k >= (1 << i)) {
            k -= (1 << i);
            u = b[u][i];
        }
    }
    if (u == v) return u;
    int res = 0;
    for (int i = 18; i >= 0; i--) {
        if (b[u][i] != b[v][i]) {
            u = b[u][i];
            v = b[v][i];
        }
        else res = b[u][i];
    }
    assert(b[u][0] == b[v][0]);
    return res = b[u][0];
}

long long getDist(int u, int v) {
    int root = LCA(u, v);
    return dist[u] + dist[v] - dist[root] * 2;
}

int label[maxN];
int used[maxN];
vector<int> vertice[maxN];
void sol(){
    int n, time = 0;
    while (cin >> n) {
        if (n == 0) break;
        time++;
        vector<int> div;
        for (int i = 1; i <= n; i++) {
            cin >> label[i];
            for (int x : divisors[label[i]]) {
                vertice[x].push_back(i);
                if (used[x] != time) {
                    div.push_back(x);
                    used[x] = time;
                }
            }
            adj[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        DFS(1, 0);
        long long res = 0;
        for (int gcd : div) {
            int root = vertice[gcd][0];
            long long ans_dist = 0;
            int left = root;
            for (int u : vertice[gcd]) {
                long long dist = getDist(root, u);
                if (dist > ans_dist) {
                    left = u;
                    ans_dist = dist;
                }
            }
            for (int u : vertice[gcd]) {
                long long dist = getDist(left, u);
                ans_dist = max(ans_dist, dist);
            }
            res = max(res, ans_dist * gcd);
            vertice[gcd].clear();
        }
        cout << res << '\n';
    }
}

void solve() {
    precalc();
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
