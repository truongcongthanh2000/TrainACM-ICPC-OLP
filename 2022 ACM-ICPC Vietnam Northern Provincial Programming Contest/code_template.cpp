mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
int rand(int l, int r){
    return (long long)(1LL * rnd() * RAND_MAX + rnd()) % (r - l + 1) + l;
}
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
void Diophante(long long a, long long b, long long &d, long long&x)
{
  long long m, n, r, q, xm, xn, xr;
  m = a; xm = 1;
  n = b; xn = 0;
  while (n != 0)
  {
    q = m / n;
    r = m - q * n;
    xr = xm - q * xn;
    m = n; xm = xn;
    n = r; xn = xr;
  }
  d = m;
  x = xm;
  cout << d << " " << x << '\n';
}

{
    // dijkstra for minimize path
    template <typename TEdge, typename TVertex>
    void dijkstra(const vector<vector<pair<int, TEdge>>>& adj, int source, vector<TVertex>& d) {
        int n = (int)adj.size();

        d.resize(n);
        for (int i = 0; i < n; i++) d[i] = std::numeric_limits<TVertex>::max();  // initialize for each vertex
        d[source] = 0;                                                           /// initialize for vertex source

        typedef pair<TVertex, int> i2;
        priority_queue<i2, vector<i2>, std::greater<i2>> Q;
        Q.push({d[source], source});

        while ((int)Q.size() != 0) {
            i2 valueTop = Q.top();
            Q.pop();

            TVertex du = valueTop.first;
            int u = valueTop.second;
            if (d[u] != du) {  // or abs(d[u] - du) > EPS for double
                continue;
            }

            for (auto it : adj[u]) {
                int v = it.first;
                TEdge w = it.second;

                if (d[v] > d[u] + w) {  // if d[u] + w is better than d[v]
                    d[v] = d[u] + w;
                    Q.push({d[v], v});
                }
            }
        }
    }
}

{
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
}

{
    const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;
    const int P1 = 311, P2 = 331;
    struct H {
        using type1 = num_t<MOD1>;
        using type2 = num_t<MOD2>;

        type1 a1;
        type2 a2;

        H(){};

        H(type1 _a1) {
            a1 = _a1;
            a2 = _a1;
        }

        H(type1 _a1, type2 _a2) {
            a1 = _a1;
            a2 = _a2;
        }

        friend ostream& operator << (ostream& out, const H& v) {return out << v.a1 << " " << v.a2 << '\n'; }

        bool operator == (const H& other) {return a1 == other.a1 && a2 == other.a2; }
        bool operator != (const H& other) {return !(*this == other); }
        bool operator < (const H& other) { return a1 < other.a1 || (a1 == other.a1 && a2 < other.a2); };
        bool operator <= (const H& other) { return (*this < other) || (*this == other); };
        bool operator > (const H& other) { return !(*this <= other); };
        bool operator >= (const H& other) { return !(*this < other); };

        void operator = (const H& other) { a1 = other.a1; a2 = other.a2; }

        inline H operator + (const H& other) { return H(a1 + other.a1, a2 + other.a2); }
        inline H operator += (const H& other) { *this = H(a1 + other.a1, a2 + other.a2); return *this; }
        inline H operator - (const H& other) { return H(a1 - other.a1, a2 - other.a2); }
        inline H operator -= (const H& other) { *this = H(a1 - other.a1, a2 - other.a2); return *this; }
        inline H operator * (const H& other) { return H(a1 * other.a1, a2 * other.a2); }
        inline H operator *= (const H& other) { *this = H(a1 * other.a1, a2 * other.a2); return *this; }
        inline H operator / (const H& other) { return H(a1 / other.a1, a2 / other.a2); }
        inline H operator /=(const H& other) { *this = H(a1 / other.a1, a2 / other.a2); return *this; }

        template<typename U> inline H operator + (const U& other) { return *this + H(other, other + MOD1); }
        template<typename U> friend H operator + (const U& a, const H& b) { return H(a, a + MOD1) + b; }

        template<typename U> inline H operator - (const U& other) { return *this - H(other, other + MOD1); }
        template<typename U> friend H operator - (const U& a, const H& b) { return H(a, a + MOD1) - b; }

        template<typename U> inline H operator * (const U& other) { return *this * H(other, other + MOD1); }
        template<typename U> friend H operator * (const U& a, const H& b) { return H(a, a + MOD1) * b; }

        template<typename U> inline H operator / (const U& other) { return *this / H(other, other + MOD1); }
        template<typename U> friend H operator / (const U& a, const H& b) { return H(a, a + MOD1) / b; }

        long long getValue() {
            return 1LL * int(a1) * INF + int(a2);
        }
    };

    struct Hash {
        vector<H> p, vHash;
        Hash(){};

        void init(const string &s) {
            int n = (int)s.size();
            p.resize(n + 1);
            vHash.resize(n + 1);

            const H P = H(P1, P2);
            p[0] = H(1, 1);
            vHash[0] = H(0, 0);
            for (int i = 1; i <= n; i++) {
                p[i] = p[i - 1] * P;
                vHash[i] = vHash[i - 1] * P + s[i - 1];
            }
        }

        H getHash(int L, int R) {
            return vHash[R] - vHash[L - 1] * p[R - L + 1];
        }
};
}

