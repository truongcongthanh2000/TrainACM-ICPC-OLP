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

vector<int> adj[maxN];

int numNode[maxN];
int parent[maxN];
int L[maxN], R[maxN], order = -1;
void DFS(int u, int pa) {
    L[u] = ++order;
    numNode[u] = 1;
    for (int v : adj[u]) {
        if (v != pa) {
            parent[v] = u;
            DFS(v, u);
            numNode[u] += numNode[v];
        }
    }
    R[u] = order;
}

int chainHead[maxN], nChain = 0, chainInd[maxN], Pos[maxN], Base = 0;
void HLD(int u, int pa) {
    if (chainHead[nChain] == -1) {
        chainHead[nChain] = u;
    }
    chainInd[u] = nChain;
    Pos[u] = Base++;

    int nxt = -1;
    for (int v : adj[u]) {
        if (v != pa) {
            if (nxt == -1 || numNode[v] > numNode[nxt]) nxt = v;
        }
    }
    if (nxt != -1) HLD(nxt, u);

    for (int v : adj[u]) {
        if (v != nxt && v != pa) {
            nChain++;
            HLD(v, u);
        }
    }
}

long long IT[maxN * 4];
int lazy[maxN * 4];

void push_down(int i, int L, int R) {
    if (lazy[i] == 0) return;
    IT[i] += 1LL * (R - L + 1) * lazy[i];
    if (L != R) {
        lazy[i << 1] += lazy[i];
        lazy[i << 1 | 1] += lazy[i];
    }
    lazy[i] = 0;
}
void update(int i, int L, int R, int u, int v, int val) {
    push_down(i, L, R);
    if (L > v || R < u) return;
    if (L >= u && R <= v) {
        lazy[i] += val;
        push_down(i, L, R);
        return;
    }
    int mid = (L + R) >> 1;
    update(i << 1, L, mid, u, v, val);
    update(i << 1 | 1, mid + 1, R, u, v, val);
    IT[i] = IT[i << 1] + IT[i << 1 | 1];
}

long long get(int i, int L, int R, int u, int v) {
    push_down(i, L, R);
    if (L > v || R < u) return 0;
    if (L >= u && R <= v) return IT[i];
    int mid = (L + R) >> 1;
    long long left = get(i << 1, L, mid, u, v);
    long long right = get(i << 1 | 1, mid + 1, R, u, v);
    return left + right;
}

void sol() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i <= n; i++) chainHead[i] = -1;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }

    DFS(0, -1);

    HLD(0, -1);

    auto up = [&](int u, int a, int val) {
        int uchain = chainInd[u], achain = chainInd[a];
        int ans = 0;
        while (true) {
            if (uchain == achain) {
                update(1, 0, n, Pos[a], Pos[u], val);
                break;
            }

            update(1, 0, n, Pos[chainHead[uchain]], Pos[u], val);
            u = parent[chainHead[uchain]];
            uchain = chainInd[u];
        }
    };

    for (int i = 1; i <= m; i++) {
        int t, e, v;
        cin >> t >> e >> v;
        if (t == 1) {
            up(e, e, v);
        }
        else {
            up(e, 0, v);
        }
    }

    vector<long long> s(n + 1, 0);
    for (int i = 0; i <= n; i++) {
        int id = L[i];
        s[id] = get(1, 0, n, Pos[i], Pos[i]);
    }
    for (int i = 1; i <= n; i++) s[i] += s[i - 1];

    for (int i = 0; i < q; i++) {
        int t, e;
        cin >> t >> e;
        if (t == 1) {
            long long ans = s[L[e]];
            if (L[e]) ans -= s[L[e] - 1];
            cout << ans << '\n';
        }
        else {
            long long ans = s[R[e]];
            if (L[e]) ans -= s[L[e] - 1];
            cout << ans << '\n';
        }
    }
}

void solve() {
    clock_t begin = clock();
    int T;
    //cin >> T;
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
