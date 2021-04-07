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

int GCD(int a, int b) {
    return b == 0 ? a : GCD(b, a % b);
}
void solve() {
    int Test;
    cin >> Test;
    while (Test--) {
        int n; cin >> n;
        int a[n], b[n], H[n];
        int sumA = 0, sumB = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i];
            sumA += a[i] * b[i];
            sumB += b[i];
            H[i] = i;
        }
        sort(H, H + n, [&](int i, int j){
            return a[i] > a[j];
        });
        vector <int> Res;
        for (int i = 0; i < n; i++) {
            int id = H[i];
            if (1LL * sumB * a[id] > sumA) {
                sumA += a[id];
                sumB++;
                Res.push_back(id);
            }
        }
        int x = GCD(sumA, sumB);
        cout << sumA / x << "/" << sumB / x << '\n';
        cout << (int)Res.size() << '\n';
        for (int x : Res) cout << x + 1 << ' ';
        cout << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