{
    ///combinatorial, nCk, math
    template <class T>
    struct math {
        vector<T> fact, inv_fact;
        int n;

        math(int _n = 1) {
            n = _n;
            fact = vector<T>(n + 1, 1);
            inv_fact = vector<T>(n + 1, 1);
            for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;

            inv_fact.back() = inverse(fact.back());
            for (int i = n; i >= 1; i--) inv_fact[i - 1] = inv_fact[i] * i;
        }

        T nCk(int n, int k) {
            if (k < 0) return T(0);
            T TS = fact[n];
            T MS = inv_fact[k] * inv_fact[n - k];

            return TS * MS;
        }
    };

    ///usage
    math<type> combi(3 * n + 10);
}
{
    ///RMQ, Range Min/Max Query
    template <typename T, class func = function<T(const T&, const T&)> >
    struct rmq {
        int n;
        vector<vector<T> > b;
        func F;

        rmq(const vector<T> &a, const func &_F) : F(_F) {
            n = (int)a.size();
            int log_size = 0;
            while ((1 << log_size) <= n) log_size++;
            b.resize(log_size);
            b[0] = a;
            for (int j = 1; j < log_size; j++) {
                b[j].resize(n - (1 << j) + 1);
                for (int i = 0; i + (1 << j) <= n; i++) {
                    b[j][i] = F(b[j - 1][i], b[j - 1][i + (1 << (j - 1))]);
                }
            }
        }

        T calc(int L, int R) const {
            assert(0 <= L && L <= R && R < n);
            int k = __lg(R - L + 1);
            assert((1 << k) <= (R - L + 1) && (1 << (k + 1)) > (R - L + 1));
            return F(b[k][L], b[k][R - (1 << k) + 1]);
        }
    };

    ///usage:
    vector<long long> d(n - 1);
    rmq<long long> st(d, [&](long long a, long long b) {
        return __gcd(a, b);
    });

}
{
    ///HLD, Heavy Light Decomposition
    vector<int> adj[maxN];
    int numNode[maxN];

    void DFS(int u, int pa) {
        numNode[u] = 1;
        for (int v : adj[u]) {
            if (v != pa) {
                DFS(v, u);
                numNode[u] += numNode[v];
            }
        }
    }
    int chainHead[maxN], chainInd[maxN], L[maxN], R[maxN];
    int nChain = 1, Base = 0;
    void HLD(int u, int pa) {
        if (chainHead[nChain] == 0) { ///chainHead[x] : đỉnh đầu tiên của đoạn thứ x
            chainHead[nChain] = u;
        }
        chainInd[u] = nChain; ///đoạn mà chứa đỉnh u
        L[u] = ++Base; ////Thứ tự của đỉnh u khi trải mảng
        int dinh = 0;
        for (int v : adj[u]) {
            if (v == pa) continue;
            if (dinh == 0 || numNode[v] > numNode[dinh]) dinh = v; ////lấy đỉnh v có số nút con là max
        }
        if (dinh > 0) HLD(dinh, u);
        for (int v : adj[u]) {
            if (v == pa) continue;
            if (v != dinh) {
                nChain++;
                HLD(v, u);
            }
        }
        R[u] = Base;
    }

    /// Build Segment Tree ....

    int parent[maxN];
    void update(int u, int a) { /// Tách đường đi từ u đến a: đỉnh u thuộc cây con gốc a
        // uchain chuỗi hiện tại của u
        // achain chuỗi của a
         int uchain = chainInd[u], achain = chainInd[a];
         while (1) {
            // Nếu u và a cùng nằm trên một chuỗi thì update đoạn từ u đến a và kết thúc.
              if (uchain == achain) {
                   updateIntervalTree(..., L[a], L[u], ...);
                   break;
              }
            // Nếu u và a không nằm trên cùng một chuỗi thì update đoạn từ u đến đỉnh đầu của chuỗi hiện tại.
              updateIntervalTree(..., L[chainHead[uchain]], L[u], ...);
            // Nhảy lên đỉnh cha của đỉnh đầu hiện tại.
              u = parent[chainHead[uchain]];
              uchain = chainInd[u];
         }
    }
}
{
    //IT, Segment Tree, Lazy
    int IT[maxN], lazy[maxN];

    void build(int i, int L, int R) {
        lazy[i] = -1;
        IT[i] = 0;
        if (L == R) return;
        int mid = (L + R) >> 1;
        build(i << 1, L, mid);
        build(i << 1 | 1, mid + 1, R);
    }

    void push(int i, int L, int R) {
        if (lazy[i] == -1) return;
        IT[i] = lazy[i] * (R - L + 1);
        if (L != R) {
            lazy[i << 1] = lazy[i];
            lazy[i << 1 | 1] = lazy[i];
        }
        lazy[i] = -1;
    }

    ///update: a(i) = val for all i: u <= i <= v
    void update(int i, int L, int R, int u, int v, int val) {
        push(i, L, R);
        if (L > v || R < u) return;
        if (L >= u && R <= v) {
            lazy[i] = val;
            push(i, L, R);
            return;
        }
        int mid = (L + R) >> 1;
        update(i << 1, L, mid, u, v, val);
        update(i << 1 | 1, mid + 1, R, u, v, val);
        IT[i] = IT[i << 1] + IT[i << 1 | 1];
    }

    int get(int i, int L, int R, int u, int v) {
        push(i, L, R);
        if (L > v || R < u) return 0;
        if (L >= u && R <= v) return IT[i];
        int mid = (L + R) >> 1;
        int left = get(i << 1, L, mid, u, v);
        int right = get(i << 1 | 1, mid + 1, R, u, v);
        return left + right;
    }
}
{
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

}
{
    ///IT Line: Max y = ax + b;
    struct Line {
        ///y = a * x + b;
        long long a, b;
        Line(){};
        Line(long long _a, long long _b) {
            a = _a;
            b = _b;
        }
    };

    Line IT[maxN * 4];
    vector<long long> realX; ///maybe not used
    long long get(Line L, int x) {
        if (L.a == 0 && L.b == 0) return -INF_LL;
        return L.a * realX[x] + L.b;
    }
    void update(int i, int L, int R, int u, int v, Line val) {
        if (L > v || R < u) return;
        int mid = (L + R) >> 1;
        if (L >= u && R <= v) {
            if (get(IT[i], L) >= get(val, L) && get(IT[i], R) >= get(val, R)) return;
            if (get(IT[i], L) <= get(val, L) && get(IT[i], R) <= get(val, R)) {
                IT[i] = val;
                return;
            }
            if (get(IT[i], L) >= get(val, L) && get(IT[i], mid) >= get(val, mid)) {
                update(i << 1 | 1, mid + 1, R, u, v, val);
                return;
            }
            if (get(IT[i], L) <= get(val, L) && get(IT[i], mid) <= get(val, mid)) {
                update(i << 1 | 1, mid + 1, R, u, v, IT[i]);
                IT[i] = val;
                return;
            }
            if (get(IT[i], mid + 1) >= get(val, mid + 1) && get(IT[i], R) >= get(val, R)) {
                update(i << 1, L, mid, u, v, val);
                return;
            }
            if (get(IT[i], mid + 1) <= get(val, mid + 1) && get(IT[i], R) <= get(val, R)) {
                update(i << 1, L, mid, u, v, IT[i]);
                IT[i] = val;
                return;
            }
        }
        update(i << 1, L, mid, u, v, val);
        update(i << 1 | 1, mid + 1, R, u, v, val);
    }
    long long get(int i, int L, int R, int x)
    {
        if (L > x || R < x) return -INF_LL;
        if (L >= x && R <= x) return get(IT[i], x);
        int mid = (L + R) >> 1;
        long long left = get(i << 1, L, mid, x);
        long long right = get(i << 1 | 1, mid + 1, R, x);
        return max(max(left,right), get(IT[i], x));
    }
}
{
    ///Pisano periods (or Pisano numbers): period of Fibonacci numbers mod n.
    ///n <= 10^12
    ///https://oeis.org/A001175
    struct matrix {
        long long c[2][2];
        void init() {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) c[i][j] = 0;
            }
        }
    };
    long long Mul(long long x, long long y,long long m) /// Tinh (x * y) mod M voi (x,y, M <= 10 ^ 18)
    {
        x %= m; y %= m;
        long long q = (long double) x * y / m;
        long long r = (x * y - q * m) % m;
        if (r < 0) r += m;
        return r;
    }
    struct Fibo {
        long long module;
        Fibo(long long _module = 0) : module(_module) {};
        matrix nhan(matrix a,matrix b) {
            matrix C;
            C.init();
            for (int k = 0; k < 2; k++) {
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        long long val = Mul(a.c[i][k], b.c[k][j], module);
                        C.c[i][j] = (C.c[i][j] + val) % module;
                    }
                }
            }
            return C;
        }
        matrix Get(long long n) {
            matrix a;
            a.c[0][0] = 0; a.c[0][1] = 1;
            a.c[1][0] = 1; a.c[1][1] = 1;
            matrix Res;
            Res.init();
            for (int i = 0; i < 2; i++) Res.c[i][i] = 1;
            for (; n; n = n >> 1, a = nhan(a,a)) {
                if (n & 1) Res = nhan(Res,a);
            }
            return Res;
        }
    };
    long long F(long long n, long long m) {
        if (n == 0) return 0;
        Fibo fb(m);
        long long fn = fb.Get(n).c[0][1];
        return fn;
    }
    long long pisano_prime_brute(int p) {
        int f0 = 0, f1 = 1;
        for (long long sz = 2; ; sz++) {
            int f2 = f0 + f1;
            if (f2 >= p) f2 -= p;
            if (f1 == 0 && f2 == 1) {
                return sz - 1;
            }
            f0 = f1;
            f1 = f2;
        }
    }
    vector<int> factors(int p) {
        vector<int> res;
        for (int i = 1; i * i <= p; i++) {
            if (p % i == 0) {
                res.push_back(i);
                res.push_back(p / i);
            }
        }
        sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());
        return res;
    }
    bool isPower(int n, int p) {
        while (n % p == 0) n /= p;
        return n == 1;
    }
    long long pisano_prime(int p) {
        if (isPower(p, 2)) return 1LL * p * 3 / 2;
        if (isPower(p, 5)) return 1LL * p * 4;
        if (p % 5 == 1 || p % 5 == 4) {
            vector<int> factor = factors(p - 1);
            for (int n : factor) {
                long long c = F(n, p);
                long long d = F(n + 1, p);
                if (c == 0 && d == 1) return n;
            }
        }
        else {
            vector<int> factor = factors(2 * p + 2);
            for (int n : factor) {
                long long c = F(n, p);
                long long d = F(n + 1, p);
                if (c == 0 && d == 1) return n;
            }
        }
        return 0;
    }
    long long gcd(long long x, long long y) {
        return y == 0 ? x : gcd(y, x % y);
    }
    long long lcm(long long x, long long y) {
        return x / gcd(x, y) * y;
    }
    long long pisano(int n) {
        vector<pair<int, int> > primes;
        int x = n;
        for (int i = 2; i * i <= x; i++) {
            if (n % i == 0) {
                int d = 0;
                while (n % i == 0) {
                    n /= i;
                    d++;
                }
                primes.push_back({i, d});
            }
        }
        if (n > 1) {
            primes.push_back({n, 1});
        }
        long long res = 1;
        for (auto it : primes) {
            int p = it.first;
            int w = it.second;
            long long cost = 1;
            for (int i = 1; i < w; i++) cost *= p;
            cost *= pisano_prime(p);
            res = lcm(res, cost);
        }
        return res;
    }
}
{
    ///minimum enclosing circle O(N)
    ///https://www.geeksforgeeks.org/minimum-enclosing-circle-set-2-welzls-algorithm/
    struct Point {
        double x, y;
        Point(){};
        Point(double _x, double _y) : x(_x), y(_y) {};
        Point(const Point &A) : x(A.x), y(A.y) {};
        int operator < (const Point &A) {
            return make_pair(x, y) < make_pair(A.x, A.y);
        }
        int operator == (const Point &A) {
            return make_pair(x, y) == make_pair(A.x, A.y);
        }
    };

    struct Circle {
        Point center;
        double r;
        Circle(){};
        Circle(double _x, double _y, double _r) : center(Point(_x, _y)), r(_r) {};
        Circle(Point _center, double _r) : center(_center), r(_r) {};
        Circle(const Circle &A) : center(A.center), r(A.r) {};
        int operator < (const Circle &A) {
            return r < A.r;
        }
    };

    double dist(Point A, Point B) {
        double x = A.x - B.x;
        double y = A.y - B.y;
        return sqrtl(x * x + y * y);
    }

    bool inSide(Point A, Circle C) {
        return dist(A, C.center) <= C.r;
    }

    Point get_circle_center(double bx, double by,
                            double cx, double cy)
    {
        double B = bx * bx + by * by;
        double C = cx * cx + cy * cy;
        double D = bx * cy - by * cx;
        return { (cy * B - by * C) / (2 * D),
                 (bx * C - cx * B) / (2 * D) };
    }

    Circle circle_three(Point A, Point B, Point C) {
        Point O = get_circle_center(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);
        O.x += A.x;
        O.y += A.y;
        return Circle(O, dist(O, A));
    }

    Circle circle_two(Point A, Point B) {
        Point O = Point((A.x + B.x) / 2.0, (A.y + B.y) / 2.0);
        return Circle(O, dist(A, B) / 2.0);
    }

    bool check_valid_circle(Circle C, vector<Point> p) {
        for (Point A : p) {
            if (!inSide(A, C)) return false;
        }
        return true;
    }

    // Function to return the minimum enclosing circle for N <= 3
    Circle MEC_small(vector<Point> p) {
        assert((int)p.size() <= 3);
        if (p.empty()) return Circle(Point(0, 0), 0);
        if ((int)p.size() == 1) return Circle(p[0], 0);
        if ((int)p.size() == 2) return circle_two(p[0], p[1]);

        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                Circle C = circle_two(p[i], p[j]);
                if (check_valid_circle(C, p)) return C;
            }
        }
        Circle res = circle_three(p[0], p[1], p[2]);
        return res;
    }

    Circle welzl_helper(vector<Point>& P, vector<Point> R, int n)
    {
        if (n == 0 || R.size() == 3) {
            return MEC_small(R);
        }

        int idx = rng() % n;
        Point p = P[idx];

        swap(P[idx], P[n - 1]);

        Circle C = welzl_helper(P, R, n - 1);

        if (inSide(p, C)) {
            return C;
        }

        R.push_back(p);

        return welzl_helper(P, R, n - 1);
    }

    ///minimum enclosing circle O(N)
    Circle MEC(vector<Point> p) {
        int n = (int)p.size();
        random_shuffle(p.begin(), p.end());
        return welzl_helper(p, {}, n);
    }

    ///minimum enclosing circle O(N)
    Circle get(vector<double> &x, vector<double> &y) {
        int n = (int)x.size();
        vector<Point> p(n);
        for (int i = 0; i < n; i++) p[i] = Point(x[i], y[i]);
        return MEC(p);
    }

}
{
    ///Gen Convex Full, N <= 4 x 10^5, x, y <= 4 x 10^7
    #include <bits/stdc++.h>
    using namespace std;

    #define MAXN 500000
    #define pb push_back
    #define all(v) (v).begin(), (v).end()
    typedef long long lld;

    int N;
    int stk[MAXN], scnt;

    struct Z{
        int x, y;
    } A[MAXN];

    int ccw(int ax, int ay, int bx, int by, int cx, int cy)
    {
        lld k = (lld)(bx - ax) * (cy - ay) - (lld)(cx - ax) * (by - ay);
        if (k > 0) return 1;
        if (k) return -1;
        return 0;
    }

    int ccw(Z a, Z b, Z c){ return ccw(a.x, a.y, b.x, b.y, c.x, c.y); }

    int gcd(int a, int b){ return b ? gcd(b, a%b) : a; }

    int main()
    {
        vector <Z> frac;
        for (int i=2;i<999;i++){
            for (int j=1;j<i;j++) if (gcd(i, j) == 1){
                frac.pb({i, j});
            }
        }
        sort(all(frac), [](const Z &a, const Z &b){
            return a.x+a.y < b.x+b.y;
        });
        int sum = 0;
        vector <Z> lst;
        for (Z &z: frac){
            sum += z.x + z.y;
            if (sum > 20000000) break;
            lst.pb(z);
        }
        sort(all(lst), [](const Z &a, const Z &b){
            return (lld)a.y * b.x < (lld)b.y * a.x;
        });
        auto lst2 = lst;
        reverse(all(lst2));
        int x = 20000000, y = 0;
        for (Z &z: lst){
            A[++N] = {x, y};
            x += z.x, y += z.y;
        }
        for (Z &z: lst2){
            A[++N] = {x, y};
            x += z.y, y += z.x;
        }
        for (Z &z: lst){
            A[++N] = {x, y};
            x -= z.y, y += z.x;
        }
        for (Z &z: lst2){
            A[++N] = {x, y};
            x -= z.x, y += z.y;
        }
        for (Z &z: lst){
            A[++N] = {x, y};
            x -= z.x, y -= z.y;
        }
        for (Z &z: lst2){
            A[++N] = {x, y};
            x -= z.y, y -= z.x;
        }
        for (Z &z: lst){
            A[++N] = {x, y};
            x += z.y, y -= z.x;
        }
        for (Z &z: lst2){
            A[++N] = {x, y};
            x += z.x, y -= z.y;
        }
        /* Get convex hull for cross checking */
        for (int i=2;i<=N;i++)
            if (A[1].y > A[i].y || A[1].y == A[i].y && A[1].x > A[i].x)
                swap(A[1], A[i]);
        sort(A+2, A+N+1, [](const Z &a, const Z &b){
            int k = ccw(A[1], a, b);
            if (k) return k > 0;
            return abs(a.x-A[1].x)+abs(a.y-A[1].y) < abs(b.x-A[1].x)+abs(b.y-A[1].y);
        });
        stk[scnt=1] = 1;
        for (int i=2;i<=N;i++){
            while (scnt > 1 && ccw(A[stk[scnt-1]], A[stk[scnt]], A[i]) <= 0) scnt--;
            stk[++scnt] = i;
        }
        if (N != scnt) return 0;
        scanf("%d", &N);
        for (int i=1;i<=N;i++) printf("%d %d\n", A[i].x, A[i].y);
    }
}
{
    int D[maxN];
    int b[maxN][20];
    long long F[maxN];
    typedef pair<int, int> i2;
    vector<i2> adj[maxN];
    void DFS(int u, int pa) {
        for (int i = 0; i <= 18; i++) {
            int v = b[u][i];
            if (v == 0) break;
            b[u][i + 1] = b[v][i];
        }
        for (auto [v, w] : adj[u]) {
            if (v != pa) {
                D[v] = D[u] + 1;
                F[v] = F[u] + w;
                b[v][0] = u;
                DFS(v, u);
            }
        }
    }

    int LCA(int u, int v) {
        if (D[u] < D[v]) swap(u, v);
        int k = D[u] - D[v];
        for (int i = 18; i >= 0; i--) {
            if (k >= (1 << i)) {
                k -= (1 << i);
                u = b[u][i];
            }
        }
        if (u == v) return u;
        int res = 0;
        for (int i = 18; i >= 0; i--) {
            if (b[u][i] != b[v][i]) {
                u = b[u][i];
                v = b[v][i];
            }
            else res = b[u][i];
        }
        return res;
    }
}
struct Manacher {
    string s;
    int n;
    vector<int> d1, d2;
    Manacher(){};
    Manacher(string _s) {
        s = _s;
        n = (int)s.size();
        d1 = vector<int>(n, 0);
        d2 = vector<int>(n, 0);
    }

