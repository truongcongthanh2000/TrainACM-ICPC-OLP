#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "OB"
#define OUT "OB"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-7;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

int Used[maxN];
int suf[maxN], suf2[maxN];
vector<int> adj[maxN];
int ans[maxN], num[maxN];

void DFS(int u) {
    Used[u] = 1;
    for (int v : adj[u]) {
        if (Used[v] == 0) DFS(v);
        int new_suf = suf[v] + 1;
        if (new_suf > suf[u]) {
            suf2[u] = suf[u];
            suf[u] = new_suf;
        }
        else {
            suf2[u] = max(suf2[u], new_suf);
        }
    }
}

void DFS2(int u, int pre = 0) {
    Used[u] = 1;
    for (int v : adj[u]) {
        if (suf[u] - 1 == suf[v]) {
            if (Used[v] == 0) DFS2(v, pre + 1);
            num[pre]++;
            ans[pre] = pre + suf2[u];
        }
    }
}
void sol() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) adj[0].push_back(i);
    DFS(0);
    memset(Used, 0, sizeof(Used));
    DFS2(0);
    int res = suf[0];
    for (int i = 1; i <= n; i++) {
        if (num[i] == 1) res = min(res, ans[i]);
    }
    cout << res - 1;
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
