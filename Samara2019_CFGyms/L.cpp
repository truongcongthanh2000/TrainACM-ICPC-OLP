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
    long double x1, x2, y1, y2, r1, r2;
    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;
    long double O1O2 = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    long double R = (r1 + r2 - O1O2)/2;
    long double x = (r1 - R)*(x2 - x1)/O1O2 + x1;
    long double y = (r1 - R)*(y2 - y1)/O1O2 + y1;
    cout << fixed << setprecision(10) << x;
    cout << " " << fixed << setprecision(10) << y;
    cout << " " << fixed << setprecision(10) << R;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //oc();
    solve();
}
