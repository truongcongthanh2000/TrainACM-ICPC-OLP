#include <bits/stdc++.h>

using namespace std;

void open_file() {
#ifdef THEMIS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif  // THEMIS
}

#define ull unsigned long long
mt19937 rnd((ull)chrono::system_clock::now().time_since_epoch().count());

using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n) {  // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}) {
        if (n % a == 0) return false;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}) {
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

const int maxN = 4e6;
int p[maxN];
vector<int> primes;
map<ull, int> M;

void gen() {
    for (int i = 2; i < maxN; i++) {
        if (!p[i]) {
            for (int j = i + i; j < maxN; j += i) p[j] = i;
            primes.push_back(i);
        }
    }

    ull limits = 1000000000;
    limits *= limits * 10;

    for (int i = 0; i < (int)primes.size(); i++) {
        ull tich = 1;
        for (int j = i; j < (int)primes.size(); j++) {
            if (tich <= limits / primes[j]) {
                tich *= primes[j];
                M[tich] = 1;
            } else {
                break;
            }
        }
    }
}

bool special_case(ull n) {
    if (MillerRabin(n)) return true;
    if (n <= 1e12) return false;

    ull x = sqrt(n);
    while (x * x > n) x--;
    while ((x + 1) * (x + 1) <= n) x++;

    ull larger = 0;
    ull weaker = 0;
    for (int i = 1;; i++) {
        ull y = x + i;
        if (MillerRabin(y)) {
            larger = y;
            break;
        }
    }

    for (int i = 0;; i--) {
        ull y = x + i;
        if (MillerRabin(y)) {
            weaker = y;
            break;
        }
    }

    return n == larger * weaker;
}

void sol() {
    ull n;
    cin >> n;
    if (M[n] || special_case(n)) {
        cout << "NICE" << '\n';
    } else {
        cout << "UGLY" << '\n';
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    open_file();
    gen();
    int t = 1;
    cin >> t;
    while (t--) sol();
}
