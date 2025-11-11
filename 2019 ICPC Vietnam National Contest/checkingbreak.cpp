#include <bits/stdc++.h>

using namespace std;
#define TASK "solve"
const int maxN = 2e5 + 100;
void doc() {
    freopen(TASK ".inp", "r", stdin);
    freopen(TASK ".out", "w", stdout);
}

bool Get(int a, int b, int c, int d) {
    return max(a, c) <= min(b, d);
}
void solve() {
    while (true) {
        int a;
        cin >> a;
        if (a == -1) break;
        int b, c;
        cin >> b >> c;
        long long S = 1LL * a * b * c;
        int m;
        cin >> m;
        int x[m], y[m], z[m];
        for (int i = 0; i < m; i++) cin >> x[i] >> y[i] >> z[i];
        int L1[m], R1[m], U1[m], L2[m], R2[m], U2[m];
        bool Check = true;
        for (int i = 0; i < m; i++) cin >> L1[i] >> R1[i] >> U1[i] >> L2[i] >> R2[i] >> U2[i];
        for (int i = 0; i < m; i++) {
            if (L1[i] > L2[i] || R1[i] > R2[i] || U1[i] > U2[i]) Check = false;
            if (L2[i] > a || R2[i] > b || U2[i] > c) Check = false;
            if (x[i] < L1[i] || x[i] > L2[i]) Check = false;
            if (y[i] < R1[i] || y[i] > R2[i]) Check = false;
            if (z[i] < U1[i] || z[i] > U2[i]) Check = false;
            for (int j = i + 1; j < m; j++) {
                if (Get(L1[i], L2[i], L1[j], L2[j]) == false) continue;
                if (Get(R1[i], R2[i], R1[j], R2[j]) == false) continue;
                if (Get(U1[i], U2[i], U1[j], U2[j]) == false) continue;
                Check = false;
            }
            if (S > 0)
                S -= 1LL * (L2[i] - L1[i] + 1) * (R2[i] - R1[i] + 1) * (U2[i] - U1[i] + 1);
        }
        Check &= S == 0;
        if (Check) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ///doc();
    solve();
}
