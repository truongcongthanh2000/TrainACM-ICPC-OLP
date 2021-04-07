#include <bits/stdc++.h>
using namespace std;
const int MaxN = 1e6+5;

int n, m, q, P[1005][1005];
void doc() {
    freopen("OB.inp","r",stdin);
    freopen("OB.out","w",stdout);
}

int GCD(int a, int b) {
    return b == 0 ? a : GCD(b, a % b);
}
void solve() {
    int n; cin >> n;
    while (n--) {
        string S, T;
        cin >> S >> T;
        bool Check1 = false;
        int aa = 0;
        int SL = 0;
        int Type = 0;
        for (int i = 0; i <= 10; i++) {
            if (i < (int)S.size() && S[i] == '.') {
                Type = 1;
                continue;
            }
            if (Type == 0 && i == (int)S.size()) {
                Type = 1;
            }
            aa = aa * 10 + (i >= (int)S.size() ? 0 : S[i] - '0');
            SL += Type;
            if (SL == 5) break;
        }
        int bb = 0;
        SL = 0;
        Type = 0;
        for (int i = 0; i <= 10; i++) {
            if (i < (int)T.size() && T[i] == '.') {
                Type = 1;
                continue;
            }
            if (Type == 0 && i == (int)T.size()) {
                Type = 1;
            }
            bb = bb * 10 + (i >= (int)T.size() ? 0 : T[i] - '0');
            SL += Type;
            if (SL == 5) break;
        }
        //cerr << aa << " " << bb << '\n';
        int gcd = GCD(aa, bb);
        aa /= gcd;
        bb /= gcd;
        //cerr << aa << " " << bb << '\n';
        if (min(aa, bb) == 1) {
            if (aa == bb) cout << 2 << " " << 2 << '\n';
            else cout << "impossible" << endl;
            continue;
        }
        int able = 1;
        for (int i = 2; i*i <= aa; i++) {
            if (aa%i == 0) {
                able = 0;
                break;
            }
        }
        for (int i = 2; i*i <= bb; i++) {
            if (bb%i == 0) {
                able = 0;
                break;
            }
        }
        if (able) cout << aa << " " << bb;
        else cout << "impossible";
        cout << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
