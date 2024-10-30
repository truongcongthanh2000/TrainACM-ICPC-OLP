#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

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
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    // Statment: Find the longest sequence 00..0(d)100..0(d)...100..0(d), each group 0 has size d and following by 1
    // We can try for all d <= n and build the sequence in O(n/d), total complexity is sum O(n/i) for all i <= n ~ O(nlgnlgn)
    // To build the sequence fast in O(n/d), we need to build the next(i, c) = minimum j > i that s(j) = c
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<int>> id(2);
    for (int i = 0; i < n; i++) id[s[i] - '0'].push_back(i);

    auto get_id = [&](int value, int i) {
        int j = lower_bound(id[value].begin(), id[value].end(), i + 1) - id[value].begin();
        return j;
    };

    vector<vector<int>> jump(2, vector<int>(n));
    for (int value = 0; value < 2; value++) {
        for (int i = 0; i < n; i++) jump[value][i] = get_id(value, i);
    }

    int ans = id[1].size(); // d = 0 ~ 11111...1111
    for (int d = 1, m = id[0].size(); d <= m; d++) {
        int len = 0;
        int current = id[0][d - 1];
        while (current < n) {
            // each step will try to make 100..(d) from the current index
            int i1 = jump[1][current];
            if (i1 == id[1].size()) {
                break;
            }
            int i0 = jump[0][id[1][i1]];
            if (i0 + d - 1 >= m) {
                break;
            }
            current = id[0][i0 + d - 1];
            len += 1 + d;
        }
        if (len) {
            len += d;
        }
        ans = max(ans, len);
    }
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
