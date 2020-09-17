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

const int maxN = 5e2 + 10;

int DP[maxN][maxN];

void sol() {
    int n; cin >> n;
    vector<vector<int>> M(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cin >> M[i][j];
    }
    for (int l = 1; l < n; ++l) {
        for (int i = 0; i < n; ++i) {
            int j = (i + l) % n;
            int nI = (i + 1) % n;
            int nJ = (j + n - 1) % n;
            for (int k = 0; k < l; ++k) {
                int nI = (i + k) % n;
                int nJ = (nI + 1) % n;
                DP[i][j] = max(DP[i][j], DP[i][nI] + DP[nJ][j]);
            }
            if (M[i][j]) DP[i][j] = max(DP[i][j], DP[nI][nJ] + 1);
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) res = max(res, DP[i][(i + n - 1) % n]);
    cout << res;
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
