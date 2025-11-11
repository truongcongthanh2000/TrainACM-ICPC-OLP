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
    vector<vector<int> > edge(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if (u > v) swap(u, v);
        edge[u][v] = 1;
    }
    vector<int> remain(n);
    iota(remain.begin(), remain.end(), 0);

    vector<int> perm;
    for (int i = 0; i < n; i++) {
        int num = 0;
        for (int j = i + 1; j < n; j++) num += edge[i][j];
        int u = remain[num];
        remain.erase(remain.begin() + num);
        perm.push_back(u);
    }
    vector<long long> dp(n, 0);
    for (int i = 0; i < n; i++) {
        bool ok = true;
        for (int j = 0; j < i; j++) ok &= perm[j] > perm[i];
        dp[i] = ok;
    }
    for (int i = 0; i < n; i++) {
        if (dp[i]) {
            for (int j = i + 1; j < n; j++) {
                if (perm[j] > perm[i]) {
                    bool ok = true;
                    for (int k = i + 1; k < j; k++) ok &= perm[k] < perm[i] || perm[k] >= perm[j];
                    if (ok) dp[j] += dp[i];
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        bool ok = true;
        for (int j = i + 1; j < n; j++) ok &= perm[i] > perm[j];
        if (ok) ans += dp[i];
    }
    cout << ans;
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
