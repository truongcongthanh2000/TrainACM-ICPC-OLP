#include <bits/stdc++.h>

using namespace std;

void doc() {
    #ifdef THEMIS
        freopen("solve.inp", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif
}

const int maxN = 1e3 + 100;
const int INF = 1e9 + 100;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void sol() {
    int xL, yL, xR, yR;
    cin >> xL >> yL >> xR >> yR;
    auto get = [&](int x1, int y1, int x2, int y2) -> long long {
        int k = abs(x2 - x1);
        long long res = 1e18;
        for (int dx = -1; dx <= 1; dx += 2) {
            int y11 = y1 + dx * k;
            long long cost = 2LL * k + 1LL * abs(y2 - y11) / 2 * 4 + (abs(y2 - y11) % 2);
            res = min(res, cost);
        }
        return res;
    };
    cout << min(get(xL, yL, xR, yR), get(yL, xL, yR, xR)) << '\n';
}

void solve() {
    int T;
    cin >> T;
    //T = 1;
    while (T--) {
        sol();
    }
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
