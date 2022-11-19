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

struct DisjointSetUnion {  /// Base 1th or Base 0th
    /// if u is root then p[u] < 0 and |p[u]| is size of the Set that u is root
    /// if u is not root then p[u] = x and x, u are belong the same Set
    int n;
    vector<int> p;
    DisjointSetUnion(){};
    DisjointSetUnion(int _n) {
        n = _n;
        p.assign(n + 7, -1);  /// p[i] = -1 for all i
    }

    int find_root(int u) {              /// find the root in the Set contain u
        if (p[u] < 0) return u;         /// u is root
        return p[u] = find_root(p[u]);  /// get the root and jump
    }

    void Union(int u, int v) {
        int x = find_root(u);
        int y = find_root(v);
        if (x == y) return;
        if (p[x] > p[y]) swap(x, y);  /// small Set point to big Set, p[x] > p[y] so |p[x]| < |p[y]|
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

struct Interval {
    int L, R;
    int id;
    bool operator<(const Interval& other) {
        return L < other.L;
    }
};

void sol() {
    int n, k;
    cin >> n >> k;
    vector<Interval> I(n);
    for (int i = 0; i < n; i++) {
        cin >> I[i].L >> I[i].R;
        I[i].id = i;
    }
    sort(I.begin(), I.end());

    DisjointSetUnion dsu(n);
    vector<pair<int, int> > point;
    vector<int> id(n, 0);

    for (int i = 0; i < n;) {
        int j = i, R = I[i].R;
        while (j < n - 1 && I[j + 1].L <= R) {
            j++;
            R = max(R, I[j].R);
        }

        for (int k = i; k < j; k++) {
            dsu.Union(I[k].id, I[k + 1].id);
        }

        int root = dsu.find_root(I[i].id);
        point.push_back({I[i].L, R});
        id[root] = (int)point.size();

        i = j + 1;
    }
    
    vector<long long> sum(n + 1, 0);
    for (int i = 0; i < (int)point.size() - 1; i++) {
        sum[i + 1] = sum[i] + point[i + 1].first - point[i].second;
    }

    auto dist = [&](int u, int v) -> long long {
        int x = dsu.find_root(u);
        int y = dsu.find_root(v);
        if (x == y) return 0;

        int L = id[x], R = id[y];
        if (L > R) swap(L, R);

        return sum[R - 1] - sum[L - 1];
    };

    long long ans = 0;
    int last = 0;
    for (int i = 0; i < k; i++) {
        int u;
        cin >> u;
        u--;

        ans += dist(last, u);
        last = u;
    }

    cout << ans;
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
