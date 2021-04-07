#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const int QQ = 3e5 + 10;
const int maxN = 3e5 + 10;
const int maxA = 1e6 + 10;
const long long oo = 1e16;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double du = 1e-9;
const string YES = "YES";
const string NO = "NO";
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void doc() {
    freopen(INP ".inp","r",stdin);
    freopen(OUT ".out","w",stdout);
}

typedef pair<int, char> i2;
int n, m;
vector<i2> adj[maxN];
int D[maxN], trace[maxN];
void sol() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end(), [](i2 a, i2 b) {
            if (a.second != b.second) return a.second < b.second;
            return a.first < b.first;
        });
    }

    queue <int> Q;
    Q.push(n);
    D[n] = 1;
    while ((int)Q.size() != 0) {
        int u = Q.front(); Q.pop();
        for (i2 it : adj[u]) {
            int v = it.first;
            char c = it.second;
            if (D[v] == 0) {
                D[v] = D[u] + 1;
                Q.push(v);
            }
        }
    }
    vector<int> Used(n + 1, 0);
    vector<int> path;
    string res;
    vector<int> cur = {1};
    Used[1] = 1;
    for (; cur.size() > 0; ) {
        char min_character = 'z';
        bool ok = false;
        for (int u : cur) {
            for (i2 it : adj[u]) {
                int v = it.first;
                char c = it.second;
                if (D[v] == D[u] - 1 && Used[v] == 0) {
                    ok = true;
                    min_character = min(min_character, c);
                }
            }
        }
        if (!ok) break;
        res += min_character;
        vector<int> nxt;
        for (int u : cur) {
            for (i2 it : adj[u]) {
                int v = it.first;
                char c = it.second;
                if (D[v] == D[u] - 1 && Used[v] == 0 && c == min_character) {
                    trace[v] = u;
                    nxt.push_back(v);
                    Used[v] = 1;
                }
            }
        }
        swap(cur, nxt);
    }
    int t = n;
    while (t != 1) {
        path.push_back(t);
        t = trace[t];
    }
    path.push_back(1);
    reverse(path.begin(), path.end());
    cout << (int)res.size() << '\n';
    for (int x : path) cout << x << ' ';
    cout << '\n';
    cout << res;
}

void solve() {
    int T;
    ///cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        ///cout << "Case #" << TestCase << ": ";
        sol();
    }
}

int main(int argc,char *argv[]) {
    srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
}