    void calc() {
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
                k++;
            }
            d1[i] = k--;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
            while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
                k++;
            }
            d2[i] = k--;
            if (i + k > r) {
                l = i - k - 1;
                r = i + k ;
            }
        }
    }

    int getLenPalindrome(int root) {
        return max(d1[root] * 2 - 1, d2[root] * 2);
    }
};
namespace FFT {
    long long mo=998244353;
    long long modpow(long long a, long long n = mo-2) {
        long long r = 1;
        while(n) r = r * ((n % 2) ? a : 1) % mo, a = a*a%mo, n>>=1;
        return r;
    }
    vector<long long> fft(vector<long long> v, bool rev=false) {
        int n=v.size(), i, j, m;

        for(i=0, j=1; j<n-1; j++) {
            for(int k=n>>1; k>(i^=k); k>>=1);
            if(i>j) swap(v[i], v[j]);
        }
        for(int m=2; m<=n; m*=2) {
            long long wn=modpow(5,(mo-1)/m);
            if(rev) wn=modpow(wn);
            for(i=0; i<n; i+=m) {
                long long w=1;
                for(int j1=i, j2=i+m/2; j2<i+m; j1++, j2++) {
                    long long t1=v[j1],t2=w*v[j2]%mo;
                    v[j1]=t1+t2;
                    v[j2]=t1+mo-t2;
                    while(v[j1]>=mo) v[j1]-=mo;
                    while(v[j2]>=mo) v[j2]-=mo;
                    w=w*wn%mo;
                }
            }
        }
        if(rev) {
            long long rv = modpow(n);
            for (int i = 0; i < n; i++) v[i] = v[i] * rv % mo;
        }
        return v;
    }

