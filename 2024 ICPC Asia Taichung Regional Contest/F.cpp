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

const int maxN = 2e6 + 100;
const int MOD = 998244353;

vector<long long> segmentedSieveNoPreGen(long long L, long long R) {
    vector<bool> isPrime(R - L + 1, true);
    long long lim = sqrt(R);
    for (int i = 2; i <= lim; ++i)
        for (long long j = max(1LL * i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    if (L == 1)
        isPrime[0] = false;
    vector<long long> ans;
    for (int i = 0; i < R - L + 1; i++) {
        if (isPrime[i]) {
            ans.push_back(i + L);
        }
    }
    return ans;
}

void sol() {
    long long l, r;
    cin >> l >> r;
    vector<long long> p = segmentedSieveNoPreGen(l + l, r + r);
    p.insert(p.begin(), 0);
    p.push_back(INF_LL);

    int mn = INF, cnt = 0;
    auto f = [&](auto &&self, long long l, long long r) -> void {
        if (r - l == mn) {
            cnt++;
        }
        if (r - l < mn) {
            mn = r - l;
            cnt = 1;
        }
        auto it = lower_bound(p.begin(), p.end(), (l + r + 1) / 2);
        if (*it < r) {
            self(self, l, *it);
        }
        it = upper_bound(p.begin(), p.end(), (l + r) / 2);
        if (*prev(it) > l) {
            self(self, *prev(it), r);
        }
    };
    f(f, l + l, r + r);
    cout << cnt << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    cin >> T;
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
