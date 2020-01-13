#include <bits/stdc++.h>

using namespace std;
#define TASK "solve"
const int maxN = 2e5 + 100;
void doc() {
    freopen(TASK ".inp", "r", stdin);
    freopen(TASK ".out", "w", stdout);
}

typedef pair<int, int> i2;
const int dx[] = {0, 0, 1};
const int dy[] = {-1, -2, -1};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> c(n);
    int x = 0;
    int y = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        c[i] = s;
    }
    queue <i2> Q;
    int KT[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) KT[i][j] = -1;
    }
    KT[x][y] = 0;
    Q.push(i2(x, y));
    while ((int)Q.size() != 0) {
        i2 A = Q.front(); Q.pop();
        int x = A.first;
        int y = A.second;
        ///cout << x << " " << y << '\n';
        if (x == n - 1) {
            cout << KT[x][y] + 1;
            return;
        }
        for (int h = 0; h < 2; h++) {
            int u = x + dx[h];
            int v = (y + dy[h]) % m;
            if (v < 0) v += m;
            if (c[u][v] == 'M') break;
            ///cout << x << " " << y << " " << u << " " << v << '\n';
            if (KT[u][v] == -1) {
                KT[u][v] = KT[x][y] + 1;
                Q.push(i2(u, v));
            }
        }
        for (int h = 2; h < 3; h++) {
            int u = x + dx[h];
            int v = (y + dy[h]) % m;
            if (v < 0) v += m;
            if (c[u][y] == 'M' || c[u][v] == 'M') break;
            ///cout << x << " " << y << " " << u << " " << v << '\n';
            if (KT[u][v] == -1) {
                KT[u][v] = KT[x][y] + 1;
                Q.push(i2(u, v));
            }
        }
        int u = x - 1;
        int v = y - 1;
        if (v < 0) v += m;
        if (u >= 0) {
            if (c[u][y] != 'M' && c[u][v] != 'M') {
                if (KT[u][v] == -1) {
                    KT[u][v] = KT[x][y] + 1;
                    Q.push(i2(u, v));
                }
            }
        }
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ///doc();
    solve();
}
