#include <bits/stdc++.h>

using namespace std;
#define TASK "solve"
const int maxN = 2e5 + 100;
void doc() {
    freopen(TASK ".inp", "r", stdin);
    freopen(TASK ".out", "w", stdout);
}

const long long oo = 1e18;
struct mt{
    long long c[50][50];
    mt() {
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++)
                c[i][j] = -oo;
        }
    }
};
int R, C;
mt nhan(mt a, mt b) {
    mt c;
    for (int k = 0; k < C; k++) {
        for (int i = 0; i < C; i++) {
            for (int j = 0; j < C; j++) {
                long long val = a.c[i][k] + b.c[k][j];
                c.c[i][j] = max(c.c[i][j], val);
            }
        }
    }
    return c;
}
mt Get(mt a, int n) {
    mt Res;
    for (int i = 0; i < C; i++) Res.c[i][i] = 0;
    for (; n; n = n >> 1, a = nhan(a, a)) {
        if (n & 1) Res = nhan(Res, a);
    }
    return Res;
}
typedef pair<int, int> i2;
int KT[100][100];
void solve() {
    cin >> R >> C;
    int K;
    cin >> K;
    char c[R][C];
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) cin >> c[i][j];
    }
    int Val[C];
    for (int i = 0; i < C; i++) cin >> Val[i];
    mt a;
    for (int i = 0; i < C; i++) {
        queue <i2> Q;
        Q.push(i2(0, i));
        if (c[0][i] == 'X') continue;
        for (int i = 0; i <= R; i++) {
            for (int j = 0; j < C; j++) {
                KT[i][j] = 0;
            }
        }
        KT[0][i] = 1;
        while ((int)Q.size() != 0) {
            i2 A = Q.front(); Q.pop();
            int x = A.first;
            int y = A.second;
            if (x == R) continue;
            if (c[x][y] == '?') {
                for (int dy = -1; dy <= 1; dy += 2) {
                    int u = x;
                    int v = y + dy;
                    if (v >= 0 && v < C) {
                        if (c[u][v] == 'X') continue;
                        if (KT[u][v] == 0) {
                            KT[u][v] = 1;
                            Q.push(i2(u, v));
                        }
                    }
                }
            }
            else {
                if (c[x][y] == 'R') {
                    for (int dy = 1; dy <= 1; dy += 2) {
                        int u = x;
                        int v = y + dy;
                        if (v >= 0 && v < C) {
                            if (c[u][v] == 'X') continue;
                            if (KT[u][v] == 0) {
                                KT[u][v] = 1;
                                Q.push(i2(u, v));
                            }
                        }
                    }
                }
                else {
                    if (c[x][y] == 'L') {
                        for (int dy = -1; dy <= -1; dy += 2) {
                            int u = x;
                            int v = y + dy;
                            if (v >= 0 && v < C) {
                                if (c[u][v] == 'X') continue;
                                if (KT[u][v] == 0) {
                                    KT[u][v] = 1;
                                    Q.push(i2(u, v));
                                }
                            }
                        }
                    }
                    else {
                        int u = x + 1;
                        int v = y;
                        if (u == R || c[u][v] != 'X') {
                            if (KT[u][v] == 0) {
                                KT[u][v] = 1;
                                Q.push(i2(u, v));
                            }
                        }
                    }
                }
            }
        }
        for (int j = 0; j < C; j++) {
            if (KT[R][j] == 1) {
                ///cout << i << " " << j << '\n';
                a.c[i][j] = Val[j];
            }
        }
    }
    a = Get(a, K);
    long long Res = 0;
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < C; j++) Res = max(Res, a.c[i][j]);
    }
    cout << Res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ///doc();
    solve();
}
