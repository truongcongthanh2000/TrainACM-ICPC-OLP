#include <bits/stdc++.h>

using namespace std;

void doc() {
    freopen("OB.inp", "r", stdin);
    freopen("OB.out", "w", stdout);
}

int GCD(int x, int y) {
    return y == 0 ? abs(x) : GCD(y, x % y);
}
void solve() {
    int Test;
    cin >> Test;
    while (Test--) {
        int xL, yL, xR, yR;
        cin >> xL >> yL >> xR >> yR;
        int val1 = GCD(xL, yL);
        int val2 = GCD(xR, yR);
        bool Check = val1 == val2;
        if (Check) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
