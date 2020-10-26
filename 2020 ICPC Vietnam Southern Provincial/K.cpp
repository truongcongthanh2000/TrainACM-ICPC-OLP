#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "OB"
#define OUT "OB"
#define X first
#define Y second

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-7;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

typedef pair<int, double> ii;
const int maxN = 1e5 + 5;

double f[105][maxN];
ii a[105];
int m[maxN];
void sol(){
    int t, n;
    cin >> t >> n;
    int sum = 0;
    for(int i = 0; i < n; i++){
        int cnt, radius;
        cin >> cnt >> radius;
        double P = 1.0 * 2 * radius * M_PI;
        a[i] = ii(cnt, P);
        sum += cnt;
    }

    for(int i = 0; i < n; i++)
    for(int j = 0; j <= sum; j++) f[i][j] = INF;
    int res = 0;
    for(int i = 0; a[0].Y * i <= t && i <= a[0].X; i++) {
        f[0][i] = a[0].Y * i;
        m[0] = i;
    }
    res = m[0];
    
    // for(int i = 1; i < n; i++){
    //     int j = 0;
    //     while (j <= sum){
    //         f[i][j] = f[i - 1][j];
    //         for(int k = 0; k <= a[i].X; k++){
    //             if (a[i].Y * k > t) break;
    //             f[i][j] = min(f[i][j], f[i - 1][j - k] + a[i].Y * k);
    //         }
    //         if (f[i][j] <= t) res = max(res, j);
    //         j++;
    //     }
    // }


    for(int i = 0; i < n - 1; i++){
        int cnt = a[i + 1].X;
        double cost = a[i + 1].Y;
        for(int j = 0; j <= m[i]; j++){
            if (f[i][j] == INF) continue;
            for(int k = 0; cost * k <= t && k <= cnt; k++){
                f[i + 1][j + k] = min(f[i + 1][j + k], f[i][j] + cost * k);
                if (f[i + 1][j + k] <= t) m[i + 1] = max(m[i + 1], j + k);
            }
        }
        res = max(res, m[i + 1]);
    }
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
