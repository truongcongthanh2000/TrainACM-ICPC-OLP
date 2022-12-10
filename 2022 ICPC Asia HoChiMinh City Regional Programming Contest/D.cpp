#include <bits/stdc++.h>

using namespace std;

void open_file() {
    #ifdef THEMIS
        freopen("sol.inp", "r", stdin);
        freopen("sol.out", "w", stdout);
    #endif // THEMIS
}

const int maxN = 3e5 + 10;
int check[maxN][2];
set<int> S;
vector<int> adj[maxN];
int TP[maxN];

void DFS(int u, int t) {
    check[u][t] = 1;
    TP[u] = 1;
    S.insert(u);
    for (int v : adj[u]) {
        if (check[v][t ^ 1] == 0) DFS(v, t ^ 1);
    }
}
void sol() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (TP[i] == 0) {
            S.clear();
            DFS(i, 0);
            int even = 0, odd = 0;
            for (int u : S) {
                even += check[u][0];
                odd += check[u][1];
            }
            ans += 1LL * even * even;
            ans += 1LL * odd * odd;
            int common = 0;
            for (int u : S) {
                common += check[u][0] * check[u][1];
            }
            ans -= 1LL * common * common;
        }
    }

    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    int t = 1;
//    cin >> t;
    while (t--) sol();
}
