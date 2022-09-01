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

const int maxN = 3e5 + 100;
const int MOD = 1e9 + 7;

vector<vector<int> > IT(maxN * 4, vector<int>(64, 0));
void build(int i, int L, int R) {
    IT[i][0] = R - L + 1;
    if (L == R) return;
    int mid = (L + R) >> 1;
    build(i << 1, L, mid);
    build(i << 1 | 1, mid + 1, R);
}

vector<int> merge(vector<int> L, vector<int> R) {
    vector<int> ans(64, 0);
    for (int i = 0; i < 64; i++) {
        ans[i] = L[i] + R[i];
    }
    return ans;
}

int lazy[maxN * 4];
void push(int i, int L, int R) {
    if (lazy[i] == 0) return;

    vector<int> next(64, 0);
    for (int m = 0; m < 64; m++) next[m ^ lazy[i]] = IT[i][m];
    swap(IT[i], next);

    if (L != R) {
        lazy[i << 1] ^= lazy[i];
        lazy[i << 1 | 1] ^= lazy[i];
    }
    lazy[i] = 0;
}

void update(int i, int L, int R, int u, int v, int bit) {
    push(i, L, R);
    if (L > v || R < u) return;
    if (L >= u && R <= v) {
        lazy[i] ^= 1 << bit;
        push(i, L, R);
        return;
    }
    int mid = (L + R) >> 1;
    update(i << 1, L, mid, u, v, bit);
    update(i << 1 | 1, mid + 1, R, u, v, bit);
    IT[i] = merge(IT[i << 1], IT[i << 1 | 1]);
}

vector<int> get(int i, int L, int R, int u, int v) {
    push(i, L, R);
    if (L > v || R < u) return vector<int>(64, 0);
    if (L >= u && R <= v) return IT[i];
    int mid = (L + R) >> 1;
    auto left = get(i << 1, L, mid, u, v);
    auto right = get(i << 1 | 1, mid + 1, R, u, v);
    return merge(left, right);
}

void sol() {
    string s;
    cin >> s;
    int n = (int)s.size();
    build(1, 0, n);
    for (int i = 1; i <= n; i++) update(1, 0, n, i, n, s[i - 1] - 'a');

    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int L, R;
            cin >> L >> R;
            auto v_mask = get(1, 0, n, L - 1, R);

            long long ans = 0;
            for (auto num : v_mask) {
                ans += 1LL * num * (num - 1) / 2;
            }
            cout << ans << '\n';
        } else {
            int i;
            char c;
            cin >> i >> c;
            update(1, 0, n, i, n, s[i - 1] - 'a');
            s[i - 1] = c;
            update(1, 0, n, i, n, s[i - 1] - 'a');
        }
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
