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
    long long p, n;
    cin >> p >> n;
    int arr[p];
    for (int i = 0; i < p; i++) arr[i] = 0;
    arr[0] = 1;
    if (n >= p) n = p - 1;
    long long pos = 0;
    for (int i = 1; i <= n; i++) {
        pos = (pos + i)%p;
        arr[pos] = 1;
    }
    long long res = 0;
    for (int i = 0; i < p; i++) res += arr[i];
    cout << res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
