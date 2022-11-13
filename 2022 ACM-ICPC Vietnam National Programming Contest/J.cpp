#include <bits/stdc++.h>

using namespace std;

void open_file() {
#ifdef THEMIS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif  // THEMIS
}
void sol() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            adj[i].push_back(x);
        }
    }

    vector<int> r(n), c(m);
    for (int i = 0; i < n; i++) {
        bool ok = true;
        for (int j = 0; j < m; j++) ok &= adj[i][j] == adj[i][0];
        r[i] = ok;
    }

    for (int j = 0; j < m; j++) {
        bool ok = true;
        for (int i = 0; i < n; i++) ok &= adj[i][j] == adj[0][j];
        c[j] = ok;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) ans += r[i] * c[j];
    }
    cout << ans << '\n';
}
int main() {
    int t = 1;
    cin >> t;
    while (t--) sol();
}
