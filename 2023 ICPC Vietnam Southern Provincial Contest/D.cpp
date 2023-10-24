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
const int INF = 2e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e5 + 100;
const int MOD = 1e9 + 7;

int get_n_dangerous(const vector<vector<int>>& a, int G) {
    int n = a.size();
    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] < G) {
                cost[i][j] = 1;
            } else {
                cost[i][j] = 0;
            }
        }
    }
    vector<vector<int>> d(n, vector<int>(n, INF));
    d[0][0] = 0;
    typedef pair<int, pair<int, int>> i2;
    priority_queue<i2, vector<i2>, greater<i2>> Q;
    Q.push({0, {0, 0}});
    while ((int)Q.size() != 0) {
        i2 it = Q.top();
        Q.pop();
        int du = it.first, u = it.second.first, v = it.second.second;
        if (du != d[u][v]) {
            continue;
        }
        for (int h = 0; h < 4; h++) {
            int x = u + dx[h];
            int y = v + dy[h];
            if (x >= 0 && x < n && y >= 0 && y < n && d[x][y] > d[u][v] + cost[x][y]) {
                d[x][y] = d[u][v] + cost[x][y];
                Q.push({d[x][y], {x, y}});
            }
        }
    }
    return d[n - 1][n - 1];
}
void sol() {
    int t;
    cin >> t;
    int n, G;
    if (t == 1) {
        cin >> n >> G;
    } else {
        cin >> n;
    }
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) cin >> a[i];
    if (t == 1) {
        cout << get_n_dangerous(a, G) << '\n';
    } else {
        int L = 0, R = 1e5 + 100;
        int ans = 0;
        while (L <= R) {
            int mid = (L + R) >> 1;
            if (get_n_dangerous(a, mid) == 0) {
                ans = mid;
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }
        cout << ans << '\n';
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
