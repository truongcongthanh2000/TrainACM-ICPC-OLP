#include <bits/stdc++.h>

using namespace std;

void doc()
{
    freopen("solve.inp","r",stdin);
    freopen("solve.out","w",stdout);
}
///L - 10 <= a1 + a2 + ... + ak <= L + 5 * (k - 1)
void solve() {
    int n, L;
    cin >> n >> L;
    int oo = 5000;
    bool F[n + 1][oo];
    memset(F, 0, sizeof(F));
    F[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        for (int k = i; k >= 1; k--) {
            for (int j = oo - 1; j >= x; j--) {
                F[k][j] |= F[k - 1][j - x];
            }
        }
    }
    long double Res = -1.0;
    for (int k = 1; k <= n; k++) {
        int m = L + 5 * (k - 1);
        while (m >= 0 && F[k][m] == false) m--;
        //cout << k << " " << m << '\n';
        if (m == -1) continue;
        if (L - 10 <= m && m <= L + (k - 1) * 5) {
            long double Val = 1.0 * m - L + 10;
            Val = Val / (1.0 * (k + 1));
            Res = max(Res, Val);
        }
    }
    if (Res == -1.0) cout << "impossible";
    else cout << fixed << setprecision(10) << Res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
