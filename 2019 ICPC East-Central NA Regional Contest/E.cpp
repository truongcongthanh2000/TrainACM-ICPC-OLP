#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e2 + 10;

int e[maxN][maxN];
int dist[maxN][maxN][12];
int r, c, n;

int inSide(int x, int y) {
    return x >= 1 && x <= r && y >= 1 && y <= c && e[x][y] != -1;
}

bool isPass(int x, int y) {
    for (int h = 0; h < 4; h++) {
        int u = x + dx[h];
        int v = y + dy[h];
        if (!inSide(u, v)) return false;
        if (h % 2 == 0 && e[x][y] >= e[u][v]) return false;
        if (h % 2 == 1 && e[x][y] <= e[u][v]) return false;
    }
    return true;
}
void sol() {
    cin >> r >> c >> n;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            cin >> e[i][j];
            for (int k = 0; k <= n; k++) dist[i][j][k] = INF;
        }
    }
    for (int i = 1; i <= r; i++) {
        if (e[i][1] != -1) {
            int d = isPass(i, 1);
            dist[i][1][d] = e[i][1];
        }
    }
    for (int j = 1; j < c; j++) {
        for (int i = 1; i <= r; i++) {
            for (int k = 0; k <= n; k++) {
                if (dist[i][j][k] != INF) {
                    for (int dx = -1; dx <= 1; dx++) {
                        int u = i + dx;
                        int v = j + 1;
                        if (inSide(u, v)) {
                            int cost = isPass(u, v);
                            int nxt_k = k + cost;
                            if (nxt_k <= n && dist[u][v][nxt_k] > dist[i][j][k] + e[u][v]) {
                                dist[u][v][nxt_k] = dist[i][j][k] + e[u][v];
                            }
                        }
                    }
                }
            }
        }
    }
    int res  = INF;
    for (int i = 1; i <= r; i++) {
        res = min(res, dist[i][c][n]);
    }
    if (res == INF) cout << "impossible";
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
