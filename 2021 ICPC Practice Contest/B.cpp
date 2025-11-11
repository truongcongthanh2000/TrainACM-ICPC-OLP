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
// vector<long long> d(n - 1);
// rmq<long long> st(d, [&](long long a, long long b) {
//     return __gcd(a, b);
// });

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
    }
};

//apple 
//sa = 1, 5, 4, 3, 2
//f(1) = 1, vị trí lớn nhất là 5
//f(2) = 1
//f(3) = 1
//f(4) = 1
//f(5) = 1

//banana
//sa = 6, 4, 2, 1, 5, 3
//f(1) = 2, vị trí lớn nhất là 6
//f(2) = 2, vị trí lớn nhất là 5
//f(3) = 2
//f(4) = 2
//f(5) = 2
//f(6) = 1

//abcdabcd

vector<int> sort_cyclic_shifts(string const& s, vector<vector<int> >& cmp) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    cmp.push_back(c);
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
        cmp.push_back(c);
    }
    return p;
}
vector<int> suffix_array_construction(string s, vector<vector<int> > &cmp) {
    s += "$";
    vector<int> sorted_shifts = sort_cyclic_shifts(s, cmp);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

void sol() {
    string s;
    cin >> s;
    int n = (int)s.size();

    vector<vector<int> > cmp;
    vector<int> p = suffix_array_construction(s, cmp);

    int log_n = 0;
    while ((1 << (log_n + 1)) <= n) log_n++;
    auto LongestCommonPrefix = [&](int i, int j) {
        int ans = 0;
        for (int k = log_n; k >= 0; k--) {
            if (cmp[k][i] == cmp[k][j]) {
                ans += 1 << k;
                i += 1 << k;
                j += 1 << k;
            }
        }
        return ans;
    };

    vector<int> lcp(n, 0);
    for (int i = 0; i < n - 1; i++) lcp[i] = LongestCommonPrefix(p[i], p[i + 1]);

    rmq<int> st(lcp, [&](int a, int b) {
        return min(a, b);
    });

    rmq<int> st2(p, [&](int a, int b) {
        return min(a, b);
    });

    long long ans = 0;
    int idx = 0;
    for (int i = 0; i < n; i++) {
        int last = n - i - 1;
        while (idx < n && p[idx] > last) idx++;
        
        int L = idx + 1, R = n - 1;
        int jump = idx;
        while (L <= R) {
            int mid = (L + R) >> 1;
            int w = st.calc(idx, mid - 1);
            if (w >= i + 1) {
                jump = mid;
                L = mid + 1;
            }
            else R = mid - 1;
        }
        int choose = st2.calc(idx, jump);
        ans += 1LL * (i + 1) * (choose + 1);
    }
    cout << ans << '\n';
}

void solve() {
    int T = 1;
    cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        // cerr << "Processing test = " << TestCase << '\n';
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
