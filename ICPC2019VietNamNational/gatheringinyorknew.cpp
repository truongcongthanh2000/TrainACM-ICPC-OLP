#include <bits/stdc++.h>

using namespace std;
#define TASK "solve"
const int maxN = 2e5 + 100;
void doc() {
    freopen(TASK ".inp", "r", stdin);
    freopen(TASK ".out", "w", stdout);
}

long long a[maxN];
long long s[maxN];
int n;
//long long Get(int x) {
//    long long Res = 0;
//    for (int i = 1; i <= n; i++) {
//        Res = Res + min(abs(x), abs(x - a[i]));
//    }
//    return Res;
//}
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i + 1];
    a[++n] = 0;
    sort(a + 1, a + 1 + n);
    long long Res = 1e18;
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
    for (int i = 1; i <= n; i++) {
        if (a[i] < 0) {
            long long L = 1LL * a[i] * i - s[i];
            int id = lower_bound(a + 1, a + 1 + n, 0) - a;
            long long R = s[n] - s[id - 1];
            int mid = a[i] / 2;
            int prev = lower_bound(a + 1, a + 1 + n, mid + 1) - a;
            prev--;
            long long Giua = (1LL * (prev - i) * a[i] + (s[i] - s[prev])) + s[id] - s[prev];
            Giua = 0LL - Giua;
            ///cout << i << " " << L << " " << R << " " << Giua << " " << id << " " << prev << '\n';
            Res = min(Res, L + R + Giua);
        }
        else {
            long long R = s[n] - s[i] - 1LL * (n - i) * a[i];
            int id = lower_bound(a + 1, a + 1 + n, 0) - a;
            long long L = 0LL - s[id];
            int mid = a[i] / 2;
            int prev = lower_bound(a + 1, a + 1 + n, mid + 1) - a;
            prev--;
            long long Giua = s[prev] - s[id] + (1LL * (i - prev) * a[i]) - (s[i] - s[prev]);
            ///cout << L << " " << R << " " << Giua << " " << id << " " << prev << '\n';
            Res = min(Res, L + R + Giua);
        }
    }
    cout << Res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ///doc();
    solve();
}
