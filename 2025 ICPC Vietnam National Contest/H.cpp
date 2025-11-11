#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <immintrin.h>

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
const int INF = 1e9 + 100;
const long double EPS = 1e-12;
const int BLOCK = 330;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e6 + 100;
const int MOD = 998244353;

void sol() {
    int n, k;
    cin >> n >> k;
    if (k == 0) {
        cout << string(n, '0') << '\n';
        return;
    }
    if (k == n) {
        cout << string(n, '1') << '\n';
        return;
    }
    int z = n - k;
    int best_block1 = 0;
    long long best_val = 1e18;
    for (int block1 = 1; block1 <= k; block1++) {
        int s1 = k / block1;
        int l0 = (z + block1) / (block1 + 1);
        long long val = 1LL * l0 * (n + 1) - s1;
        if (val < best_val) {
            best_block1 = block1;
            best_val = val;
        }
    }

    int s1 = k / best_block1;
    int remain1 = k % best_block1;
    vector<int> ones(best_block1);
    for (int i = 0; i < best_block1; i++) ones[i] = s1 + (i < remain1 ? 1 : 0);

    vector<int> zeros(best_block1 + 1, 0);
    int l0 = z / (best_block1 + 1);
    int remain0 = z % (best_block1 + 1);
    for (int i = 0; i <= best_block1; i++) zeros[i] = l0 + (i < remain0 ? 1 : 0);

    string ans;
    for (int i = 0; i < best_block1; i++) {
        if (zeros[i]) ans.append(zeros[i], '0');
        if (ones[i]) ans.append(ones[i], '1');
    }
    if (zeros[best_block1]) ans.append(zeros[best_block1], '0');
    cout << ans << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    cin >> T;
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
