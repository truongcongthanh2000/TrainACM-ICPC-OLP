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

const int maxN = 3e5 + 100;

namespace Pollard {
    template<typename num_t>
    num_t mulmod(num_t a, num_t b, num_t p) {
        a %= p; b %= p;
        num_t q = (num_t) ((long double) a * b / p);
        num_t r = a * b - q * p;
        while (r < 0) r += p;
        while (r >= p) r -= p;
        return r;
        /*
        num_t r = 0;
        int block = 1;
        num_t base = 1LL << block;
        for (; b; b >>= block) {
            r = (r + a * (b & (base - 1))) % p;
            a = a * base % p;
        }
        return r;
        */
    }
    template<typename num_t>
    num_t powmod(num_t n, num_t k, num_t p) {
        num_t r = 1;
        for (; k; k >>= 1) {
            if (k & 1) r = mulmod(r, n, p);
            n = mulmod(n, n, p);
        }
        return r;
    }
    template<typename num_t>
    int rabin(num_t n) {
        if (n == 2) return 1;
        if (n < 2 || !(n & 1)) return 0;
        const num_t p[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
        num_t a, d = n - 1, mx = 4;
        int i, r, s = 0;
        while (!(d & 1)) {++s; d >>= 1;}
        for (i = 0; i < mx; i++) {
            if (n == p[i]) return 1;
            if (!(n % p[i])) return 0;
            a = powmod(p[i], d, n);
            if (a != 1) {
                for (r = 0; r < s && a != n - 1; r++) a = mulmod(a, a, n);
                if (r == s) return 0;
            }
        }
        return 1;
    }
    template<typename num_t>
    inline num_t f(num_t a, num_t b, num_t n) {
        return (mulmod(a, a, n) + b) % n;
    }
    template<typename num_t>
    void factorize(num_t n, vector<num_t>& facs) {
        static int init_seed = 0;
        if (!init_seed) {
            init_seed = 1;
            srand(2311);
        }
        if (n == 1) {
            return;
        }
        if (rabin(n)) {
            facs.push_back(n);
            return;
        }
        if (n == 4) {
            facs.push_back(2);
            facs.push_back(2);
            return;
        }
        while (1) {
            num_t a = rand() & 63, x = 2, y = 2;
            while (1) {
                x = f(x, a, n), y = f(f(y, a, n), a, n);
                if (x == y) break;
                num_t p = __gcd(n, y <= x ? x - y : y - x);
                if (p > 1) {
                    factorize(p, facs), factorize(n / p, facs);
                    return;
                }
            }
        }
    }
}

void sol(){
    // int n, k;
    // cin >> n >> k;
    // vector<long long> p_i;
    // vector<long long> n_pi;
    // for (int i = 0; i < n; i++) {
    //     long long x;
    //     cin >> x;
    //     vector<long long> facts;
    //     Pollard::factorize(x, facts);
    //     sort(facts.begin(), facts.end());
    //     if (facts[0] == facts.back()) p_i.push_back(x);
    //     else n_pi.push_back(x);
    // }
    // sort()
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<int> s(m);
    for (int i = 0; i < m; i++) cin >> s[i];
    sort(s.begin(), s.end());

    int t = -1;
    if (a < b) t = b - 1;
    else t = n - b;

    int tmp = t;
    t -= 1;
    int ans = 0;
    for (int i = 0; i < m && t; i++) {
        if (s[i] + t <= tmp) {
            t--;
            ans++;
        }
        else {
            t = tmp - s[i];
            if (t <= 0) break;
            t--;
            ans++;
        }
    }
    ans = min(ans, abs(a - b) - 1);
    cout << ans << '\n';
}

void solve() {
    clock_t begin = clock();
    int T;
    cin >> T;
    //T = 1;
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
