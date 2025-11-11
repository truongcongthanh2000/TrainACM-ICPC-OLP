#include <bits/stdc++.h>

using namespace std;

void doc()
{
    freopen("solve.inp","r",stdin);
    freopen("solve.out","w",stdout);
}

int Ask(int id, int b) {
    cout << "? " << id << " " << b << '\n';
    fflush(stdout);
    int x;
    cin >> x;
    return x;
}
int lg(int n) {
    int Res = 0;
    for (int i = 0; i < n; i++) {
        if ((1 << i) > n) break;
        Res = i;
    }
    return Res;
}
void solve() {
    int n;
    cin >> n;
    vector <int> a;
    for (int i = 0; i <= n; i++) a.push_back(i);
    int lm = lg(n);
    int KT[n];
    memset(KT, 0, sizeof(KT));
    int Ans[n];
    for (int pBit = 0; pBit <= lm; pBit++) {
        int D[2];
        D[0] = D[1] = 0;
        for (int x : a) {
            int bit = (x >> pBit) & 1;
            D[bit]++;
        }
        for (int i = 0; i < n; i++) {
            if (KT[i] == 0) {
                int bit = Ask(i + 1, pBit);
                Ans[i] = bit;
                D[bit]--;
            }
        }
        vector <int> b;
        for (int bit = 0; bit <= 1; bit++) {
            if (D[bit] > 0) {
                for (int x : a) {
                    int vBit = (x >> pBit) & 1;
                    if (vBit == bit) b.push_back(x);
                }
            }
        }
        a = b;
        for (int i = 0; i < n; i++) {
            if (KT[i] == 0) {
                int bit = Ans[i];
                if (D[bit] == 0) {
                    KT[i] = 1;
                }
            }
        }
    }
    cout << "! " << a[0];
    fflush(stdout);
}

int main(){
    ios_base::sync_with_stdio(1); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
