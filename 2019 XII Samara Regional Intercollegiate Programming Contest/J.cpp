#include <bits/stdc++.h>
using namespace std;
const int MaxN=100005*2;
int n,m;
struct data
{
    int L,R,cs;
}a[MaxN];
vector <int> c;

void doc()
{
    freopen("OB.inp","r",stdin);
    freopen("OB.out","w",stdout);
}

bool ss (data i, data j){
    return i.L < j.L;
}

void solve() {
    int n; cin >> n;
    long long twoMin[n];
    long long summ[n];
    for (int i = 0; i < n; i++) {
        long long x, y, z;
        cin >> x >> y >> z;
        long long minn = min(min(x, y), z);
        long long maxx = max(max(x, y), z);
        long long midd = x + y + z - minn - maxx;
        twoMin[i] = minn + midd;
        summ[i] = twoMin[i] + maxx;
    }
    int arr[n];
    for (int i = 0; i < n; i++) arr[i] = twoMin[i];
    sort(twoMin, twoMin + n);
    int ans[n];
    for (int i = 0; i < n; i++) {
        int pos = upper_bound(twoMin, twoMin + n, summ[i] - 2) - twoMin;
        ans[i] = pos;
        if (summ[i] - 2 >= arr[i]) ans[i]--;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i]
         << " ";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
