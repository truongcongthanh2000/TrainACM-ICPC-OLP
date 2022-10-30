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
    vector<vector<int> > cost;
    cost.push_back({255, 255, 255});
    cost.push_back({192, 192, 192});
    cost.push_back({128, 128, 128});
    cost.push_back({0, 0, 0});
    cost.push_back({255, 0, 0});
    cost.push_back({128, 0, 0});
    cost.push_back({255, 255, 0});
    cost.push_back({128, 128, 0});
    cost.push_back({0, 255, 0});
    cost.push_back({0, 128, 0});
    cost.push_back({0, 255, 255});
    cost.push_back({0, 128, 128});
    cost.push_back({0, 0, 255});
    cost.push_back({0, 0, 128});
    cost.push_back({255, 0, 255});
    cost.push_back({128, 0, 128});

    vector<string> names = {
        "White",
        "Silver",
        "Gray",
        "Black",
        "Red",
        "Maroon",
        "Yellow",
        "Olive",
        "Lime",
        "Green",
        "Aqua",
        "Teal",
        "Blue",
        "Navy",
        "Fuchsia",
        "Purple"};

    int r, g, b;
    while (cin >> r >> g >> b) {
        if (r == -1) return;
        int p = 0, ans = INF;
        for (int i = 0; i < (int)names.size(); i++) {
            int R = cost[i][0], G = cost[i][1], B = cost[i][2];
            int d = (R - r) * (R - r) + (G - g) * (G - g) + (B - b) * (B - b);
            if (d < ans) {
                p = i;
                ans = d;
            }
        }
        cout << names[p] << '\n';
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
