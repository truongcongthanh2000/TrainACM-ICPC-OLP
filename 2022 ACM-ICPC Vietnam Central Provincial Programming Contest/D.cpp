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
const int BLOCK = 330;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
#ifdef THEMIS
    freopen(INP ".txt", "r", stdin);
    freopen(OUT ".txt", "w", stdout);
#endif  // THEMIS
}

const int maxN = 1e5 + 100;
const int MOD = 1e9 + 7;

int a[maxN];
vector<int> st[maxN * 4];

void build(int id, int l, int r) {
    if (l == r) {
        st[id].push_back(a[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);

    st[id].assign(r - l + 1, 0);
    merge(st[id * 2].begin(), st[id * 2].end(), st[id * 2 + 1].begin(), st[id * 2 + 1].end(), st[id].begin());
}

int get(int id, int l, int r, int u, int v, int k) {
    if (v < l || r < u) {
        return 0;
    }
    if (u <= l && r <= v) {
        return upper_bound(st[id].begin(), st[id].end(), k) - st[id].begin();
    }
    int mid = (l + r) / 2;
    return get(id * 2, l, mid, u, v, k) + get(id * 2 + 1, mid + 1, r, u, v, k);
}

void sol() {
    int n, Q;
    cin >> n >> Q;

    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);

    for (int i = 0; i < Q; i++) {
        int L, R;
        cin >> L >> R;

        int med = (R - L + 2) / 2;
        int x = 0, y = 1e5, ans = 0;
        while (x <= y) {
            int mid = (x + y) >> 1;
            int num = get(1, 1, n, L, R, mid);

            if (num < med) {
                x = mid + 1;
            } else {
                ans = mid;
                y = mid - 1;
            }
        }
        cout << ans << '\n';
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
