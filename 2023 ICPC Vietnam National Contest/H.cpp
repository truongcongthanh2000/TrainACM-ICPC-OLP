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
const int INF = 2e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e5 + 100;
const int MOD = 1e9 + 7;

template <typename T>
struct FenwickTree {
    vector<T> fenwick;
    int N;
    FenwickTree(int N = 1) {
        this->N = N;
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

void sol() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<vector<int>> positions(n + 1);
    for (int i = 1; i <= n; i++) {
        positions[a[i]].push_back(i);
    }
    vector<FenwickTree<long long>> fws(n + 1);
    for (int i = 1; i <= n; i++) {
        if (positions[i].size() > 0) fws[i] = FenwickTree<long long>(positions[i].size());
        int d = 1;
        for (int x : positions[i]) {
            fws[i].update(d++, 1LL * x * x);
        }
    }
    auto index = [&](int value, int p) -> int {
        return lower_bound(positions[value].begin(), positions[value].end(), p) - positions[value].begin();
    };
    auto update = [&](int p, int c) -> int {
        int i = index(a[p], p);
        fws[a[p]].update(i + 1, 1LL * c * p * p);
        return i;
    };
    long long last = 0;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int p;
            cin >> p;
            p = (p + last - 1) % (n - 1) + 1;
            if (a[p] != a[p + 1]) {
                int i = update(p, -1);
                int j = update(p + 1, -1);
                positions[a[p]][i] = p + 1;
                positions[a[p + 1]][j] = p;
                swap(a[p], a[p + 1]);
                update(p, 1);
                update(p + 1, 1);
            }
            continue;
        }
        int l, r, x;
        cin >> l >> r >> x;
        l = (l + last - 1) % n + 1;
        r = (r + last - 1) % n + 1;
        x = (x + last - 1) % n + 1;
        if (l > r) {
            swap(l, r);
        }
        if (t == 2) {
            last = fws[x].get(index(x, l) + 1, index(x, r + 1));
        } else {
            if (l > (int)positions[x].size()) {
                last = 0;
            } else {
                last = fws[x].get(l, min((int)positions[x].size(), r));
            }
        }
        cout << last << '\n';
    }
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
