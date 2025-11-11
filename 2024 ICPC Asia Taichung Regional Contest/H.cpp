#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T>>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) {
        for (const auto& value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for (auto& x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-12;
const int BLOCK = 330;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e6 + 100;
const int MOD = 998244353;

/// MOD NUM, MOD < 2^31
template <int _MOD>
class num_t {
    //    long long Mul(long long x, long long y,long long m) /// Tinh (x * y) mod M voi (x,y, M <= 10 ^ 18)
    //    {
    //        x %= m; y %= m;
    //        long long q = (long double) x * y / m;
    //        long long r = (x * y - q * m) % m;
    //        if (r < 0) r += m;
    //        return r;
    //    }
    static constexpr int MOD = _MOD;

   private:
    int value;

    static int power(int a, int n) {
        int ans = 1;
        for (; n; n >>= 1, a = 1LL * a * a % MOD) {
            if (n & 1) {
                ans = 1LL * ans * a % MOD;
            }
        }
        return ans;
    }

    //    static int inverse(int a, int m) {
    //        a %= m;
    //        assert(a);
    //        return a == 1 ? 1 : int(m - 1LL * inverse(m, a)) * m / a);
    //    }

    static int inverse(int a) {
        return power(a, MOD - 2);
    }

   public:
    num_t() : value(0) {};
    template <typename U>
    num_t(U _value) {
        value = _value % MOD;
        if (value < 0) value += MOD;
    }

    friend ostream& operator<<(ostream& out, const num_t& n) { return out << int(n); }
    friend istream& operator>>(istream& in, num_t& n) {
        long long _value;
        in >> _value;
        n = num_t(_value);
        return in;
    }

    bool operator==(const num_t& other) { return value == other.value; }
    bool operator!=(const num_t& other) { return !(*this == other); }

    void operator=(const num_t& other) { value = other.value; }

    template <typename U>
    void operator=(U other) { value = other; };

    operator int() const { return value; }

    num_t power(int n) const {
        num_t ans;
        ans.value = power(value, n);
        return ans;
    };

    num_t inverse() const {
        num_t ans;
        ans.value = inverse(value);
        return ans;
    }

    friend num_t inverse(const num_t& other) { return other.inverse(); }

    num_t& operator+=(const num_t& other) {
        value += other.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }

    template <typename U>
    num_t& operator+=(U other) {
        return *this += num_t(other);
    }

    num_t& operator-=(const num_t& other) {
        value -= other.value;
        if (value < 0) value += MOD;
        return *this;
    }

    template <typename U>
    num_t& operator-=(U other) {
        return *this -= num_t(other);
    }

    num_t& operator*=(const num_t& other) {
        value = 1LL * value * other.value % MOD;
        return *this;
    }

    num_t& operator/=(const num_t& other) {
        return *this *= other.inverse();
    }

    num_t& operator++() {
        value++;
        if (value >= MOD) value -= MOD;
        return *this;
    }

    num_t operator++(int) {
        num_t ans(*this);
        *this += 1;
        return ans;
    }

    num_t& operator--() {
        value++;
        if (value < 0) value += MOD;
        return *this;
    }

    num_t operator--(int) {
        num_t ans(*this);
        this -= 1;
        return ans;
    }

    num_t operator-() const {
        return num_t(-value);
    }

    friend num_t operator+(const num_t& a, const num_t& b) { return num_t(a) += b; }
    template <typename U>
    friend num_t operator+(const num_t& a, U b) { return num_t(a) += b; }
    template <typename U>
    friend num_t operator+(U a, const num_t& b) { return num_t(a) += b; }

    friend num_t operator-(const num_t& a, const num_t& b) { return num_t(a) -= b; }
    template <typename U>
    friend num_t operator-(const num_t& a, U b) { return num_t(a) -= b; }
    template <typename U>
    friend num_t operator-(U a, const num_t& b) { return num_t(a) -= b; }

    friend num_t operator*(const num_t& a, const num_t& b) { return num_t(a) *= b; }
    template <typename U>
    friend num_t operator*(const num_t& a, U b) { return num_t(a) *= b; }
    template <typename U>
    friend num_t operator*(U a, const num_t& b) { return num_t(a) *= b; }

    friend num_t operator/(const num_t& a, const num_t& b) { return num_t(a) /= b; }
    template <typename U>
    friend num_t operator/(const num_t& a, U b) { return num_t(a) /= b; }
    template <typename U>
    friend num_t operator/(U a, const num_t& b) { return num_t(a) /= b; }
};

/// usage
using type = num_t<MOD>;

vector<type> fact{1};
type nCk(int n, int k) {
    if (k > n) return 0;
    while (fact.size() <= n) fact.push_back(fact.back() * fact.size());
    return fact[n] / (fact[k] * fact[n - k]);
}

void sol() {
    int n, k;
    cin >> n >> k;
    vector<type> dp(n + 1, 1);
    type pw2 = 1;
    for (int i = 1; i <= n; i++) {
        pw2 *= 2;
        if (i < k) {
            dp[i] = pw2;
            continue;
        }
        if (i == k) {
            dp[i] = pw2 - 2;
        }
        else {
            dp[i] = dp[i - 1] * 2 - dp[i - k];
        }
    }
    type ans = 0;
    for (int i = 0; i < n; i++) ans += nCk(n - 1, i) * dp[i];
    cout << ans << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    // cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        // cerr << "Processing test = " << TestCase << '\n';
        // cout << "Case #" << TestCase << ": ";
        sol();
        // if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc, char* argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