    vector<long long> MultPoly(vector<long long> P, vector<long long> Q, bool resize=true) {
        if(resize) {
            int maxind = 0, pi = 0, qi = 0, i;
            int s = 2;
            for (int i = 0; i < (int)P.size(); i++) if(P[i]) pi=i;
            for (int i = 0; i < (int)Q.size(); i++) if(Q[i]) qi=i;
            maxind = pi + qi + 1;
            while(s*2 < maxind) s *= 2;
            P.resize(s*2); Q.resize(s*2);
        }
        P=fft(P), Q=fft(Q);
        for(int i=0; i < P.size(); i++) P[i]=P[i]*Q[i]%mo;
        return fft(P,true);
    }
}

int min_rotation(string s) {
    int a = 0, N = (int)s.size();
    for (int b = 0; b < N; b++) {
        for (int i = 0; i < N; i++) {
            if (a + i == b || s[(a + i) % N] < s[(b + i) % N]) {
                b += max(0, i - 1);
                break;
            }
            if (s[(a + i) % N] > s[(b + i) % N]) {
                a = b;
                break;
            }
        }
    }
    return a;
};

void Zfunction(int z[], string s) {
    int n = (int)s.size();
    for (int i = 1; i <= n; i++) z[i] = 0;
    int L = 1, R = 1;
    for (int i = 2; i <= n; i++) {
        if (i <= R) z[i] = min(z[i - L + 1], R - i + 1);
        while (i + z[i] <= n && s[z[i]] == s[i + z[i] - 1]) z[i]++;
        if (i + z[i] - 1 > R) {
            L = i;
            R = i + z[i] - 1;
        }
    }
}

template<typename T>
struct FenwickTree_2D{
    vector<vector<T> > fenwick;
    int N, M;
    FenwickTree_2D(){};
    FenwickTree_2D(int _N, int _M) {
        N = _N;
        M = _M;
        fenwick = vector<vector<T> >(N + 1, vector<T>(M + 1, 0));
    }

    void updateY(int x, int y, T val) {
        for (; y <= M; y += y & (-y)) fenwick[x][y] += val;
    }

    void updateX(int x, int y, T val) {
        for (; x <= N; x += x & (-x)) updateY(x, y, val);
    }

    T sumY(int x, int y) {
        T res = 0;
        for (; y; y -= y & (-y)) res += fenwick[x][y];
        return res;
    }
    T sumX(int x, int y) {
        T res = 0;
        for (; x; x -= x & (-x)) res += sumY(x, y);
        return res;
    }

    T get(int xL, int yL, int xR, int yR) {
        return sumX(xR, yR) - sumX(xL - 1, yR) - sumX(xR, yL - 1) + sumX(xL - 1, yL - 1);
    }
};

template<typename T>
struct sum_2D {
    int n, m;
    vector<vector<T> > a;
    sum_2D(int _n, int _m) {
        n = _n;
        m = _m;
        a = vector<vector<T> >(n + 1, vector<T>(m + 1, 0));
    }

    void set_value(int x, int y, T value) {
        a[x][y] = value;
    }

    void precalc() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) a[i][j] += a[i - 1][j]  + a[i][j - 1] - a[i - 1][j - 1];
        }
    }

    T get(int xL ,int yL, int xR, int yR) {
        return a[xR][yR] - a[xL - 1][yR] - a[xR][yL - 1] + a[xL - 1][yL - 1];
    }
};
struct Edge {
    int u, v;
    int c, f; ///if flow > int, use long long
    Edge(){};
    Edge(int _u, int _v, int _c, int _f) : u(_u), v(_v), c(_c), f(_f) {};
};
struct Ford_FulkersonFlow{ ///Base 0-th, The vertices are numbered from 0 to n - 1
    const int oo = 2e9; ///if flow > int, use long long
    vector <Edge> E;
    int n, numEdge;
    vector <vector<int> > adj; ///adj[u]: set index Edge u -> v
    vector <int> Trace_Edge; ///Trace_Edge[v]: index Edge u -> v in Argument Flow

    Ford_FulkersonFlow(int _n = 0) {
        n = _n; numEdge = 0;
        adj.resize(n);
        Trace_Edge.assign(n, -1);
    }

