#pragma GCC diagnostic ignored "-Wunused-parameter"

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

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 10;

long long F[505][505], F2[505][505];
int p[maxN];
void sol() {
    int n, m, t, d;
    cin >> n >> m >> t >> d;
    for (int i = 2; i <= t + 1; i++) {
        cin >> p[i];
    }
    auto floyd = [&]() {
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    F[i][j] = min(F[i][j], F[i][k] + F[k][j]);
                }
            }
        }
    };
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) F[i][j] = F2[i][j] = INF_LL;
        F2[i][i] = 0;
        F[i][i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        F[u][v] = min(F[u][v], 1LL * w);
        F[v][u] = F[u][v];
    }
    floyd();
    p[1] = 1;
    p[t + 2] = n;
    n = t + 2;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int u = p[i];
            int v = p[j];
            if (F[u][v] <= d) {
                F2[i][j] = F[u][v];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            F[i][j] = F2[i][j];
        }
    }
    floyd();
    if (F[1][n] == INF_LL) cout << "stuck";
    else cout << F[1][n];
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
