#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "OB"
#define OUT "OB"

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

const int maxN = 3e5 + 10;

vector<int> ptich(int x) {
    vector<int> res;
    while (x) {
        res.push_back(x % 10);
        x /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

bool ok(int n) {
    vector<int> a = ptich(n);
    sort(a.begin(), a.end());
    int old = 0;
    for (int x : a) {
        if (x == old) return false;
        old = x;
        if (n % x) return false;
    }
    return true;
}
void sol() {
    int L, H;
    cin >> L >> H;
    int res = 0;
    for (int c = L; c <= H; c++) res += ok(c);
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