    void add_Edge(int u, int v, int c1, int c2) { ///if flow > int, use long long c1, c2
        ///u -> v: c1
        adj[u].push_back(numEdge);
        E.push_back(Edge(u, v, c1, 0));
        numEdge++;
        ///v -> u: c2
        adj[v].push_back(numEdge);
        E.push_back(Edge(v, u, c2, 0));
        numEdge++;
    }

    bool BFS(int s, int t) { ///check has path from s to t
        for (int i = 0; i < n; i++) Trace_Edge[i] = -1;
        queue <int> Q;
        Q.push(s);

        while ((int)Q.size() != 0) {
            int u = Q.front(); Q.pop();
            for (int id : adj[u]) {
                int v = E[id].v;
                if (E[id].f < E[id].c && Trace_Edge[v] == -1) {
                    Trace_Edge[v] = id; ///Trace_Edge[v] = index numberEdge: u -> v, be careful it's not v -> u
                    Q.push(v);
                    if (v == t) return true;
                }
            }
        }
        return false;
    }

    void ArgumentFlow(int s, int t) {
        int u = t;
        int Delta = oo;
        while (u != s) {
            int id = Trace_Edge[u];
            Delta = min(Delta, E[id].c - E[id].f);
            u = E[id].u;
        }

        u = t;
        while (u != s) {
            int id = Trace_Edge[u];
            E[id].f += Delta;
            E[id ^ 1].f -= Delta;
            u = E[id].u;
        }
    }

    int maxFlow(int s, int t) {
        while (BFS(s, t)) ArgumentFlow(s, t);
        int ResFlow = 0;
        for (int id : adj[s])
            ResFlow += E[id].f;
        return ResFlow;
    }

    int GetFlow(int idEdge) {
        return E[idEdge].f;
    }
};
struct DinicFlow { ///Base 0-th, The vertices are numbered from 0 to n - 1
    const int oo = 2e9; ///if flow > int, use long long
    int n, numEdge;
    vector <int> point, next, head, Dist, work;
    vector <int> flow, cap; ///if flow > int, use long long

    DinicFlow(int _n = 0) {
        n = _n; numEdge = 0;
        head.assign(n + 7, -1);
        work.assign(n + 7, -1);
        Dist.assign(n + 7, 0);
    }

    void add_Edge(int u, int v, int c1, int c2 = 0) {///if flow > int, use long long c1, c2
        ///u -> v: c1
        point.push_back(v); flow.push_back(0); cap.push_back(c1); next.push_back(head[u]); head[u] = numEdge++;
        ///v -> u: c2
        point.push_back(u); flow.push_back(0); cap.push_back(c2); next.push_back(head[v]); head[v] = numEdge++;
    }

    bool BFS(int s, int t) { ///check has path from s to t
        queue <int> Q;
        for (int i = 0; i <= n; i++) Dist[i] = -1;
        Dist[s] = 0;
        Q.push(s);
        while ((int)Q.size() != 0) {
            int u = Q.front(); Q.pop();
            for (int i = head[u]; i >= 0; i = next[i]) {
                int v = point[i];
                if (flow[i] < cap[i] && Dist[v] == -1) {
                    Dist[v] = Dist[u] + 1;
                    if (v == t) return true;
                    Q.push(v);
                }
            }
        }
        return false;
    }

    int DFS(int s, int t, int f) { ///if flow > int, use long long
        if (f == 0) ///Min F always >= 0 so if f = 0 break recursive
            return f;
        if (s == t)
            return f;
        for (int &i = work[s]; i >= 0; i = next[i]) { ///&i so important, don't use i = work[s] because it's maybe TLE
            int v = point[i];
            if (flow[i] < cap[i] && Dist[v] == Dist[s] + 1) {
                int D = DFS(v, t, min(f, cap[i] - flow[i]));
                if (D > 0) {
                    flow[i] += D;
                    flow[i ^ 1] -= D;
                    return D;
                }
            }
        }
        return 0;
    }

    int maxFlow(int s, int t) { ///if flow > int, use long long
        int Flow = 0;
        while (BFS(s, t)) {
            for (int i = 0; i <= n; i++) work[i] = head[i];
            while (true) {
                int d = DFS(s, t, oo);
                if (d == 0) break;
                Flow += d;
            }
        }
        return Flow;
    }

    int GetFlow(int idEdge) {
        return flow[idEdge];
    }
};
struct LucasTheorem { ///calculate nCk mod module with n, k is large number ~ 10^18, module is small number ~ 10^6
    long long mod;
    vector<long long> fact, inv_fact;
    const int limits = 4;
    LucasTheorem(long long _mod) {
        mod = _mod;
        fact.assign(mod + 7, 0);
        inv_fact.assign(mod + 7, 0);
        fact[0] = 1;
        for (int i = 1; i < mod; i++) {
            fact[i] = fact[i - 1] * i % mod;
        }
        inv_fact[mod - 1] = inverse(fact[mod - 1]);
        for (int i = mod - 2; i >= 0; i--) {
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % mod;
        }
    }
    long long power(long long b, long long e) {
        long long res = 1;
        b %= mod;
        for (; e; e >>= 1, b = b * b % mod) {
            if (e & 1) res = res * b % mod;
        }
        return res;
    }

    long long inverse(long long a) {
        return power(a, mod - 2);
    }
    vector<int> modRepresent(long long n) {
        vector<int> res;
        while (n) {
            res.push_back(n % mod);
            n /= mod;
        }
        while (res.size() < limits) res.push_back(0);
        return res;
    }
    long long nCk(long long n, long long k) {
        if (k > n) return 0;
        long long res = fact[n] * inv_fact[k] % mod;
        res = res * inv_fact[n - k] % mod;
        return res;
    }
    long long mod_nCk(long long n, long long k) {
        vector<int> repN = modRepresent(n);
        vector<int> repK = modRepresent(k);
        long long res = 1;
        for (int i = 0; i < limits; i++) {
            res = res * nCk(repN[i], repK[i]) % mod;
        }
        return res;
    }
};

template<typename T>
struct FenwickTree{
    vector<T> fenwick;
    int N;
    FenwickTree(){};
    FenwickTree(int _N) {
        N = _N;
        fenwick = vector<T>(N + 1, 0);
    }

    void update(int x, T val) {
        for (; x <= N; x += x & (-x)) fenwick[x] += val;
    }

    T sum(int x) {
        T res = 0;
        for (; x; x -= x & (-x)) res += fenwick[x];
        return res;
    }

    T get(int L, int R) {
        return sum(R) - sum(L - 1);
    }
};
struct SuffixArray {
    const int L;
    string s;
    vector<vector<int> > P;
    vector<pair<pair<int,int>,int> > M;
    ///P[k][i] = P[k][j] neu xau bat dau tu i co do dai 2^k = xau bat dau tu j co do dai 2^k
    SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L) {
        for (int i = 0; i < L; i++) P[0][i] = int(s[i]);
        if (L == 1) P[0][0] = 0; ///very important :)))), otherwise it may cause an error when L = 1

        for (int skip = 1, level = 1; skip < L; skip *= 2, level++) {
            P.push_back(vector<int>(L, 0));
            for (int i = 0; i < L; i++)
                M[i] = make_pair(make_pair(P[level-1][i], i + skip < L ? P[level-1][i + skip] : -1000), i);
            sort(M.begin(), M.end());
            for (int i = 0; i < L; i++)
                P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
        }
    }
    vector<int> GetSuffixArray() { return P.back(); }
    // returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
    int LongestCommonPrefix(int i, int j) {
        int len = 0;
        if (i == j) return L - i;
        for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--) {
            if (P[k][i] == P[k][j]) {
                i += 1 << k;
                j += 1 << k;
                len += 1 << k;
            }
        }
        return len;
    }};


