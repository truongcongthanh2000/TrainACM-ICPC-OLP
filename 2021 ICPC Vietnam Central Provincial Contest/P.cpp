#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".txt","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

int dp[11][101][101][101];

void init() {
    for (int u = 1; u <= 10; u++) {
        for (int i = 1; i <= 100; i++){ 
            for (int j = 1; j <= 100; j++) {
                for (int k = 1; k <= 100; k++) {
                    dp[u][i][j][k] = max(dp[u][i][j][k], dp[u][i - 1][j][k]);
                    dp[u][i][j][k] = max(dp[u][i][j][k], dp[u][i][j - 1][k]);
                    dp[u][i][j][k] = max(dp[u][i][j][k], dp[u][i][j][k - 1]);
                    if (u <= i && u <= j && u <= k) {
                        dp[u][i][j][k] = max(dp[u][i][j][k], dp[u][i - u][j][k] + j * k);
                        dp[u][i][j][k] = max(dp[u][i][j][k], dp[u][i][j - u][k] + i * k);
                        dp[u][i][j][k] = max(dp[u][i][j][k], dp[u][i][j][k - u] + i * j);
                    }
                }
            }
        }
    }
}

void sol() {
    init();
    int t;
    cin >> t;    
    while (t--) {
        int x, y, z, u;
        cin >> x >> y >> z >> u;
        cout << dp[u][x][y][z] << '\n';
    }
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    //cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
