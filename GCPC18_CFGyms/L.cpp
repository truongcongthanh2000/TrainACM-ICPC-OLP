#include <bits/stdc++.h>
using namespace std;
const int MaxN = 1e6+5;

int n, m, q, P[1005][1005];
void doc() {
    freopen("OB.inp","r",stdin);
    freopen("OB.out","w",stdout);
}

void solve() {
    int n, m;
    cin >> n >> m;
    int a[n + 2][m + 2];
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            cin >> a[i][j];
        }
    }
    bool Res[n + 1][m + 1];
    memset(Res, 0, sizeof(Res));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x = i + 1;
            int y = j + 1;
            if (a[i][j]) {
                Res[x][y] = 1;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        a[x + dx][y + dy] -= 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            if (a[i][j]) {
                cout << "impossible";
                return;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (Res[i][j]) cout << "X";
            else cout << ".";
        }
        cout << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