struct MaxBipartiteMatching { ///base 1th; X -> Y
    int n, m;
    vector <int> link, match, stk, Used;
    bool Found;
    vector <vector<int> > adj;
    MaxBipartiteMatching(){};
    MaxBipartiteMatching(int _n, int _m) {
        n = _n; ///Size(X)
        m = _m; ///Size(Y)
        link.assign(n + 7, 0); ///X
        match.assign(m + 7, 0); ///match[y] = x, if have x -> y in MaxBipartiteMatching or 0 if not
        Used.assign(m + 7, 0);
        stk.clear();
        adj.resize(n + 7);
    }

    void addEdge(int u, int v) { ///u in X and v in Y
        adj[u].push_back(v);
    }

    void DFS(int u) {
        for (int v : adj[u]) {
            if (Used[v] == 0) {
                Used[v] = 1;
                stk.push_back(v);
                if (match[v] == 0) Found = true;
                else DFS(match[v]);
                if (Found) {
                    match[v] = u;
                    return;
                }
            }
        }
    }

    int getCost() { ///get size MaxBipartiteMatching
        int Nlink = n;
        for (int i = 1; i <= n; i++) link[i] = i;
        for (int i = 1; i <= m; i++) match[i] = 0;
        int old;
        do {
            old = Nlink;
            for (int x : stk) Used[x] = 0;
            stk.clear();
            for (int i = Nlink; i >= 1; i--) {
                Found = false;
                DFS(link[i]);
                if (Found) {
                    link[i] = link[Nlink--];
                }
            }
        }
        while (old != Nlink);
        return n - old;
    }

    int getX(int y) { ///match[y] = x, if have x -> y in MaxBipartiteMatching or 0 if not
        return match[y];
    }
};

struct Trie_Binary{
    vector <vector<int> > T;
    vector <bool> End;
    int numNode;
    int cap, Base;
    Trie_Binary(){};
    Trie_Binary(int maxN, int _Base) {
        cap = maxN;
        Base = _Base; ///limits length bits = Base
        numNode = 0;
        T = vector<vector<int> > (cap, vector<int>(2, 0));
        End = vector<bool> (cap, false); ///End[u] = true if we has a complete number in Node u
    }

    int getBit(int x, int idx) {
        return (x >> idx) & 1;
    }

    int reverseBit(int x, int idx) {
        return x ^ (1 << idx);
    }

    void add(int x) {
        int root = 0;
        for (int i = Base - 1; i >= 0; i--) {
            int bit = getBit(x, i);
            if (T[root][bit] == 0) T[root][bit] = ++numNode;
            root = T[root][bit];
            assert(root < cap);
        }
        End[root] = true;
    }

    bool find(int x) { ///if we have a number = x then return true, else return false
        int root = 0;
        for (int i = Base - 1; i >= 0; i--) {
            int bit = getBit(x, i);
            if (T[root][bit] == 0) return false;
            root = T[root][bit];
        }
        return End[root];
    }
    ///add method
};

struct Trie_String{
    vector <vector<int> > T;
    vector <bool> End;
    int numNode;
    int cap, Base;
    Trie_String(){};
    Trie_String(int maxN, int _Base) {
        cap = maxN;
        Base = _Base;
        numNode = 0;
        T = vector<vector<int> > (cap, vector<int>(Base, 0));
        End = vector<bool> (cap, false); ///End[u] = true if we has a complete string in Node u
    }

    void add(string s) {
        int root = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            int c = s[i] - 'a'; ///change if s not contain only alphabet
            assert(c >= 0 && c < Base);
            if (T[root][c] == 0) T[root][c] = ++numNode;
            root = T[root][c];
            assert(root < cap);
        }
        End[root] = true;
    }

    bool find(string s) { ///if we have a complete string t = s then return true, else return false
        int root = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            int c = s[i] - 'a'; ///change if s not contain only alphabet
            assert(c >= 0 && c < Base);
            if (T[root][c] == 0) return false;
            root = T[root][c];
        }
        return End[root];
    }

    bool findPrefix(string s) { ///if we have a complete string t so s is the prefix in t then return true, else return false
        int root = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            int c = s[i] - '0';
            if (T[root][c] == 0) return false;
            root = T[root][c];
        }
        return true;
    }

    ///add method
};
struct DisjointSetUnion { ///Base 1th or Base 0th
    ///if u is root then p[u] < 0 and |p[u]| is size of the Set that u is root
    ///if u is not root then p[u] = x and x, u are belong the same Set
    int n;
    vector <int> p;
    DisjointSetUnion(){};
    DisjointSetUnion(int _n) {
        n = _n;
        p.assign(n + 7, -1); ///p[i] = -1 for all i
    }

    int find_root(int u) { ///find the root in the Set contain u
        if (p[u] < 0) return u; ///u is root
        return p[u] = find_root(p[u]); ///get the root and jump
    }

    void Union(int u, int v) {
        int x = find_root(u);
        int y = find_root(v);
        if (x == y) return;
        if (p[x] > p[y]) swap(x, y); ///small Set point to big Set, p[x] > p[y] so |p[x]| < |p[y]|
        p[x] += p[y];
        p[y] = x;
    }

    bool sameSet(int u, int v) {
        return find_root(u) == find_root(v);
    }

    int numSet() {
        int res = 0;
        for (int i = 1; i <= n; i++) res += p[i] < 0;
        return res;
    }
};
vector<vector<int> > splitRandomArray(vector<int> arr, int sz) {
    vector <int> id;
    set <int> Used;
    int n = (int)arr.size();
    for (int i = 0; i < sz - 1; i++) {
        while (true) {
            int id = rand() % n;
            if (Used.find(id) != Used.end()) continue;
            id.push_back(id);
            Used.insert(id);
        }
    }
    id.push_back(n - 1);
    sort(id.begin(), id.end());
    id.resize(unique(id.begin(), id.end()) - id.begin());
    vector<vector<int> > res;
    int L = 0;
    for (int i = 0; i < (int)id.size() - 1; i++) {
        vector <int> a;
        int R = id[i];
        while (L <= R) a.push_back(arr[L++]);
        res.push_back(a);
    }
    return res;
}

