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
    int n, m, k;
    cin >> m >> n >> k;
    int s, t;
    cin >> s >> t;

    if (s == t) {
        cout << 0;
        return;
    }
    vector<vector<pair<int, int> > > adj(n);
    map<int, map<int, int> > id;
    vector<pair<int, int> > edge(m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});

        id[u][v] = i;
        edge[i] = {u, v};
    }

    map<int, map<int, int> > bad_edge;
    for (int i = 0; i < k; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        bad_edge[id[x][y]][z] = 1;
    }

    vector<int> dist(m, INF);
    typedef pair<int, int> i2;
    priority_queue<i2, vector<i2>, greater<i2> > Q;
    for (auto [u, w] : adj[s]) {
        dist[id[s][u]] = w;
        Q.push({w, id[s][u]});
    }

    while ((int)Q.size() != 0) {
        i2 A = Q.top();
        Q.pop();
        int id_edge = A.second;
        int du = A.first;
        if (dist[id_edge] != du) continue;

        int u = edge[id_edge].second;

        if (u == t) {
            cout << du;
            return;
        }

        for (auto [v, w] : adj[u]) {
            if (bad_edge[id_edge][v]) continue;
            int n_id_edge = id[u][v];

            if (dist[n_id_edge] > du + w) {
                dist[n_id_edge] = du + w;
                Q.push({dist[n_id_edge], n_id_edge});
            }
        }
    }
    cout << -1;
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
