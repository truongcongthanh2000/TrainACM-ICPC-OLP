#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

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
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T> >& a) {
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
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
#ifdef THEMIS
    freopen(INP ".txt", "r", stdin);
    freopen(OUT ".txt", "w", stdout);
#endif  // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

long long IT[maxN * 4];

struct SegmentTree {
   private:
    vector<long long> IT;
    int n;
    void update(int i, int L, int R, int u, long long val) {
        if (L > u || R < u) return;
        if (L == R) {
            IT[i] = val;
            return;
        }
        int mid = (L + R) >> 1;
        update(i << 1, L, mid, u, val);
        update(i << 1 | 1, mid + 1, R, u, val);
        IT[i] = IT[i << 1] + IT[i << 1 | 1];
    }

    long long get(int i, int L, int R, int u, int v) {
        if (L > v || R < u) return 0;
        if (L >= u && R <= v) return IT[i];
        int mid = (L + R) >> 1;
        auto left = get(i << 1, L, mid, u, v);
        auto right = get(i << 1 | 1, mid + 1, R, u, v);
        return left + right;
    }

   public:
    SegmentTree(int _n) {
        n = _n;
        IT = vector<long long>(n * 4, 0);
    }
    void update(int u, long long val) {
        update(1, 1, n, u, val);
    }
    long long get(int L, int R) {
        return get(1, 1, n, L, R);
    }
};

void sol() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());

    vector<SegmentTree> st(k, SegmentTree(n));
    for (int i = 0; i < n; i++) {
        for (int j = k - 1; j >= 1; j--) {
            long long v = st[j - 1].get(1, a[i].second - 1);
            st[j].update(a[i].second, v);
        }
        st[0].update(a[i].second, 1);
    }

    cout << st[k - 1].get(1, n);
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    // cin >> T;
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

int main(int argc, char* argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
