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

const int maxN = 1e3 + 100;

int d[maxN][maxN];

vector<int> black;

void sol(){
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
        if (i != j) d[i][j] = INF;
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        if (x == 1) black.push_back(i);
    }
    for(int i = 1; i <= n - 1; i++){
        int x, y;
        cin >> x >> y;
        d[x][y] = 1;
        d[y][x] = 1;
    }
    for (int k = 1; k <= n; k++)
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
        if (d[i][j] > d[i][k] + d[k][j])
            d[i][j] = d[i][k] + d[k][j];

    int res = INF;
    for (int u : black) {
        for (int v : black) {
            int cnt = 0;
            for (int k : black) {
                if (max(d[u][k], d[v][k]) <= d[u][v]) cnt++;
            }
            if (cnt >= m) res = min(res, d[u][v]);
        }
    }
    cout << res;
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
