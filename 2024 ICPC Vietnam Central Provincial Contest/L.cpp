#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<vector<T>> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) {
        for (const auto &value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (auto &x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-9;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 1e6 + 100;
const int MOD = 998244353;

using u64 = uint64_t;
using u128 = __uint128_t;

void sol() {
    // know sorted: s(i) + s(j) > s(j) + s(i)
    // digit sorted: 0.(s(i)) > 0.(s(j)) -> n / 9...9(log10(n) + 1 9-digits) > m / 9...9(log10(m) + 1 9-digits)
    // find largest p/q that total digits of n sastify (n / 9...9(log10(n) + 1 9-digits)) >= p/q is >= k
    u64 n, k;
    cin >> n >> k;

    auto total_digits = [&](u64 p, u64 q) {  // total digits of n sastify (n / 9...9(log10(n) + 1 9-digits)) >= p/q
        u64 ans = 0;
        u64 numerator = 1;
        for (int ndigits = 1; numerator <= n; ndigits++, numerator = numerator * 10) {
            u64 denominator = numerator * 10 - 1;
            // n / 9..9 >= p / q -> n >= p * 9...9 / q
            u128 lower_bound = ((u128)p * denominator + q - 1) / q;
            if (lower_bound < numerator) {
                lower_bound = numerator;
            }
            if (lower_bound <= min(n, denominator)) {
                ans += (min(n, denominator) - lower_bound + 1) * ndigits;
            }
        }
        return ans;
    };
    // to find largest p/q, we can traverse each number of digits d and list all p / 9..9(d) so that total_digits >= k
    vector<pair<u64, u64>> fraction_per_ndigits;
    u64 numerator = 1;
    for (int ndigits = 1; numerator <= n; ndigits++, numerator = numerator * 10) {
        u64 denominator = numerator * 10 - 1;
        u64 L = numerator, R = denominator, p = R + 1;
        while (L <= R) {
            u64 mid = (L / 2 + R / 2) + (L % 2 + R % 2) / 2;
            if (total_digits(mid, denominator) >= k) {
                p = mid;
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }
        if (p <= denominator) {
            fraction_per_ndigits.push_back({p, denominator});
        }
    }
    if (fraction_per_ndigits.empty()) {
        cout << -1 << '\n';
        return;
    }
    // find largest p/q
    u64 p = fraction_per_ndigits[0].first, q = fraction_per_ndigits[0].second;
    for (int i = 1; i < (int)fraction_per_ndigits.size(); i++) {
        u64 a = fraction_per_ndigits[i].first, b = fraction_per_ndigits[i].second;
        // check a / b > p / q or not ?
        if ((u128)a * q > (u128)p * b) {
            p = a;
            q = b;
        }
    }
    u64 ndigits = total_digits(p, q);
    string s = std::to_string(p);
    u64 remain = (ndigits - k) % (u64)s.size();
    // ndigits can have multiple s like this, (p)(pp)(ppp)... so we need to modular to find the correct position
    cout << s[s.size() - remain - 1] << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        // cout << "Case #" << TestCase << ": ";
        sol();
        // if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc, char *argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
