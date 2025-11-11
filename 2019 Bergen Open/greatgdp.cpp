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

void sol(){
    int n;
    cin >> n;
    vector<int> c(n), k(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 0; i < n; i++) cin >> k[i];

    vector<vector<int> > adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<double> cost(n), dp(n);
    function<void(int, int)> DFS = [&](int u, int pa) {
        dp[u] = cost[u];
        for (int v : adj[u]) {
            if (v != pa) {
                DFS(v, u);
                dp[u] += max(0.0, dp[v]);
            }
        }
    };

    auto ok = [&](double x) {
        for (int i = 0; i < n; i++) cost[i] = c[i] - x * k[i];
        DFS(0, -1);
        return dp[0] >= 0;
    };

    double L = 0, R = 1e6;
    for (int i = 0; i < 60; i++) {
        double mid = (L + R) / 2.0;
        if (ok(mid)) L = mid;
        else R = mid;
    }
    cout << fixed << setprecision(10) << (L + R) / 2.0;
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
