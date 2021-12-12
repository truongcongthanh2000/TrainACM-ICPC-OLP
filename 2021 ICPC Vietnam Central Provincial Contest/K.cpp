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
using type = num_t<MOD>;
//multiply matrix and power(a ^ n)
template<typename T>
vector<vector<T>> operator * (const vector<vector<T> > &a, const vector<vector<T> > &b) {
    if ((int)a.size() == 0 || (int)b.size() == 0) {
        return {{}};
    }
    int m = (int)a.size();
    int n = (int)a[0].size();
    assert(n == (int)b.size());
    int p = (int)b[0].size();
    vector<vector<T> > c(m, vector<T>(p));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                //update: c[i][j]
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

template<typename T>
vector<vector<T>>& operator *=(vector<vector<T>> &a, vector<vector<T>> &b) {
    return a = a * b;
}

template <typename T, typename U>
vector<vector<T>> power(vector<vector<T> > &a, U n) {
    assert(n >= 0);
    int sz = (int)a.size();
    assert(sz == (int)a[0].size());
    vector<vector<T> > ans(sz, vector<T>(sz, 0));
    for (int i = 0; i < sz; i++) {
        ans[i][i] = 1;
    }

    for (; n; n >>= 1, a *= a) {
        if (n & 1) {
            ans *= a;
        }
    }
    return ans;
}

void sol() {
    int h, w, t;
    cin >> h >> w >> t;
    vector<string> s(h);
    for (int i = 0; i < h; i++) cin >> s[i];
    auto id = [&](int x, int y) {
        return x * w + y;
    };
    vector<vector<type> > a(h * w, vector<type>(h * w, 0));
    vector<type> base(h * w, 0);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '#') continue;
            base[id(i, j)] = 1;
            vector<char> choose = {s[i][j]};
            if (s[i][j] == '+') choose = {'R', 'D', 'L', 'U'};
            for (char c : choose) {
                int x = i, y = j;
                if (c == 'R') y++;
                if (c == 'D') x++;
                if (c == 'L') y--;
                if (c == 'U') x--;
                if (x >= 0 && x < h && y >= 0 && y < w && s[x][y] != '#') {
                    a[id(i, j)][id(x, y)] = 1;
                }
            }
        }
    }
    a = power(a, t);
    vector<vector<type> > vbase = {base};
    vbase = vbase * a;
    type ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) ans += vbase[0][id(i, j)];
    }
    cout << ans;
}

void solve() {
    clock_t start, end;
    start = clock();
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
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
