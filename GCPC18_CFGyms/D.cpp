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
    int a[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    int x[n + 1];
    int L = 0;
    int R = a[0] + 1;
    int L1 = -1;
    int R1 = a[0] + 1;
    while (L <= R) {
        int mid = (L + R) >> 1;
        x[0] = mid;
        bool Check = false;
        for (int i = 1; i <= n; i++) {
            x[i] = a[i - 1] - x[i - 1];
            if (x[i] < 0) {
                if (i % 2 == 1) {
                    Check = true;
                    break;
                }
                else break;
            }
        }
        if (Check) {
            R1 = mid;
            R = mid - 1;
        }
        else L = mid + 1;
    }
    L = 0;
    R = (int)a[0] + 1;
    while (L <= R) {
        int mid = (L + R) >> 1;
        x[0] = mid;
        bool Check = false;
        for (int i = 1; i <= n; i++) {
            x[i] = a[i - 1] - x[i - 1];
            if (x[i] < 0) {
                if (i % 2 == 0) {
                    Check = true;
                    break;
                }
                else break;
            }
        }
        if (Check) {
            L = mid + 1;
            L1 = mid;
        }
        else R = mid - 1;
    }
    //cout << L1 << " " << R1 << "\n";
    cout << max(0, R1 - L1 - 1);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
