#include <bits/stdc++.h>

using namespace std;

void doc() {
    #ifdef THEMIS
        freopen("solve.inp", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif // THEMIS
}

void sol() {
    int n;
    cin >> n;
    char old = '?';
    int ans = 0;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        ans += old == c;
        old = c;
    }
    cout << ans;
}

void solve() {
    int T;
    T = 1;
    //cin >> T;
    while (T--) sol();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
