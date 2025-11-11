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

vector<int> adj[maxN];

int dp[maxN], c[maxN], u[maxN];
void DFS(int u) {
    for (int v : adj[u]) {
        dp[v] = max(dp[u], c[v]) - ::u[v];
        DFS(v);
    }
}
void sol() {
    int n;
    cin >> n >> dp[0];
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> u >> c[i] >> ::u[i];
        adj[u].push_back(i);
    }
    DFS(0);
    cout << *min_element(dp, dp + n + 1);
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
