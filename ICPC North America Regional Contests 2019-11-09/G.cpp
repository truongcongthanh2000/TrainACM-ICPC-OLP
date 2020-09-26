#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

#define INP "solve"
#define OUT "solve"

using namespace std;

const int INF = 1e9;
void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 100;

typedef pair<int, int> i2;
typedef pair<int, i2> i3;
vector<i2> adj[maxN];
int color[maxN];
int Used[maxN];
int dist[maxN][3];

void sol() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    vector<int> points;
    Used[1] = 1;
    points.push_back(1);
    int d = 0;
    while ((int)points.size() > 0) {
        vector<int> nxt;
        for (int u : points) {
            for (auto [v, id] : adj[u]) {
                if (Used[v] == 0) {
                    Used[v] = Used[u] + 1;
                    color[id] = d;
                    nxt.push_back(v);
                }
                else {
                    if (Used[v] == Used[u] + 1) color[id] = d;
                }
            }
        }
        swap(points, nxt);
        d ^= 1;
    }
    cout << Used[n] - 2;
}

void solve() {
    int T;
    ///cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
