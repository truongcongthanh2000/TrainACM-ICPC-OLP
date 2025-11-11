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
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i].L >> a[i].R;
        a[i].cs = i;
    }
    int T = 1,i = 0,d = 0;
    sort(a,a+n,ss);
    while (T <= m && i < n){
        if (a[i].L > T){
            cout << "NO";
            return;
        }
        while (i < n && a[i].L <= T){
            if (a[d].R < a[i].R)
                d = i;
            i++;
        }
        c.push_back(a[d].cs);
        T = a[d].R + 1;
    }
    if (T > m){
        cout << "YES" << '\n';
        cout << c.size() << '\n';
        for (int i = 0; i < c.size(); i++)
            cout << c[i]+1 << " ";
    }
    else cout << "NO";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
   // doc();
    solve();
}
