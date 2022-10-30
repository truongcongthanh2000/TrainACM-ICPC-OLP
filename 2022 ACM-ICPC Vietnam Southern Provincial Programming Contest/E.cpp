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

struct Frac {
    double x, y;
    int num;

    Frac(int _x, int _y) {
        num = 1;
        x = _x * _y;
        y = _y * _y;
    }

    Frac(double _x, double _y, int _num) {
        x = _x;
        y = _y;
        num = _num;
    };

    double cost() {
        return x / y;
    }
};

Frac operator+(const Frac& a, const Frac& b) {
    return Frac(a.x + b.x, a.y + b.y, a.num + b.num);
};

void sol() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    cin >> a >> b;

    vector<Frac> hull;

    for (int i = 0; i < n; i++) {
        Frac cur = Frac(a[i], b[i]);
        while ((int)hull.size() > 0 && cur.cost() > hull.back().cost()) {
            cur = cur + hull.back();
            hull.pop_back();
        }
        hull.push_back(cur);
    }

    double ans = 0;
    int L = 0;
    for (auto& it : hull) {
        double r = it.cost();

        for (int i = 0; i < it.num; i++) {
            ans += (a[L] - r * b[L]) * (a[L] - r * b[L]);
            L++;
        }
    }

    cout << fixed << setprecision(10) << ans;
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
