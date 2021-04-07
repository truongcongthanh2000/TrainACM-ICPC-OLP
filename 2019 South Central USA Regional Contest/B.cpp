#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 100;

void sol() {
    int n; cin >> n;
    vector<int> cc(366, 0);
    int s = 0;
    long double res = 0;
    for (int i = 0; i < n; ++i) {
        int c; cin >> c;
        s += c;
        cc[c]++;
        for (int j = 1; j <= c; ++j) res -= log10(j);
    }
    for (int i = 1; i <= s; ++i) res += log10(i) - log10(365);
    for (int i = 1; i <= 365; ++i) res += log10(i);
    for (int i : cc) {
        for (int j = 1; j <= i; ++j) res -= log10(j);
    }
    for (int i = 1; i <= 365 - n; ++i) res -= log10(i);
    cout << fixed << setprecision(10) << res;
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
