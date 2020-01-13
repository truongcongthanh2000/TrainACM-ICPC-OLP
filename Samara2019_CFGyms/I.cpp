#include <bits/stdc++.h>
using namespace std;
const int MaxN=100005*2;
int n;
vector <int> a[MaxN];

void doc()
{
    freopen("OB.inp","r",stdin);
    freopen("OB.out","w",stdout);
}

void solve() {
    int a, b; cin >> a >> b;
    long long res = 0;
    while (a > b) {
        res += 3*(a - b);
        a -= 2*b;
        if (a > 0) res += a;
        if (a < b) res += max(a, 0);
        else res += b;
    }
    cout << res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
