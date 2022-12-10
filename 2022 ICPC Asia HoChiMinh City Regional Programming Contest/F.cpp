#include <bits/stdc++.h>

using namespace std;

void open_file() {
    #ifdef THEMIS
        freopen("sol.inp", "r", stdin);
        freopen("sol.out", "w", stdout);
    #endif // THEMIS
}

void sol() {
    long long n, x0, y0, a, b;
    cin >> n >> x0 >> y0 >> a >> b;
    double ans = 1.0 * (n) * sqrt(a * a + b * b) / 2.0;
    cout << fixed << setprecision(10) << ans;

}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    int t = 1;
//    cin >> t;
    while (t--) sol();
}
