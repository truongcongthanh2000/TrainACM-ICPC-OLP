#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".txt","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD1 = 1e9 + 9;
const int MOD2 = 1e9 + 11;
const int MOD = 1e9 + 7;
///MOD NUM, MOD < 2^31
template<int _MOD>
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
    template<typename U>
    num_t(U _value) { value = _value % MOD; if (value < 0) value += MOD; }

    friend ostream& operator << (ostream& out, const num_t &n) {return out << int(n); }
    friend istream& operator >> (istream& in, num_t &n) {long long _value; in >> _value; n = num_t(_value); return in; }

    bool operator == (const num_t &other) {return value == other.value; }
    bool operator != (const num_t &other) {return !(*this == other); }

    void operator = (const num_t &other) {value = other.value; }

    template<typename U>
    void operator = (U other) {value = other;};

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

    friend num_t inverse(const num_t &other) {return other.inverse(); }

    num_t& operator += (const num_t &other) {
        value += other.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }

    template<typename U>
    num_t& operator += (U other) {
        return *this += num_t(other);
    }

    num_t& operator -= (const num_t &other) {
        value -= other.value;
        if (value < 0) value += MOD;
        return *this;
    }

    template<typename U>
    num_t& operator -= (U other) {
        return *this -= num_t(other);
    }

    num_t& operator *= (const num_t &other) {
        value = 1LL * value * other.value % MOD;
        return *this;
    }

    num_t& operator /= (const num_t &other) {
        return *this *= other.inverse();
    }

    num_t& operator ++ () {
        value++;
        if (value >= MOD) value -= MOD;
        return *this;
    }

    num_t operator ++ (int) {
        num_t ans(*this);
        *this += 1;
        return ans;
    }


    num_t& operator -- () {
        value++;
        if (value < 0) value += MOD;
        return *this;
    }

    num_t operator -- (int) {
        num_t ans(*this);
        this -= 1;
        return ans;
    }

    num_t operator - () const {
        return num_t(-value);
    }

    friend num_t operator + (const num_t &a, const num_t &b) {return num_t(a) += b; }
    template<typename U> friend num_t operator + (const num_t &a, U b) {return num_t(a) += b; }
    template<typename U> friend num_t operator + (U a, const num_t &b) {return num_t(a) += b; }

    friend num_t operator - (const num_t &a, const num_t &b) {return num_t(a) -= b; }
    template<typename U> friend num_t operator - (const num_t &a, U b) {return num_t(a) -= b; }
    template<typename U> friend num_t operator - (U a, const num_t &b) {return num_t(a) -= b; }

    friend num_t operator * (const num_t &a, const num_t &b) {return num_t(a) *= b; }
    template<typename U> friend num_t operator * (const num_t &a, U b) {return num_t(a) *= b; }
    template<typename U> friend num_t operator * (U a, const num_t &b) {return num_t(a) *= b; }

    friend num_t operator / (const num_t &a, const num_t &b) {return num_t(a) /= b; }
    template<typename U> friend num_t operator / (const num_t &a, U b) {return num_t(a) /= b; }
    template<typename U> friend num_t operator / (U a, const num_t &b) {return num_t(a) /= b; }

};

///usage
using type1 = num_t<MOD1>;
using type2 = num_t<MOD2>;
using type_ans = num_t<MOD>;
void sol() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    vector<int> nen;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        nen.push_back(a[i]);
    }
    sort(nen.begin(), nen.end());
    nen.resize(unique(nen.begin(), nen.end()) - nen.begin());
    for (int i = 0; i < n; i++) a[i] = lower_bound(nen.begin(), nen.end(), a[i]) - nen.begin() + 1;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        b[i] = lower_bound(nen.begin(), nen.end(), x) - nen.begin() + 1;
    }
    int sz = (int)nen.size();
    vector<type1> value1(sz + 1, 1);
    int base = 998244353;
    for (int i = 1; i <= sz; i++) value1[i] = value1[i - 1] * base;
    vector<type2> value2(sz + 1, 1);
    for (int i = 1; i <= sz; i++) value2[i] = value2[i - 1] * base;
    vector<type_ans> pw2(n + 1, 1);
    for (int i = 1; i <= n; i++) pw2[i] = pw2[i - 1] * 2;

    type1 h1 = 0;
    type2 h2 = 0;
    map<long long, int> freq;
    for (int i = 0; i < n; i++) {
        h1 += value1[a[i]] - value1[b[i]];
        h2 += value2[a[i]] - value2[b[i]];
        long long h = 1LL * int(h1) * MOD + int(h2); 
        freq[h] += 1;
    }
    type_ans ans = 0;
    for (auto it : freq) {
        int n = it.second;
        ans += pw2[n] - n - 1;
    }
    cout << ans;
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
