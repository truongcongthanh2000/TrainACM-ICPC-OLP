#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<vector<T>> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) {
        for (const auto &value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (auto &x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-9;
const int BLOCK = 330;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 1e6 + 100;
const int MOD = 998244353;

#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

/// Fast Input/Output
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

template <typename T>
struct FenwickTree {
    vector<T> fenwick;
    int N;
    FenwickTree() {};
    FenwickTree(int NN) {
        N = NN;
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
    int n = ReadInt();
    vector<int> s(n);
    for (int i = 0; i < n; i++) s[i] = ReadInt();
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        a[i].first = s[i];
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    vector<int> sort_s(n);
    for (int i = 0; i < n; i++) sort_s[i] = a[i].first;
    sort_s.resize(unique(sort_s.begin(), sort_s.end()) - sort_s.begin());
    vector<int> link(n);
    for (int i = 0; i < n; i++) {
        link[a[i].second] = i;
        s[i] = lower_bound(sort_s.begin(), sort_s.end(), s[i]) - sort_s.begin() + 1;
    }
    auto get = [&]() {
        long long ans = 1LL * n * n;
        vector<int> prefix_max(n);
        prefix_max[0] = s[0];
        for (int i = 1; i < n; i++) {
            prefix_max[i] = max(prefix_max[i - 1], s[i]);
        }
        FenwickTree<int> fw(sort_s.size());
         for (int i = n - 1; i > 0; i--) {
            fw.update(s[i], 1);
            int d = fw.get(1, prefix_max[i - 1] - 1);
            int R = i + d - 1;
            long long wL = R ? 1LL * (R + 1) * (R + 1) : 0;
            long long wR = (n - i) > 1 ? 1LL * (n - i) * (n - i) : 0;
            ans = min(ans, wL + wR);
        }
        return ans;
    };

    long long ans = 1LL * n * n;
    vector<int> max_prefix_link(n), min_suffix_link(n);
    max_prefix_link[0] = link[0];
    for (int i = 1; i < n; i++) max_prefix_link[i] = max(max_prefix_link[i - 1], link[i]);
    min_suffix_link[n - 1] = link[n - 1];
    for (int i = n - 2; i >= 0; i--) min_suffix_link[i] = min(min_suffix_link[i + 1], link[i]);
    for (int i = 0; i < n;) {
        if (link[i] != i) {
            i++;
            continue;
        }
        int j = i;
        while (j < n && link[j] == j) j++;
        long long wL = i > 1 ? 1LL * i * i : 0;
        long long wR = (n - j) > 1 ? 1LL * (n - j) * (n - j) : 0;
        if ((i == 0 || max_prefix_link[i - 1] < i) && (j == n || min_suffix_link[j] >= j)) {
            ans = min(ans, wL + wR);
        }
        i = j;
    }
    ans = min(ans, get());
    for (int &x : s) x = sort_s.size() - x + 1;
    reverse(s.begin(), s.end());
    ans = min(ans, get());
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
        cerr << "Processing test = " << TestCase << '\n';
        // cout << "Case #" << TestCase << ": ";
        sol();
        // if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc, char *argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
