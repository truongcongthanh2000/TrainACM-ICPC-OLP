#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

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

vector<long long> get_divisors(map<long long, int> prime) {
    vector<long long> res(1, 1);
    for (auto it : prime) {
        int n = res.size();
        long long val = 1;
        for (int i = 0; i < it.second; ++i) {
            val *= it.first;
            for (int j = 0; j < n; ++j) {
                res.push_back(res[j] * val);
            }
        }
    }
    return res;
}

void sol() {
    int nAsk = 66;
    auto ask = [&](int xL, int yL, int xR, int yR) {
        assert(nAsk > 0);
        nAsk -= 1;
        cout << "? " << xL << " " << yL << " " << xR << " " << yR << endl;
        long long ans;
        cin >> ans;
        return ans;
    };

    int lim = 1e9;
    long long area = ask(1, 1, lim, lim);

    int xL = 1;
    {
        int L = 1, R = lim;
        while (L < R) {
            int mid = (L + R + 1) >> 1;
            long long s = ask(mid, 1, lim, lim);
            if (s == area) {
                L = mid;
            }
            else {
                R = mid - 1;
            }
        }
        xL = L;
    }
    int yL = 1;
    {
        int L = 1, R = lim;
        while (L < R) {
            int mid = (L + R + 1) >> 1;
            long long s = ask(xL, mid, lim, lim);
            if (s == area) {
                L = mid;
            }
            else {
                R = mid - 1;
            }
        }
        yL = L;
    }
    vector<long long> facs;
    Pollard::factorize(area, facs);
    map<long long, int> prime;
    for (long long x : facs) prime[x] += 1;

    vector<long long> divs = get_divisors(prime);
    sort(divs.begin(), divs.end());

    vector<int> canChoose;
    for (auto x : divs) {
        auto y = area / x;
        auto xR = xL + x - 1;
        auto yR = yL + y - 1;
        if (xR <= lim && yR <= lim) {
            canChoose.push_back(x);
        }
    }
    int mx = canChoose.back();
    long long s = ask(xL, yL, xL + mx - 1, yL + area / mx - 1);
    int y_common = area / mx;
    int x = s / y_common;
    int y = area / x; 
    int xR = xL + x - 1;
    int yR = yL + y - 1;
    cout << "! " << xL << " " << yL << " " << xR << " " << yR << endl;
}

void solve() {
    int T = 1;
    //cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
