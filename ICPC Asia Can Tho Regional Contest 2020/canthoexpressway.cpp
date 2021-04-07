#include <bits/stdc++.h>

using namespace std;

void doc() {
    #ifdef THEMIS
        freopen("solve.inp", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif // THEMIS
}

struct Point {
    int x, y;
    Point(){};
};

void sol() {
    int a, b, c[2];
    cin >> a >> b >> c[0] >> c[1];
    auto get = [&](Point O, int i) {
        return a * O.x + b * O.y - c[i];
    };
    int k;
    cin >> k;
    vector<Point> p(k);
    for (int i = 0; i < k; i++) cin >> p[i].x >> p[i].y;
    for (int i = 0; i < k; i++) {
        int j = (i + 1) % k;
        for (int cc = 0; cc < 2; cc++) {
            int a1 = get(p[i], cc);
            int a2 = get(p[j], cc);
            if (1LL * a1 * a2 < 0) {
                cout << "YES" << '\n';
                return;
            }
            if (get(p[i], cc) == 0 && get(p[j], 1 - cc) == 0) {
                cout << "YES" << '\n';
                return;
            }
        }
    }
    for (int i = 0; i < k; i++) {
        int x = get(p[i], 0);
        int y = get(p[i], 1);
        if (1LL * x * y < 0) {
            cout << "YES" << '\n';
            return;
        }
    }
    cout << "NO" << '\n';
}

void solve() {
    int T;
    //T = 1;
    cin >> T;
    while (T--) sol();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
