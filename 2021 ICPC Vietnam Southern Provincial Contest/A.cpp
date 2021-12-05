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

template<typename flow_t = int>
struct PushRelabel {
    struct Edge {
        int to, rev;
        flow_t f, c;
    };
    vector<vector<Edge> > g;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}

    int addEdge(int s, int t, flow_t cap, flow_t rcap=0) {
        if (s == t) return -1;
        Edge a = {t, (int)g[t].size(), 0, cap};
        Edge b = {s, (int)g[s].size(), 0, rcap};
        g[s].push_back(a);
        g[t].push_back(b);

        // Return ID of forward edge.
        return b.rev;
    }

    flow_t maxFlow(int s, int t) {
        int v = g.size();
        H[s] = v;
        ec[t] = 1;
        vector<int> co(2*v);
        co[0] = v-1;
        for (int i = 0; i < v; ++i) {
            cur[i] = g[i].data();
        }
        for (auto &e : g[s]) {
            add_flow(e, e.c);
        }
        if (hs[0].size()) {
            for (int hi = 0; hi >= 0;) {
                int u = hs[hi].back();
                hs[hi].pop_back();
                while (ec[u] > 0) { // discharge u
                    if (cur[u] == g[u].data() + g[u].size()) {
                        H[u] = 1e9;
                        for (auto &e : g[u]) {
                            if (e.c && H[u] > H[e.to]+1) {
                                H[u] = H[e.to]+1;
                                cur[u] = &e;
                            }
                        }
                        if (++co[H[u]], !--co[hi] && hi < v) {
                            for (int i = 0; i < v; ++i) {
                                if (hi < H[i] && H[i] < v){
                                    --co[H[i]];
                                    H[i] = v + 1;
                                }
                            }
                        }
                        hi = H[u];
                    } else if (cur[u]->c && H[u] == H[cur[u]->to] + 1) {
                        add_flow(*cur[u], min(ec[u], cur[u]->c));
                    }
                    else {
                        ++cur[u];
                    }
                }
                while (hi>=0 && hs[hi].empty()) --hi;
            }
        }
        return -ec[s];
    }

private:
    vector<flow_t> ec;
    vector<Edge*> cur;
    vector<vector<int> > hs;
    vector<int> H;

    void add_flow(Edge& e, flow_t f) {
        Edge &back = g[e.to][e.rev];
        if (!ec[e.to] && f) {
            hs[H[e.to]].push_back(e.to);
        }
        e.f += f; e.c -= f;
        ec[e.to] += f;
        back.f -= f; back.c += f;
        ec[back.to] -= f;
    }
};

void sol() {
    int n;
    cin >> n;
    vector<vector<int> > a(n, vector<int>(n, 0));
    vector<pair<int, int> > edge;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            if (a[i][j] > 0) edge.push_back({i, j});
        }
    }
    vector<vector<int> > b = a;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                b[i][j] = max(b[i][j], min(b[i][k], b[k][j]));
            }
        }
    }
    vector<vector<int> > ans(n, vector<int>(n, 0));
    int s = n, t = n + 1;
    PushRelabel pr(t + 1);
    for (auto [u, v] : edge) {
        pr.addEdge(u, v, a[u][v]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (b[i][j] == 0) continue;
            pr.addEdge(s, i, INF);
            pr.addEdge(j, t, INF);
            ans[i][j] = ans[j][i] = pr.maxFlow(s, t);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << ans[i][j] << ' ';
        cout << '\n';
    }
}

void solve() {
    int T = 1;
    cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cerr << "Processing test = " << TestCase << '\n';
        cout << "Case #" << TestCase << ":" << '\n'; 
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
