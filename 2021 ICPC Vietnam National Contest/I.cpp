#include<bits/stdc++.h>

using namespace std;

void ioFiles() {
    #ifdef THEMIS
        freopen("solve.txt", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif // THEMIS
}

const int maxN = 1e7 + 100;

int tag(string s) {
    if (s == "dp") return 0;
    if (s == "graph") return 1;
    if (s == "mathgeo") return 2;
    if (s == "ds") return 3;
    if (s == "adhoc") return 4;
    return -1;
}

long long dp[51][16][16][16][16][16];
void solve() {
    int n;
    cin >> n;
    vector<vector<int> > check(n, vector<int>(5, 0));
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        while (k--) {
            string s;
            cin >> s;
            check[i][tag(s)] += 1;
        }
    }
    vector<int> L(5), R(5);
    for (int i = 0; i < 5; i++) cin >> L[i] >> R[i];

    dp[0][0][0][0][0][0] = 1;
    for (int id = 0; id < n; id++) {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                for (int k = 0; k < 16; k++) {
                    for (int u = 0; u < 16; u++) {
                        for (int v = 0; v < 16; v++) {
                            if (dp[id][i][j][k][u][v]) {
                                dp[id + 1][i][j][k][u][v] += dp[id][i][j][k][u][v];
                                int ni = i + check[id][0];
                                int nj = j + check[id][1];
                                int nk = k + check[id][2];
                                int nu = u + check[id][3];
                                int nv = v + check[id][4];
                                if (ni <= 15 && nj <= 15 && nk <= 15 && nu <= 15 && nv <= 15) {
                                    dp[id + 1][ni][nj][nk][nu][nv] += dp[id][i][j][k][u][v];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    long long ans = 0;
    for (int i = L[0]; i <= R[0]; i++) {
        for (int j = L[1]; j <= R[1]; j++) {
            for (int k = L[2]; k <= R[2]; k++) {
                for (int u = L[3]; u <= R[3]; u++) {
                    for (int v = L[4]; v <= R[4]; v++) {
                        ans += dp[n][i][j][k][u][v];
                        if (i == 0 && j == 0 && k == 0 && u == 0 && v == 0) ans--;
                    }
                }
            }
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ioFiles();
    int t = 1;
    //cin >> t;
    while (t--) solve();
}
