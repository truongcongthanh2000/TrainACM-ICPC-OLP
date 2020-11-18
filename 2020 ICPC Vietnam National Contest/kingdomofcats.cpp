#include <bits/stdc++.h>

using namespace std;

void doc() {
    #ifdef THEMIS
        freopen("solve.inp", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif
}

const int maxN = 1e3 + 100;
const int INF = 1e6 + 100;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
const int maxv = 2e6 + 10;
const int maxe = 1e7 + 10;

struct Point {
    int x, y;
    Point(){};
};

long long S(Point A, Point B, Point C) {
    Point a[4];
    a[0] = A; a[1] = B; a[2] = C; a[3] = A;
    long long res = 0;
    for (int i = 0; i < 3; i++) {
        res += 1LL * (a[i + 1].x - a[i].x) * (a[i + 1].y + a[i].y);
    }
    return res;
}

bool check(Point A, Point B, Point C, Point D) {
    if (S(A, C, B) > 0 && S(A, D, B) < 0) return true;
    if (S(A, C, B) < 0 && S(A, D, B) > 0) return true;
    return false;
}

bool ok(Point A, Point B, Point C, Point D) {
    if (check(A, B, C, D) && check(C, D, A, B)) return true;
    if (check(A, C, B, D) && check(B, D, A, C)) return true;
    if (check(A, D, B, C) && check(B, C, A, D)) return true;
    return false;
}
Point a[maxN];
void sol() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
        int res = 0;
        for (int i = 1; i <= n - 3; i++) {
            for (int j = i + 1; j <= n - 2; j++) {
                for (int u = j + 1; u <= n - 1; u++) {
                    for (int v = u + 1; v <= n; v++) {
                        bool has = ok(a[i], a[j], a[u], a[v]);
                        res += has;
                    }
                }
            }
        }
        cout << res << '\n';
    }
}

void solve() {
    int T;
    //cin >> T;
    T = 1;
    while (T--) {
        sol();
    }
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
