#include <bits/stdc++.h>
using namespace std;
string s1,s2;
int d[100005],a[100005],b[5][10005];

void doc()
{
    freopen("OB.inp","r",stdin);
    freopen("OB.out","w",stdout);
}

void solve() {
    int n;
    cin >> n;
    int D[n + 1];
    memset(D, 0, sizeof(D));
    int L = 1;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x < 0) {
            x *= -1;
            D[x] = i;
        }
        else {
            if (D[x] != 0) {
                while (L <= D[x]) {
                    cout << i - L << ' ';
                    L++;
                }
            }
            D[x] = 0;
        }
    }
    while (L <= n) cout << n + 1 - L++ << ' ';
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
