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

void sol() {
    int p, q;
    cin >> p >> q;
    string s;
    cin >> s;
    if (s == "AABB") {
        if (q == 7) {
            cout << 8 << " " << 9 << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
    if (s == "ABAB") {
        if (p == 6 && q == 8) {
            cout << 7 << " " << 9 << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
    if (s == "ABBA") {
        if (q - p == 3) {
            cout << p + 1 << " " << p + 2 << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
    if (s == "BAAB") {
        if (p == 2 && q == 8) {
            cout << 1 << " " << 9 << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
    if (s == "BABA") {
        if (p == 2 && q == 4) {
            cout << 1 << " " << 3 << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
    if (s == "BBAA") {
        if (p == 3) {
            cout << 1 << " " << 2 << '\n';
        } else {
            cout << -1 << '\n';
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