vector<vector<int> > genTree(vector <int> vertice) {
    random_shuffle(vertice.begin(), vertice.end());
    int n = (int)vertice.size();
    vector <int> p(n);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin(), p.end(), rnd);
    vector <vector<int> > res;
    for (int i = 1; i < n; i++) {
        int j = rand() % i;
        res.push_back({vertice[j], vertice[i]});
    }
    return res;
}
vector<vector<int> > genConnectedGraph(int n, int m) {
    vector <int> vertice(n);
    iota(vertice.begin(), vertice.end(), 1) ///change 0 if base 0th
    vector<vector<int> > res = genTree(vertice);
    for (int i = n; i <= m; i++) {
        while (true) {
            int u = rnd() % n + 1;
            int v = rnd() % n + 1;
            if (u != v) {
                res.push_back({u, v});
                break;
            }
        }
    }
    return res;
}
{
    ///Palindrome
    long long pw[19] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000LL, 100000000000LL, 1000000000000LL, 10000000000000LL, 100000000000000LL, 1000000000000000LL, 10000000000000000LL, 100000000000000000LL, 1000000000000000000LL};
    long long F(int size, int type = 0) {
        if (size <= 0) return 1;
        return pw[(size - 1) / 2] * (9 + type);
    }
    long long GetPalindrome(int K) { ///tìm số Palindrome thứ K (1, 2, 3, ..., 9, 11, 22, 33, ...)
        if (K < 10) return K;
        int n = 1;
        while (true) {
            long long val = F(n);
            if (val >= K) break;
            K -= val;
            n += 1;
        }
        int tmp = n;
        vector <int> value;
        for (int sl = 1; sl <= n / 2; sl++) {
            for (int i = (sl == 1 ? 1 : 0); i < 10; i++) {
                int val = F(tmp - 2, 1);
                if (K > val) K -= val;
                else {
                    value.push_back(i);
                    tmp -= 2;
                    break;
                }
            }
        }
        long long res = 0;
        for (int x : value) res = res * 10 + x;
        if (n & 1) res = res * 10 + (K - 1);
        reverse(value.begin(), value.end());
        for (int x : value) res = res * 10 + x;
        return res;
    }
}
{
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    long long F(int p, int q, int n) { ///Tinh tổng floor(p * i / q) với i từ 1 đến n và p < q
        if (p == 0) return 0;
        long long res = n / (q / gcd(p, q));
        long long val = 1LL * n * p / q;
        res += val * n;
        res -= val * (val + 1) / 2 * (q / p);
        return res - F(q % p, p, val);
    }
    ///problem:https://open.kattis.com/problems/itsamodmodmodmodworld
    void sol() {
        int p, q, n;
        cin >> p >> q >> n;
        p %= q;
        long long res = 1LL * p * n * (n + 1) / 2;
        res -= F(p, q, n) * q;
        cout << res << '\n';
    }
}
long long Inverse(long long a,long long MOD) /// Tinh (1 / a) mod MOD
                   /// Tinh (a ^ (-1)) mod MOD
{
    long long m = a, n = MOD;
    long long xm = 1, xn = 0;
    while (n != 0)
    {
        long long q = m / n;
        long long r = m - q * n;
        long long xr = xm - q * xn;
        m = n; xm = xn;
        n = r; xn = xr;
    }
    return (xm % MOD + MOD) % MOD;
}

long long Mul(long long x, long long y,long long m) /// Tinh (x * y) mod M voi (x,y, M <= 10 ^ 18)
{
    x %= m; y %= m;
    long long q = (long double) x * y / m;
    long long r = (x * y - q * m) % m;
    if (r < 0) r += m;
    return r;
}
class Fibo {
public:
    struct matrix {
        int c[2][2];
        void init() {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) c[i][j] = 0;
            }
        }
    };
    matrix nhan(matrix a,matrix b) {
        matrix C;
        C.init();
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    int Val = 1LL * a.c[i][k] * b.c[k][j] % module;
                    C.c[i][j] += Val;
                    while (C.c[i][j] >= module) C.c[i][j] -= module;
                }
            }
        }
        return C;
    }
    matrix Get(long long n) {
        matrix a;
        a.c[0][0] = 0; a.c[0][1] = 1;
        a.c[1][0] = 1; a.c[1][1] = 1;
        matrix Res;
        Res.init();
        for (int i = 0; i < 2; i++) Res.c[i][i] = 1;
        for (; n; n = n >> 1, a = nhan(a,a)) {
            if (n & 1) Res = nhan(Res,a);
        }
        return Res;
    }
    void Print(matrix A) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                cout << A.c[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};
void sang(int N) {
    for (int i = 2; i <= N; i++) {
        p[i] = i;
    }
    for (int i = 2; i <= N; i++) {
        if (p[i] == i) {
            for (int j = 1; j * i <= N; j++) {
                p[i * j] = i;
            }
        }
    }
}
void tach(int X,int Type) {
    for (; X > 1; X /= p[X]) {
        //cout << X << " " << p[X] << '\n';
        F[p[X]] += Type;
    }
}
long long C(int N,int K) { ///Tinh to hop chap K cua N voi K, N <= 2 x 10 ^ 6
    for (int i = 1; i <= N; i++) {
        F[i] = 0;
    }
    if (K > N) {
        return 0;
    }
    for (int i = N - K + 1; i <= N; i++) {
        tach(i,1);
    }
    for (int i = 2; i <= K; i++) {
        tach(i,-1);
    }
    long long Res = 1;
    for (int i = 1; i <= N; i++) {
        if (F[i] == 0) {
            continue;
        }
        Res = (Res * Tinh(i,F[i])) % M;
    }
    return Res;
}

///Graham
struct Point {
    long long x, y;
    Point(){};
    Point(long long _x, long long _y) : x(_x), y(_y) {};
    bool operator < (const Point &A) {
        return make_pair(x, y) < make_pair(A.x, A.y);
    }
    bool operator <= (const Point &A) {
        return make_pair(x, y) <= make_pair(A.x, A.y);
    }
    bool operator > (const Point &A) {
        return make_pair(x, y) > make_pair(A.x, A.y);
    }
    bool operator >= (const Point &A) {
        return make_pair(x, y) >= make_pair(A.x, A.y);
    }
    bool operator == (const Point &A) {
        return make_pair(x, y) == make_pair(A.x, A.y);
    }
    bool operator != (const Point &A) {
        return !(*this == A);
    }
    friend ifstream& operator >> (istream &in, Point &A) {
        in >> A.x >> A.y;
        return in;
    };
    friend ostream& operator << (ostream &os, const Point &A) {
        os << A.x << " " << A.y << '\n';
        return os;
    }
};

void Tru(Point &A,Point B) {
    A.x -= B.x;
    A.y -= B.y;
}
bool CungChieu(Point O,Point A,Point B) {
    Tru(A,O);
    Tru(B,O);
    return 1ll * A.x * B.y < 1ll * A.y * B.x;
}
bool NguocChieu(Point O,Point A,Point B) {
    Tru(A,O);
    Tru(B,O);
    return 1ll * A.x * B.y > 1ll * A.y * B.x;
}
bool ThangHang(Point O,Point A,Point B) {
    Tru(A,O);
    Tru(B,O);
    return 1ll * A.x * B.y == 1ll * A.y * B.x;
}
long long Dist(Point A,Point B) {
    long long X = B.x - A.x;
    long long Y = B.y - A.y;
    return X * X + Y * Y;
}

vector<Point> ConvexHull(vector<Point> &a) {
    int n = (int)a.size();
    int j = 0;
    for (int i = 1; i < n; i++) {
        if (a[i].y < a[j].y || (a[i].y == a[j].y && a[i].x < a[j].x)) {
            j = i;
        }
    }
    swap(a[0], a[j]);
    sort(a.begin() + 1, a.begin() + n, [&](Point A, Point B) {
        if (ThangHang(a[0], A, B)) {
            return Dist(a[0], A) < Dist(a[0], B);
        }
        return NguocChieu(a[0], A, B);
    });
    int m = 0;
    a.push_back(a[0]);
    for (int i = 0; i <= n; i++) {
        while (m >= 2 && !NguocChieu(a[m - 2],a[m - 1],a[i])) {
            m--;
        }
        a[m++] = a[i];
    }
    n = m - 1;
    a.resize(n);
    return a;
}
int n;
vector<Point> a;

///https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/Geometry/polygon.h
#define Det(a,b,c) ((double)(b.x-a.x)*(double)(c.y-a.y)-(double)(b.y-a.y)*(c.x-a.x))
bool in_convex(vector<Point>& l, Point p){
    int a = 1, b = l.size()-1, c;
    if (Det(l[0], l[a], l[b]) > 0) swap(a,b);
    // Allow on edge --> if (Det... > 0 || Det ... < 0)
    if (Det(l[0], l[a], p) > 0 || Det(l[0], l[b], p) < 0) return false;
    while(abs(a-b) > 1) {
        c = (a+b)/2;
        if (Det(l[0], l[c], p) > 0) b = c; else a = c;
    }
    // Alow on edge --> return Det... <= 0
    return Det(l[a], l[b], p) < 0;
}

///Fast Input/Output
int ReadInt() {
    char c;
    bool kt = false;
    for (c = getchar(); c < '0' || c > '9'; c = getchar()) {
        if (c == '-') {
            kt = true;
        }
    }
    int res = c - '0';
    for (c = getchar(); c >= '0' && c <= '9'; c = getchar()) {
        res = res * 10 + (c - '0');
    }
    return (kt ? 0 - res : res);
}

