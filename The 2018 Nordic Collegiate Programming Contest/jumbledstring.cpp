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

void sol() {
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    auto get = [&](long long n) -> long long {
        long long x = sqrt(n * 2);
        while (x * (x - 1) < n * 2) x++;
        if (x * (x - 1) != n * 2) return -1;
        return x;
    };
    long long x = get(a);
    long long y = get(d);
    if (x == -1 || y == -1) {
        cout << "impossible";
        return;
    }
    if (a == 0) {
        if (d == 0) {
            if (b + c > 1) {
                cout << "impossible";
                return;
            }
            if (b == 1) {
                cout << "01";
                return;
            }
            if (c == 1) {
                cout << "10";
                return;
            }
            cout << "0";
            return;
        }
        if (y != b + c && b + c > 0) {
            cout << "impossible";
            return;
        }
        string res = string(y, '1');
        if (b + c > 0) res.insert(res.begin() + c, '0');
        cout << res;
        return;
    }
    if (d == 0) { ///a > 0
        if (x != b + c && b + c > 0) {
            cout << "impossible";
            return;
        }
        string res = string(x, '0');
        if (b + c > 0) res.insert(res.begin() + b, '1');
        cout << res;
        return;
    }
    auto nC2 = [&](long long n) {
        return n * (n - 1) / 2;
    };
    if (nC2(x + y) - a - d - b != c) {
        cout << "impossible";
        return;
    }
    long long r = b / y;
    long long q = b % y;
    string res = string(r, '0') + string(y - q, '1');
    if (x > r) res += "0";
    res += string(q, '1');
    if (x > r) res += string(x - r - 1, '0');
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
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
