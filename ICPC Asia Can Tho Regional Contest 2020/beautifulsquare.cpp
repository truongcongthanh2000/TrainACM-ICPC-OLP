#include <bits/stdc++.h>

using namespace std;

void doc() {
    #ifdef THEMIS
        freopen("solve.inp", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 100;
const long long INF = 1e18 + 100;


void sol() {
    int n, x, y;
    cin >> n >> x >> y;
    vector<vector<int> > a(n + 2, vector<int>(n + 2, 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) a[i][j] = 0;
    }
    int d = 0;
    auto f = [&](int x, int y) {
        assert(x >= 1 && x <= n && y >= 1 && y <= n && a[x][y] == 0);
        d++;
        a[x][y] = d;
    };
    if (n % 2 == 0) {
        if (x & 1) {
            int num = 0;
            while (x > 1) {
                f(x, y);
                x--;
                num++;
            }
            if (y == 1) {
                int dy = 1;
                for (; num < n * n; ) {
                    f(x, y);
                    num++;
                    int v = y + dy;
                    if (a[x][v] > 0) {
                        x++;
                        dy *= -1;
                    }
                    else y = v;
                }
            }
            else {
                int dy = -1;
                int tmp = y;
                for (; num < n * n && x != n; ) {
                    f(x, y);
                    num++;
                    int v = y + dy;
                    if (a[x][v] > 0 || v > tmp) {
                        x++;
                        dy *= -1;
                    }
                    else y = v;
                }
                assert(dy == 1);
                for (; num < n * n; ) {
                    f(x, y);
                    num++;
                    int v = y + dy;
                    if (a[x][v] > 0) {
                        x--;
                        dy *= -1;
                    }
                    else y = v;
                }
            }
        }
        else {
            int num = 0;
            while (x < n) {
                f(x, y);
                x++;
                num++;
            }
            if (y == 1) {
                int dy = 1;
                for (; num < n * n; ) {
                    f(x, y);
                    num++;
                    int v = y + dy;
                    if (a[x][v] > 0) {
                        x--;
                        dy *= -1;
                    }
                    else y = v;
                }
            }
            else {
                int dy = -1;
                int tmp = y;
                for (; num < n * n && x != 1; ) {
                    f(x, y);
                    num++;
                    int v = y + dy;
                    if (a[x][v] > 0 || v > tmp) {
                        x--;
                        dy *= -1;
                    }
                    else y = v;
                }
                assert(dy == 1);
                for (; num < n * n; ) {
                    f(x, y);
                    num++;
                    int v = y + dy;
                    if (a[x][v] > 0) {
                        x++;
                        dy *= -1;
                    }
                    else y = v;
                }
            }
        }
        cout << "YES" << '\n';
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) cout << a[i][j] << ' ';
            cout << '\n';
        }
        return;
    }
    else {
        if (x % 2 != y % 2) {
            cout << "NO" << '\n';
            return;
        }
        if (x % 2 == 0) {
            int tmp_y = y;
            int dx = -1;
            int num = 0;
            int tmp = x;
            for (; num < n * n && y != 1; ) {
                f(x, y);
                num++;
                int u = x + dx;
                if (a[u][y] > 0 || u > tmp) {
                    y--;
                    dx *= -1;
                }
                else x = u;
            }
            assert(dx == 1);
            while (x <= tmp) {
                f(x, y);
                x++;
                num++;
            }
            int dy = 1;
            for (; num < n * n && x != n; ) {
                f(x, y);
                num++;
                int v = y + dy;
                if (a[x][v] > 0 || v > tmp_y) {
                    x++;
                    dy *= -1;
                }
                else y = v;
            }
            assert(dy == 1);
            for (; num < n * n; ) {
                f(x, y);
                num++;
                int v = y + dy;
                if (a[x][v] > 0) {
                    x--;
                    dy *= -1;
                }
                else y = v;
            }
        }
        else {
            int num = 0;
            if (x == n) {
                int tmp_y = y;
                while (y < n) {
                    f(x, y);
                    y++;
                    num++;
                }
                int dx = -1;
                for (; num < n * n; ) {
                    f(x, y);
                    num++;
                    int u = x + dx;
                    if (a[u][y] > 0) {
                        y--;
                        dx *= -1;
                    }
                    else x = u;
                }
            }
            else {
                int num = 0;
                if (y == 1) {
                    while (x < n) {
                        f(x, y);
                        x++;
                        num++;
                    }
                    int dy = 1;
                    assert(dy == 1);
                    for (; num < n * n; ) {
                        f(x, y);
                        num++;
                        int v = y + dy;
                        if (a[x][v] > 0) {
                            x--;
                            dy *= -1;
                        }
                        else y = v;
                    }
                }
                else {
                    int tmp_x = x;
                    int tmp_y = y;
                    while (x > 1) {
                        f(x, y);
                        x--;
                        num++;
                    }
                    int dy = -1;
                    for (; num < n * n && x != tmp_x; ) {
                        f(x, y);
                        num++;
                        int v = y + dy;
                        if (a[x][v] > 0 || v > tmp_y) {
                            x++;
                            dy *= -1;
                        }
                        else y = v;
                    }
                    assert(dy == -1);
                    while (y > 1) {
                        f(x, y);
                        y--;
                        num++;
                    }
                    int dx = 1;
                    for (; num < n * n && (x != n || y != tmp_y); ) {
                        f(x, y);
                        num++;
                        int u = x + dx;
                        if (a[u][y] > 0) {
                            y++;
                            dx *= -1;
                        }
                        else x = u;
                    }
                    {
                        int dy = 1;
                        assert(dy == 1);
                        for (; num < n * n; ) {
                            f(x, y);
                            num++;
                            int v = y + dy;
                            if (a[x][v] > 0) {
                                x--;
                                dy *= -1;
                            }
                            else y = v;
                        }
                    }
                }
            }
        }
        cout << "YES" << '\n';
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) cout << a[i][j] << ' ';
            cout << '\n';
        }
    }
}

void solve() {
    int T;
    //T = 1;
    cin >> T;
    while (T--) {
        sol();
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