void WriteInt(int x) {
    if (x > 9) WriteInt(x / 10);
    putchar(x % 10 + '0');
}

void xuat(int x) {
    if (x < 0) {
        putchar('-');
        WriteInt(0 - x);
    }
    else {
        WriteInt(x);
    }
}

{
    ///https://github.com/Nikitosh/SPbAU-Generation-Z-Team-Reference/blob/master/strings/Hashes.cpp
    ///Double Hash
    const int P = 239017, MOD_X = 1e9 + 7, MOD_Y = 1e9 + 9;

    inline int add(int a, int b, int m) {
        a += b;
        return a >= m ? a - m : a;
    }

    inline int sub(int a, int b, int m) {
        a -= b;
        return a < 0 ? a + m : a;
    }

    inline int mul(int a, int b, int m) {
        return (a * 1ll * b) % m;
    }

    // using H = unsigned long long;
    struct H {
        int x, y;
        H(int _x = 0, int y = 0) {
            x = _x;
            y = _y;
        }
        inline H operator + (const H& other) const {
            return H(add(x, other.x, MOD_X), add(y, other.y, MOD_Y));
        }

        inline H operator - (const H& other) const {
            return H(sub(x, other.x, MOD_X), sub(y, other.y, MOD_Y));
        }

        inline operator * (const H& other) const {
            return H(mul(x, other.x, MOD_X), mul(y, other.y, MOD_Y));
        }

        void operator += (const H& other) {
            *this = *this + other;
        }

        void operator -= (const H& other) {
            *this = *this - other;
        }

        void operator *= (const H& other) {
            *this = *this * other;
        }
        inline bool operator == (const H& other) const {
            return x == other.x && y == other.y;
        }
    };

    H p[N], h[N];

    inline H get(int l, int r) { return h[r] - h[l] * p[r - l]; }

    void init(const string& s) {
        int n = sz(s);
        deg[0] = 1;
        forn (i, n)
            h[i + 1] = h[i] * P + s[i], p[i + 1] = p[i] * P;
    }
}
{
    ///shunting yard algorithm
    ///compact Expression
    ///s = "3*(x^2+x)+15" -> compactExpression(s)="3*x^2+3*x+15"
    ///s = "(9*x^3+5*x)*6*x+4" -> compactExpression(s)="54*x^4+30*x^2+4".

    struct node {
        int heso, mu;
        node(int _heso = 0, int _mu = 0) {
            heso = _heso;
            mu = _mu;
        }
        bool operator < (const node &a) {
            return mu < a.mu;
        }
        string evaluate() {
            string ans;
            if (mu == 0) return std::to_string(heso);
            if (heso < 0) ans += '-';
            if (abs(heso) > 1) {
                ans += std::to_string(abs(heso)) + "*";
            }
            ans += "x";
            if (mu > 1) ans += "^" + std::to_string(mu);
            return ans;
        }
    };
    vector<node> add(const vector<node> &a, const vector<node> &b) {
        int n = (int)a.size();
        int m = (int)b.size();
        vector<int> used(m, 0);
        vector<node> ans;
        for (int i = 0; i < n; i++) {
            node x = a[i];
            for (int i = 0; i < m; i++) {
                if (x.mu == b[i].mu) {
                    x.heso += b[i].heso;
                    used[i] = 1;
                    break;
                }
            }
            if (x.heso != 0) ans.push_back(x);
        }
        for (int i = 0; i < m; i++) {
            if (used[i] == 0) ans.push_back(b[i]);
        }
        if ((int)ans.size() == 0) return {node(0, 0)};
        sort(ans.begin(), ans.end());
        return ans;
    }
    node mul(node a, node b) {
        node ans;
        ans.heso = a.heso * b.heso;
        ans.mu = a.mu + b.mu;
        return ans;
    }
    vector<node> mul(const vector<node> &a, const vector<node> &b) {
        vector<node> ans;
        for (node x : a) {
            vector<node> v;
            for (node y : b) {
                y = mul(x, y);
                if (y.heso != 0) v.push_back(y);
            }
            ans = add(ans, v);
        }
        if ((int)ans.size() == 0) return {node(0, 0)};
        return ans;
    }
    vector<node> sub(const vector<node> &a, vector<node> b) {
        for (node &x : b) x.heso *= -1;
        return add(a, b);
    }
    vector<node> power(const vector<node> &a, vector<node> x) {
        vector<node> ans = {node(1, 0)};
        while ((int)x.size() > 1) continue;
        while (x[0].mu > 0) continue;
        for (int i = 0; i < x[0].heso; i++) ans = mul(ans, a);
        return ans;
    }

    int precedence(char c) {
        if (c == '(') return 0;
        if (c == '+' || c == '-') return 1;
        if (c == '*') return 2;
        if (c == '^') return 3;
        while (true) {
            continue;
        }
        return -1;
    }

    void infixToRpn(string s, vector<pair<node, char> > &exp) {
        vector<char> cur_op;
        int n = (int)s.size();
        for (int i = 0; i < n; ) {
            int j = i;
            if (s[i] >= '0' && s[i] <= '9') {
                int heso = 0;
                while (j < n && s[j] >= '0' && s[j] <= '9') {
                    heso = (heso * 10) + (s[j] - '0');
                    j++;
                }
                exp.push_back({node(heso, 0), '?'});
                i = j;
            }
            else {
                if (s[i] == 'x') {
                    exp.push_back({node(1, 1), '?'});
                    i++;
                    continue;
                }
                else {
                    if (s[i] == ')') {
                        while ((int)cur_op.size() > 0 && cur_op.back() != '(') {
                            exp.push_back({node(), cur_op.back()});
                            cur_op.pop_back();
                        }
                        if ((int)cur_op.size() > 0) cur_op.pop_back();
                    }
                    else{
                        if (s[i] == '(') cur_op.push_back('(');
                        else {
                            while ((int)cur_op.size() > 0) {
                                int top_prece = precedence(cur_op.back());
                                int cur_prece = precedence(s[i]);
                                int canEqual = cur_op.back() != '^';
                                if (top_prece + canEqual > cur_prece) {
                                    exp.push_back({node(), cur_op.back()});
                                    cur_op.pop_back();
                                }
                                else break;
                            }
                            cur_op.push_back(s[i]);
                        }
                    }
                }
                i++;
            }
        }
        while ((int)cur_op.size() > 0) {
            exp.push_back({node(), cur_op.back()});
            cur_op.pop_back();
        }
    }
    string compactExpression(string s)
    {
        if ((int)s.size() == 0) return "";
        vector<pair<node, char> > exp;
        infixToRpn(s, exp);

        stack<vector<node> > stk;
        for (auto [x, op] : exp) {
            if (op == '?') stk.push({x});
            else {
                vector<node> last = stk.top(); stk.pop();
                vector<node> prev;
                if ((int)stk.size() == 0) prev = {node(0, 0)};
                else {
                    prev = stk.top();
                    stk.pop();
                }
                vector<node> result;
                if (op == '+') result = add(prev, last);
                if (op == '-') result = sub(prev, last);
                if (op == '*') result = mul(prev, last);
                if (op == '^') result = power(prev, last);

                stk.push(result);
            }
        }

        if ((int)stk.size() == 0) {
            while (true) continue;
        }
        vector<node> value = stk.top();
        string ans;
        int sz = (int)value.size();
        for (int i = sz - 1; i >= 0; i--) {
            string t = value[i].evaluate();
            if (t[0] == '-') {
                ans += t;
            }
            else {
                if (i != sz - 1) ans += "+";
                ans += t;
            }
        }
        return ans;
    }
}
