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
    int n, m;
    cin >> n >> m;
    vector<vector<int> > adj(n);

    vector<pair<int, int> > edge;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edge.push_back({u, v});
    }

    vector<int> dTriangle(n, 0);
    vector<int> visit(n, 0);
    int cur = 0;
    for (int u = 0; u < n; ++u) {
        cur++;
        for (int &x : adj[u]) visit[x] = cur;
        for (int &v : adj[u]) if (adj[u].size() > adj[v].size() || (adj[u].size() == adj[v].size() && u < v)) {
            for (int &v2 : adj[v]) {
                if (visit[v2] == cur) {
                    dTriangle[u]++;
                    dTriangle[v2]++;
                    dTriangle[v]++;
                }
            }
        }
    }
    vector<long long> d2(n, 0);
    for (int u = 0; u < n; ++u) {
        dTriangle[u] /= 3;
        for (int &v : adj[u]) d2[u] += adj[v].size() - 1;
    }

    long long ans = 0;
    for (int u = 0; u < n; ++u) {
        int deg = adj[u].size();
        long long val = d2[u] * (deg - 1) * (deg - 2) * (deg - 3) / 6;
        val -= 1LL * dTriangle[u] * (deg - 2) * (deg - 3);
        ans += val;
    }
    
    cout << ans;
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
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
