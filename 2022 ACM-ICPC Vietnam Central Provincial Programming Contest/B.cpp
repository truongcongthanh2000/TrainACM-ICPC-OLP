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

void Zfunction(int z[], string s) {
    int n = (int)s.size();
    for (int i = 1; i <= n; i++) z[i] = 0;
    int L = 1, R = 1;
    for (int i = 2; i <= n; i++) {
        if (i <= R) z[i] = min(z[i - L + 1], R - i + 1);
        while (i + z[i] <= n && s[z[i]] == s[i + z[i] - 1]) z[i]++;
        if (i + z[i] - 1 > R) {
            L = i;
            R = i + z[i] - 1;
        }
    }
}

int z[maxN];
void sol() {
    string s;
    cin >> s;
    int n = (int)s.size();
    Zfunction(z, s);
    vector<int> sum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        sum[z[i]]++;
    }
    for (int i = n - 1; i >= 0; i--) sum[i] += sum[i + 1];

    int Q;
    cin >> Q;
    while (Q--) {
        int L;
        cin >> L;
        if (L >= n - 1)
            cout << "NO" << '\n';
        else {
            if (z[n - L + 1] < L) {
                cout << "NO" << '\n';
            } else {
                if (sum[L] < 2) {
                    cout << "NO" << '\n';
                } else {
                    cout << "YES"
                         << " " << sum[L] + 1 << '\n';
                }
            }
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
