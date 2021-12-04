#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    int n, m, k;
    cin >> n >> m >> k;
    string sname, tname;
    cin >> sname >> tname;
    vector<string> v_names = {sname, tname};

    vector<string> name(n);
    vector<int> c_tmp(n), moon_tmp(n);
    for (int i = 0; i < n; i++){
        cin >> name[i] >> moon_tmp[i] >> c_tmp[i];
        v_names.push_back(name[i]);
    }

    sort(v_names.begin(), v_names.end());
    v_names.resize(unique(v_names.begin(), v_names.end()) - v_names.begin());

    auto id = [&](string name) -> int {
        return lower_bound(v_names.begin(), v_names.end(), name) - v_names.begin();
    };

    vector<int> c(n), moon(n);
    vector<string> name_r(n);
    for (int i = 0; i < n; i++) {
        int nid = id(name[i]);
        name_r[nid] = name[i];
        c[nid] = c_tmp[i];
        moon[nid] = moon_tmp[i];
    }

    vector<vector<pair<int, int> > > adj(n);
    for (int i = 0; i < m; i++) {
        string u, v;
        int c;
        cin >> u >> v >> c;
        adj[id(u)].push_back({id(v), c});
        adj[id(v)].push_back({id(u), c});
    }
    int time = 0;
    vector<int> used(n, 0);
    auto calc = [&](int source) {
        time++;
        used[source] = time;
        int ans = 0;
        vector<int> Q = {source};
        for (int i = 0; i < k; i++) {
            vector<int> nQ;
            for (int u : Q) {
                for (auto [v, id] : adj[u]) {
                    if (used[v] != time) {
                        used[v] = time;
                        nQ.push_back(v);
                    }
                }
            }
            Q.clear();
            for (int u : nQ) {
                Q.push_back(u);
                ans += c[u];
            }
        }
        return ans;
    };
    vector<int> cost(n);
    for (int i = 0; i < n; i++) {
        cost[i] = calc(i);
    }

    typedef pair<int, int> i2;
    typedef pair<int, i2> i3;
    priority_queue<i3, vector<i3>, greater<i3> > Q;

    int s = id(sname);
    int t = id(tname);
    
    vector<int> dist(n, INF), dmoon(n, 0);
    dist[s] = 0;
    dmoon[s] = moon[s];

    Q.push({0, {-dmoon[s], s}});
    while ((int)Q.size() > 0) {
        i3 A = Q.top(); Q.pop();
        int du = A.first;
        int moonu = -A.second.first;
        int u = A.second.second;
        if (dist[u] != du || moonu != dmoon[u]) continue;
        for (auto [v, w] : adj[u]) {
            int dv = du + cost[u] + w;
            if (dist[v] > dv) {
                dist[v] = dv;
                dmoon[v] = dmoon[u] + moon[v];
                Q.push({dist[v], {-dmoon[v], v}});
            }
            else {
                if (dv == dist[v] && dmoon[v] < dmoon[u] + moon[v]) {
                    dmoon[v] = dmoon[u] + moon[v];
                    Q.push({dist[v], {-dmoon[v], v}});
                }
            }
        }
    }
    cout << dist[t] << " " << dmoon[t] << '\n';
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
