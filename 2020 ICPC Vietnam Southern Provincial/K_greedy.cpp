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

typedef pair<int, int> ii;
const int maxN = 1e5 + 5;

double f[105][maxN];
ii a[105];
int m[maxN];
void sol(){
    int t, n;
    cin >> t >> n;
    for(int i = 0; i < n; i++){
        int cnt, radius;
        cin >> cnt >> radius;
        a[i] = ii(cnt, radius * 2);
    }

    t /= M_PI;
    sort(a, a + n, [&](ii A, ii B){
        return A.second < B.second;
    });

    int temp = 0;
    int res = 0;
    for(int i = 0; i < n; i++){
        if (temp + a[i].first * a[i].second <= t){
            res += a[i].first;
            temp += a[i].first * a[i].second;
        }
        else {
            res += (t - temp) / a[i].second;
            break;
        }
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
