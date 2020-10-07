#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[6] = {0, 0, 1, -1, 1, -1};
const int dy[6] = {1, -1, 0, 0, 1, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e3 + 10;

bool ok(int n, int base) {
    string s;
    while (n) {
        s += char(n % base);
        n /= base;
    }
    string t = s;
    reverse(s.begin(), s.end());
    return s == t;
}
vector<int> special = {0, 1, 6643, 1422773};
void sol() {
    int limits = 10;
    int a, b, k;
    cin >> a >> b >> k;
    if (k > 3) {
        int res = 0;
        for (int i = 0; i <= 1; i++) {
            res += i >= a && i <= b;
        }
        cout << res;
        return;
    }
    if (k == 3) {
        int res = 0;
        for (int x : special) {
            res += x >= a && x <= b;
        }
        cout << res;
        return;
    }
    int res = 0;
    for (int i = a; i <= b; i++) {
        res += ok(i, 2);
    }
    cout << res;
}

void solve() {
    int T;
    //cin >> T;
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
