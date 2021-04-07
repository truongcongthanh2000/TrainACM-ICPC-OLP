#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-9;
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

const int maxN = 2e5 + 1000;

int a[maxN], h[maxN];
void sol() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        h[i] = i;
    }
    vector<pair<int, int> > res;
    while (true) {
        sort(h + 1, h + 1 + n, [&](int i, int j) {
            return a[i] > a[j];
        });
        if (a[h[2]] == 0) break;
        int u = h[1];
        int v = h[2];
        res.push_back({u, v});
        a[u] -= 1;
        a[v] -= 1;
    }
    if (*max_element(a + 1, a + 1 + n) == 0) {
        cout << "yes" << '\n';
        for (auto [u, v] : res) cout << u << " " << v << '\n';
    }
    else cout << "no";
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
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
