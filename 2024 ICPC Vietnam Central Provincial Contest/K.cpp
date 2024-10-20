#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

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
const int INF = 2e9 + 100;
const long double EPS = 1e-9;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e5 + 100;
const int MOD = 998244353;

void sol() {
    // advance traveling salesman problem
    int n;
    cin >> n;
    vector<pair<int, int>> p; // list id(x, y) of '*'
    vector<vector<int>> a(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            string s;
            cin >> s;
            if (s == "*") {
                p.push_back({i, j});
            } else {
                a[i][j] = std::stoi(s);
            }
        }
    }
    auto dijkstra = [&](pair<int, int> s) -> vector<vector<long long>> {
        vector<vector<long long>> dist(n, vector<long long>(n, INF_LL));
        dist[s.first][s.second] = a[s.first][s.second];
        typedef pair<long long, pair<int, int>> i2;
        priority_queue<i2, vector<i2>, greater<i2>> Q;
        Q.push({a[s.first][s.second], {s.first, s.second}});
        while (Q.size() != 0) {
            i2 A = Q.top();
            Q.pop();
            long long du = A.first;
            int x = A.second.first, y = A.second.second;
            if (dist[x][y] != du) {
                continue;
            }
            for (int h = 0; h < 4; h++) {
                int u = x + dx[h];
                int v = y + dy[h];
                if (u >= 0 && u < n && v >= 0 && v < n && dist[u][v] > dist[x][y] + a[u][v]) {
                    dist[u][v] = dist[x][y] + a[u][v];
                    Q.push({dist[u][v], {u, v}});
                }
            }
        }
        return dist;
    };
    int m = p.size();
    vector<vector<vector<long long>>> edge;
    for (int i = 0; i < m; i++) edge.push_back(dijkstra(p[i]));
    vector<long long> cost(1 << m, INF_LL); // cost(mask) = minimum total distance from 1 cell (x, y) is not '*' to all bit 1 in mask
    for (int mask = 1; mask < (1 << m); mask++) {
        vector<int> ids;
        for (int i = 0; i < m; i++) {
            if ((mask >> i) & 1) {
                ids.push_back(i);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j]) { // not '*'
                    long long sum = 0;
                    for (int k = 0; k < ids.size(); k++) {
                        sum += edge[ids[k]][i][j];
                    }
                    cost[mask] = min(cost[mask], sum);
                }
            }
        }
    }
    // dp[mask]: minimum distance to merge all bit 1 in mask
    // dp[mask] = min(dp[s1] + dp[s2] + cost[mask]), s1 & mask == s1 and s2 = mask ^ s1
    vector<long long> dp(1 << m, INF_LL);
    for (int i = 0; i < m; i++) dp[1 << i] = 0;
    for (int mask = 1; mask < (1 << m); mask++) {
        for (int s1 = (mask - 1) & mask; s1 > 0; s1 = (s1 - 1) & mask) { // loop all subset of mask
            int s2 = mask ^ s1;
            dp[mask] = min(dp[mask], dp[s1] + dp[s2] + cost[mask]);
        }
    }
    cout << dp[(1 << m) - 1] << '\n';
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

int main(int argc, char *argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
