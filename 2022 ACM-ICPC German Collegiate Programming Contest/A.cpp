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

void sol() {
    int a, b;
    cin >> a >> b;
    set<pair<int, int>> s1, s2;

    auto f = [&](int c, set<pair<int, int>>& s) {
        for (int i = 1; i < c; ++i) {
            int a = i;
            long long value = 1LL * c * c - 1LL * a * a;
            int b = sqrt(value);
            while (1LL * (b + 1) * (b + 1) <= value) b++;
            while (1LL * b * b > value) b--;
            if (1LL * a * a + 1LL * b * b == 1LL * c * c) {
                int gcd = __gcd(a, b);
                if (a > b) {
                    swap(a, b);
                }
                a /= gcd;
                b /= gcd;
                s.insert({a, b});
            }
        }
    };

    f(a - 1, s1);
    f(b - 1, s2);

    int ans = 0;
    for (auto it : s1) {
        ans += s2.find(it) != s2.end();
    }
    cout << (ans * 4 + 2) / (a == b ? 2 : 1);
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
