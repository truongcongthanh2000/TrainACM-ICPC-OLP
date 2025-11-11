#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e6+5;

void doc() {
    freopen("OB.inp","r",stdin);
    freopen("OB.out","w",stdout);
}
void solve(){
    int n;
    cin >> n;
    int a[n], b[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    int L = 0;
    int R = 1e9;
    int Res = 1e9;
    while (L <= R) {
        int mid = (L + R) >> 1;
        bool Check = true;
        //cout << mid << '\n';
        for (int i = 0; i < n; i++) {
            int x = a[i] + mid;
            int y = b[i];
            //cout << x << " " << y << '\n';
            if (x > y) break;
            if (x < y) {
                Check = false;
                break;
            }
        }
        if (Check) {
            Res = mid;
            R = mid - 1;
        }
        else L = mid + 1;
    }
    cout << Res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
