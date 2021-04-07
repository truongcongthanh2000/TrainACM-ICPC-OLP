#include <bits/stdc++.h>

using namespace std;

void doc() {
    freopen("OB.inp", "r", stdin);
    freopen("OB.out", "w", stdout);
}

int SL(int n) {
    return n < 10 ? 1 : SL(n / 10) + 1;
}
int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res -= res / i;
        }
    }
    if (n != 1) {
        res -= res / n;
    }
    return res;
}
const int oo = 1e6 + 10;
bool F[oo + 1];
void solve() {
    for (int i = 0; i <= oo; i++) F[i] = false;
    F[1] = true;
    for (int i = 2; i < oo; i++) {
       bool x = F[i - 1];
       bool y = F[i - SL(i)];
       bool z = F[i - phi(i)];
       if ((x & y & z) == false) F[i] = true;
    }
    int Test;
    cin >> Test;
    while (Test--) {
        int n;
        cin >> n;
        cout << (F[n] ? "BACH" : "KHOA") << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
}
