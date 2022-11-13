#include <bits/stdc++.h>

using namespace std;

void open_file() {
    #ifdef THEMIS
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // THEMIS
}

int get(vector<int> p) {
    int n = (int)p.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans += p[i] > p[j];
        }
    }
    return ans;
}

void gen(vector<int> p) {
    int n = (int)p.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            swap(p[i], p[j]);
            cout << get(p) << ' ';
            swap(p[i], p[j]);
        }
        cout << '\n';
    }
}
void sol() {
    int n;
    cin >> n;
    vector<vector<int> > c(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c[i][j];
        }
    }
    int num_i = c[0][0];
    vector<vector<int> > F(n, vector<int>(n, 0));
    vector<vector<int> > L(n, vector<int>(n, 0));
    vector<vector<int> > G(n, vector<int>(n, 0));

    for (int len = 1; len < n; len++) {
        for (int i = 0; i + len < n; i++) {
            int j = i + len;
            int x = -L[i][j] + L[j][i] - G[j][i] + G[i][j];
            if (x + num_i < c[i][j]) {
                F[i][j] = 1;
            } else {
                F[j][i] = 1;
            }
        }
        for (int i = 0; i + (len + 1) < n; i++) {
            int j = i + len;
            L[i][j + 1] = F[i + 1][j + 1] + L[i + 1][j + 1];
            L[j + 1][i] = F[j][i] + L[j][i];

            G[i][j + 1] = (j - i) - L[i][j + 1];
            G[j + 1][i] = (j - i) - L[j + 1][i];
        }
    }

    vector<vector<int> > adj(n);
    vector<int> deg(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (F[i][j]) {
                deg[j]++;
                adj[i].push_back(j);
            }
        }
    }

    queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) Q.push(i);
    }

    vector<int> ans(n, 0);
    int LK = 1;
    while ((int)Q.size() != 0) {
        int u = Q.front(); Q.pop();
        ans[u] = LK++;
        for (int v : adj[u]) {
            if (--deg[v] == 0) Q.push(v);
        }
    }
    for (int x : ans) cout << x << ' ';
}
int main() {
    open_file();
    int t = 1;
    //cin >> t;
    while (t--) sol();
}
