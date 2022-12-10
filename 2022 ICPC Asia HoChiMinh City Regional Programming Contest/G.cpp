#include <bits/stdc++.h>

using namespace std;

void open_file() {
    #ifdef THEMIS
        freopen("sol.inp", "r", stdin);
        freopen("sol.out", "w", stdout);
    #endif // THEMIS
}

void sol() {
    int n, r, x1, x2;
    cin >> n >> r >> x1 >> x2;

    bool ok = false;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        if (x1 < x2) {
            ok |= p + r <= x1;
        } else {
            ok |= p - r >= x1;
        }
    }
    if (ok) cout << "GOAL";
    else cout << "NO GOAL";

}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    int t = 1;
//    cin >> t;
    while (t--) sol();
}
