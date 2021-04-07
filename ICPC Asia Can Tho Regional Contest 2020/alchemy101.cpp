#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 998244353;
const int MOD = 1e9 + 7;
const int Base = 311;
const long double EPS = 1e-1000;
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

const int maxN = 3e5 + 1000;

void sol() {
    int m;
    cin >> m;
    vector<int> ans(m, 0);
    iota(ans.begin(), ans.end(), 1);
    int x = 0;
    for (int i = 1; i <= m; i++) x ^= i;
    if (x != m) ans.erase(ans.begin() + (x ^ m) - 1);
    cout << (int)ans.size() << '\n';
    for (int x : ans) cout << x << ' ';
    cout << '\n';
}

void solve() {
    int T;
    cin >> T;
    //T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        //cout << "Test " << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
}
int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
