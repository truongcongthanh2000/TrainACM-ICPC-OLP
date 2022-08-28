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

const int maxN = 2e6 + 100;
const int MOD = 1e9 + 7;

int lp[maxN];
vector<int> primes;

void Sieve() {
    for (int i = 2; i * i < maxN; i++) {
        if (!lp[i]) {
            for (int j = i * i; j < maxN; j += i) lp[j] = i;
        }
    }
    for (int i = 2; i < maxN; i++) {
        if (!lp[i]) primes.push_back(i);
    }
}

bool check(int p, string t) {
    string s = std::to_string(p);
    int m = t.size();
    int n = s.size();
    for (int i = 0; i <= n - m; i++) {
        if (s.substr(i, m) == t) return true;
    }
    return false;
}

void sol() {
    Sieve();
    cerr << (int)primes.size() << '\n';
    int l, h;
    cin >> l >> h;
    string p;
    cin >> p;
    int cnt = 0;
    for (int i = l - 1; i < h; i++) {
        if (check(primes[i], p)) {
            cnt++;
        }
    }
    cout << cnt;
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
