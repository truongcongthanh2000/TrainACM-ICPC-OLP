#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e6+5;

void doc() {
    freopen("OB.inp","r",stdin);
    freopen("OB.out","w",stdout);
}
long long pw(long long x, int n) {
    long long Res = 1;
    for (; n; n = n >> 1, x = x * x) {
        if (n & 1) Res = Res * x;
    }
    return Res;
}
void solve(){
    long long oo = 1e16;
    long long m;
    cin >> m;
    for (int n = 3; n <= 60; n++) {
        long long T = 0;
        int S = 1;
        while (T += pw(S, n - 1)) {
            if (T > m) break;
            if (T == m) {
                cout << n << " " << S;
                return;
            }
            S++;
        }
    }
    cout << "impossible";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
