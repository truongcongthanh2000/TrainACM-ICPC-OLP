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

long long lcm(long long a, long long b) {
    return a / __gcd(a, b) * b;
}

long double s[maxN];
void init() {
    s[0] = 0.0;
    long long ms = 1;
    for (int i = 1; i <= 40; i++) {
        ms = lcm(ms, i * (i + 1));
        long long ts = 0;
        for (int j = 1; j <= i; j++) {
            ts += ms / (j * (j + 1));
        }
        s[i] = 1.0 * ts / ms;
    }
    for (int i = 41; i < maxN; i++) {
        s[i] = s[i - 1] + (1.0 / (1LL * i * (i + 1)));
    }
}

void sol() {
    int n;
    cin >> n;

    n++;
    long long ts = 1;
    for (int i = 1; i <= 9; i++) {
        ts = ts * 10;
        cout << ts / n;
        ts %= n;
    }
    cout << '.';
    for (int i = 1; i <= 9; i++) {
        ts *= 10;
        cout << ts / n;
        ts %= n;
    }
    cout << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    init();
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

int main(int argc, char* argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
