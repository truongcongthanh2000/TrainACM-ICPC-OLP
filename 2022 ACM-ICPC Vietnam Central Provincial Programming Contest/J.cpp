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
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    auto idx = [&](int x) {
        return make_pair((x - 1) / m, (x - 1) % m);
    };

    auto pa = idx(a);
    auto pb = idx(b);

    if (pa.first == pb.first) {
        cout << 1 << '\n';
        cout << pa.second << " " << pa.first << " " << pb.second + 1 << " " << pa.first + 1 << '\n';
        return;
    }

    if (pa.second == 0 && (pb.second == m - 1 || b == n)) {
        cout << 1 << '\n';
        cout << pa.second << " " << pa.first << " " << m << " " << pb.first + 1 << '\n';
        return;
    }

    if (pa.second == 0 || (pb.second == m - 1 || b == n)) {
        cout << 2 << '\n';
        if (pa.second == 0) {
            cout << 0 << " " << pa.first << " " << m << " " << pb.first << '\n';
            cout << 0 << " " << pb.first << " " << pb.second + 1 << " " << pb.first + 1 << '\n';
        } else {
            cout << pa.second << " " << pa.first << " " << m << " " << pa.first + 1 << '\n';
            cout << 0 << " " << pa.first + 1 << " " << m << " " << pb.first + 1 << '\n';
        }
    } else {
        if (pa.second == pb.second + 1) {
            cout << 2 << '\n';
            cout << pa.second << " " << pa.first << " " << m << " " << pb.first << '\n';
            cout << 0 << " " << pa.first + 1 << " " << pb.second + 1 << " " << pb.first + 1 << '\n';
        } else {
            if (pa.first + 1 == pb.first) {
                cout << 2 << '\n';
                cout << pa.second << " " << pa.first << " " << m << " " << pa.first + 1 << '\n';
                cout << 0 << " " << pb.first << " " << pb.second + 1 << " " << pb.first + 1 << '\n';
            } else {
                cout << 3 << '\n';
                cout << pa.second << " " << pa.first << " " << m << " " << pa.first + 1 << '\n';
                cout << 0 << " " << pa.first + 1 << " " << m << " " << pb.first << '\n';
                cout << 0 << " " << pb.first << " " << pb.second + 1 << " " << pb.first + 1 << '\n';
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
