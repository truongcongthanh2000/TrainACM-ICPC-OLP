#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-9;
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

int bitSet(int n) {
    int cnt = 0;
    while (n) {
        if (n & 1) cnt++;
        n /= 2;
    }
    return cnt;
}

int gauss (vector < vector<long double> > a, vector<long double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;
 
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;
 
        for (int i=0; i<n; ++i)
            if (i != row) {
                long double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }
 
    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    // for (int i=0; i<n; ++i) {
    //     long double sum = 0;
    //     for (int j=0; j<m; ++j)
    //         sum += ans[j] * a[i][j];
    //     if (abs (sum - a[i][m]) > EPS)
    //         return 0;
    // }

    // If we need any solution (in case INF solutions), we should be
    // ok at this point.
    // If need to solve partially (get which values are fixed/INF value):
//    for (int i=0; i<m; ++i)
//        if (where[i] != -1) {
//            REP(j,n) if (j != i && fabs(a[where[i]][j]) > EPS) {
//                where[i] = -1;
//                break;
//            }
//        }
    // Then the variables which has where[i] == -1 --> INF values
 
    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}

void solve() {
    int n, k; cin >> n >> k;
    long double p; cin >> p;
    int m = 1 << n;
    vector<vector<long double>> dp(m, vector<long double>(m + 1, 0));
    for (int i = 0; i < m; ++i) {
        if (bitSet(i) == k) {
            dp[i][i] = 1;
            continue;
        }
        dp[i][i] = -1;
        dp[i][i / 2 + m / 2] += p;
        dp[i][i / 2] += 1 - p;
        dp[i][m] = -1;
    }
    // for (int i = 0; i < m; ++i) {
    //     for (int j = 0; j <= m; ++j) cout << dp[i][j] << " \n"[j == m];
    // }
    vector<long double> res(m, 0);
    int ans = gauss(dp, res);
    // cout << ans;
    assert(ans != 0);
    // assert(ans == 1);
    cout << fixed << setprecision(10) << res[0];
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
