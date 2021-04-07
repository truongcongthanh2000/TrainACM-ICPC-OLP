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

long long gcd(long long x, long long y) {
    return y == 0 ? abs(x) : gcd(y, x % y);
}

long long lcm(long long x, long long y) {
    return x / gcd(x, y) * y;
}
struct Fraction{
    long long x, y;
    Fraction(){};
    Fraction(long long _x, long long _y) : x(_x), y(_y) {
        normal();
    };
    void normal() {
        long long GCD = gcd(x, y);
        x /= GCD;
        y /= GCD;
        if (y < 0) {
            x *= -1;
            y *= -1;
        }
    }
    Fraction operator+ (const Fraction& A){
        long long mau = lcm(y, A.y);
        long long tu = x * (mau / y) + (mau / A.y) * A.x;
        return Fraction(tu, mau);
    }
    Fraction operator- (const Fraction& A){
        long long mau = lcm(y, A.y);
        long long tu = x * (mau / y) - (mau / A.y) * A.x;
        return Fraction(tu, mau);
    }
};

void sol() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<long long> pw(15, 0);
    pw[0] = 1;
    for (int i = 1; i < 15; i++) pw[i] = pw[i - 1] * 10;
    int sz = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '.') sz = (int)s.size() - 1 - i;
    }
    reverse(s.begin(), s.end());
    long long val = 0;
    for (int i = 0; i < n; i++) {
        int c = s[i] - '0';
        val = c * pw[i] + val;
    }
    Fraction res(val, pw[n] - 1);
    for (int i = n, d = 0; i < (int)s.size(); i++, d++) {
        if (s[i] == '.') {
            res = Fraction(res.x, res.y * pw[d]);
            break;
        }
    }
    bool has = false;
    for (int i = n, d = 0; i < (int)s.size(); i++) {
        if (s[i] == '.') {
            has = true;
            continue;
        }
        int c = s[i] - '0';
        if (has) res = res + Fraction(c * pw[d++], 1);
        else res = res + Fraction(c, pw[sz - i]);
    }
    cout << res.x << "/" << res.y;
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
