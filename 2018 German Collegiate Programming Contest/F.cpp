#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e6+5;

void doc() {
    freopen("OB.inp","r",stdin);
    freopen("OB.out","w",stdout);
}
void solve(){
    vector <int> Fibo;
    Fibo.push_back(1);
    Fibo.push_back(1);
    int oo = 1e6;
    int D[oo + 100];
    memset(D, 0, sizeof(D));
    int M = 2;
    for (int i = 1; i <= 100; i++) {
        int x = Fibo[M - 1] + Fibo[M - 2];
        //cerr << x << '\n';
        if (x > 2 * oo) break;
        Fibo.push_back(x);
        M++;
    }
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x == 1) {
            if (D[1]) {
                cout << D[1] << " " << i;
                return;
            }
            D[1] = i;
        }
        else {
            //cerr << "OK" << '\n';
            auto id = lower_bound(Fibo.begin(), Fibo.end(), x);
            if (*id != x) continue;
            int oldW = *(--id);
            id++;
            id++;
            int newW = *id;
            if (D[oldW]) {
                cout << D[oldW] << " " << i;
                return;
            }
            if (D[newW]) {
                cout << i << " " << D[newW];
                return;
            }
            D[x] = i;
        }
    }
    cout << "impossible";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
