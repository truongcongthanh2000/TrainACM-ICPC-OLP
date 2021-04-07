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

const int maxN = 5e5 + 1000;

int p[maxN];
int find_root(int u) {
    return p[u] < 0 ? u : p[u] = find_root(p[u]);
}
bool Union(int u, int v) {
    int x = find_root(u);
    int y = find_root(v);
    if (x == y) return false;
    if (p[x] > p[y]) swap(x, y);
    p[x] += p[y];
    p[y] = x;
    return true;
}

struct edges {
    int u, v, w, id;
    edges(){};
    bool operator < (const edges &A) {
        return w < A.w;
    }
};

edges e[maxN];
int ok[maxN];

void sol() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) p[i] = -1;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        Union(e[i].u, e[i].v);
        ok[i] = 0;
        e[i].id = i;
    }
    int numCom = 0;
    for (int i = 1; i <= n; i++) numCom += p[i] < 0;
    if (numCom > 1) {
        cout << -1 << '\n';
        return;
    }
    sort(e + 1, e + 1 + m);
    for (int i = 1; i <= n; i++) p[i] = -1;
    vector<int> result;
    for (int i = 1; i <= m; ) {
        int j = i;
        while (j <= m && e[i].w == e[j].w) j++;
        vector<edges> goodEdges;
        for (int k = i; k < j; k++) {
            int u = e[k].u;
            int v = e[k].v;
            if (find_root(u) != find_root(v)) {
                goodEdges.push_back(e[k]);
            }
        }
        for (edges e : goodEdges) {
            int u = e.u;
            int v = e.v;
            if (find_root(u) == find_root(v)) {
                result.push_back(e.id);
            }
            Union(u, v);
        }
        i = j;
    }
    cout << (int)result.size() << ' ';
    for (int x : result) cout << x << ' ';
    cout << '\n';
}

void solve() {
    int T;
    cin >> T;
    //T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        //cout << "Test " << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
}
int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
