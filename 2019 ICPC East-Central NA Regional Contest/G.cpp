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

const int maxN = 2e6 + 10;

int x[maxN];

bool find(int value, int L, int R) {
    if (L > R) return false;
    int mid = (L + R) >> 1;
    if (x[mid] == value) return true;
    if (x[mid] < value) return find(value, mid + 1, R);
    return find(value, L, mid - 1);
}
void sol() {
    int n, m, a, c;
    cin >> n >> m >> a >> c >> x[0];
    for (int i = 1; i <= n; i++) {
        x[i] = (1LL * a * x[i - 1] + c) % m;
    }
    int res = 0;
    for (int i = 1; i <= n; i++) res += find(x[i], 1, n);
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
