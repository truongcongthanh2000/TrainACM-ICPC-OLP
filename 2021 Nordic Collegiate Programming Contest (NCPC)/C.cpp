#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".txt","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int> > adj(n);
    vector<int> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto dijkstra = [&](int s, vector<long long> &d) {
        for (int i = 0; i < n; i++) d[i] = INF_LL;
        d[s] = w[s];
        typedef pair<long long, int> i2;
        priority_queue<i2, vector<i2>, greater<i2> > Q;
        Q.push({d[s], s});
        while ((int)Q.size() != 0) {
            i2 A = Q.top(); Q.pop();
            long long du = A.first;
            int u = A.second;
            if (d[u] != du) continue;
            for (int v : adj[u]) {
                if (d[v] > d[u] + w[v]) {
                    d[v] = d[u] + w[v];
                    Q.push({d[v], v});
                }
            }
        }
    };
    vector<long long> d1(n), d2(n);
    dijkstra(0, d1);
    dijkstra(n - 1, d2);
    vector<vector<int> > adj2(n);
    vector<int> deg(n, 0);
    bool special = false;
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            if (d1[u] + d2[v] == d1[n - 1] && d1[u] < d1[v]) {
                special |= u == 0 && v == n - 1;
                adj2[u].push_back(v);
                deg[v]++;
            }
        }
    }
    vector<int> p(n);
    queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            Q.push(i);
        }
    }
    vector<int> order(n);
    for (int idx = 0; idx < n; idx++) {
        int u = Q.front(); Q.pop();
        p[u] = idx;
        order[idx] = u;
        for (int v : adj2[u]) {
            if (--deg[v] == 0) Q.push(v);
        }
    }
    if (n == 2 && k == 1) {
        cout << "impossible";
        return;
    }
    if (special && p[n - 1] > k - 1) {
        if (k >= 2) {
            swap(order[k - 1], order[p[n - 1]]);
        }
        else {
            for (int i = k; i < n; i++) {
                if (order[i] != n - 1) {
                    swap(order[0], order[i]);
                    break;
                }
            }
        }
    }
    vector<char> ans(n);
    for (int i = 0; i < k; i++) ans[order[i]] = 'N';
    for (int i = k; i < n; i++) ans[order[i]] = 'S';
    for (int i = 0; i < n; i++) cout << ans[i];
}

void solve() {
    int T = 1;
    //cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
