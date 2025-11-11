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

const int maxN = 2e6 + 1000;

typedef pair<int, int> i2;
int a[maxN];
int tim[maxN];
int ans[maxN];

vector<int> adj[maxN];
bool DFS(int u, int c) {
    if (ans[u]) return ans[u] == c;
    ans[u] = c;
    for (int v : adj[u]) {
        if (!DFS(v, 3 - c)) return false;
    }
    return true;
}
int T = 0;

bool color(int u) {
    T++;
    for (int v : adj[u]) {
        if (ans[v]) tim[ans[v]] = T;
    }
    ans[u] = 1;
    while (tim[ans[u]] == T) ans[u]++;
    return ans[u] <= 3;
}
bool visit(int u) {
    while ((int)adj[u].size() > 0 && ans[adj[u].back()]) adj[u].pop_back();
    if ((int)adj[u].size() == 0) return true;
    int v = adj[u].back();
    color(v);
    visit(u);
    visit(v);
    return true;
}
void sol() {
    int n;
    cin >> n;
    int res = 1;
    int top = 0;
    bool special = true;
    for (int i = 1; i <= n; i++) {
        int f, h;
        cin >> f >> h;
        while (top > 0 && f >= a[top]) {
            int u = i;
            int v = tim[top];
            adj[u].push_back(v);
            adj[v].push_back(u);
            special = false;
            f -= a[top];
            top--;
        }
        if (top > 0 && f > 0 && f < a[top]) {
            int u = i;
            int v = tim[top];
            adj[u].push_back(v);
            adj[v].push_back(u);
            special = false;
            a[top] -= f;
        }
        if (h > 0) {
            top++;
            tim[top] = i;
            a[top] = h;
        }
    }
    for (int i = 1; i <= n; i++) sort(adj[i].begin(), adj[i].end());
    if (special) {
        cout << 1 << '\n';
        for (int i = 1; i <= n; i++) cout << 1 << ' ';
        return;
    }
    bool ok = true;
    for (int i = 1; i <= n; i++) {
        if (ans[i] == 0) ok &= DFS(i, 1);
    }
    if (ok) {
        cout << 2 << '\n';
        for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
        return;
    }
    memset(tim, 0, sizeof(tim));
    memset(ans, 0, sizeof(ans));
    for (int i = 1; i <= n; i++) {
        if (ans[i] == 0) {
            ans[i] = 1;
            visit(i);
        }
    }
    cout << 3 << '\n';
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
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
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
