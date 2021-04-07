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
    int n, m, L;
    cin >> n >> m >> L;
    vector<pair<int, int> > p(n);
    for (int i = 0; i < n; i++) cin >> p[i].first >> p[i].second;
    vector<pair<int, int> > a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin(), a.end());

    vector<int> sum(m + 1, 0);
    auto up = [&](int x, int y) {
        if (y > L) return;
        int l = lower_bound(a.begin(), a.end(), make_pair(x + y - L, -1)) - a.begin();
        int R = upper_bound(a.begin(), a.end(), make_pair(x - y + L, m)) - a.begin();
        sum[l] += 1;
        sum[R] -= 1;
    };
    for (int i = 0; i < n; i++) up(p[i].first, p[i].second);
    for (int i = 1; i < m; i++) sum[i] += sum[i - 1];

    vector<int> ans(m);
    for (int i = 0; i < m; i++) ans[a[i].second] = sum[i];
    for (int i = 0; i < m; i++) cout << ans[i] << '\n';
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
