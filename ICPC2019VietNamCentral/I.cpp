#include <bits/stdc++.h>

using namespace std;

void doc() {
    freopen("OB.inp", "r", stdin);
    freopen("OB.out", "w", stdout);
}
const int maxN = 1e5 + 100;
int GCD(int a, int b) {
    return b == 0 ? a : GCD(b, a % b);
}
int IT[maxN * 4], n;
void up(int i, int L, int R, int u, int val) {
    if (L > u || R < u) return;
    if (L == R) {
        IT[i] = val;
        return;
    }
    int mid = (L + R) >> 1;
    up(i << 1, L, mid, u, val);
    up(i << 1 | 1, mid + 1, R, u, val);
    IT[i] = GCD(IT[i << 1], IT[i << 1 | 1]);
}
int Get(int i, int L, int R, int u, int v) {
    if (L > v || R < u) return 0;
    if (L >= u && R <= v) return IT[i];
    int mid = (L + R) >> 1;
    int Left = Get(i << 1, L, mid, u, v);
    int Right = Get(i << 1 | 1, mid + 1, R, u, v);
    return GCD(Left, Right);
}
int n;
int b[maxN][20];
int lg(int n) {
    int Res = 0;
    while (n > 1) {
        Res++;
        n /= 2;
    }
    return Res;
}
int Get(int L, int R) {
    int k = lg(R - L + 1);
    return GCD(b[L][k], b[R - (1 << k) + 1][k]);
}
int Jump(int x, int L, int R) {
    int tmp = L;
    int Res = n + 1;
    while (L <= R) {
        int mid = (L + R) >> 1;
        int val = Get(tmp, mid); ///Get(1, 1, n, tmp, mid);
        if (val % x != 0) {
            Res = mid;
            R = mid - 1;
        }
        else L = mid + 1;
    }
    return Res;
}
const int oo = 1e5 + 10;
int a[maxN];
map <int, long long> M;
void Jump(int id, int x) {
    int L = id;
    while (1 < 2) {
        int R = Jump(x, id, n);
        M[x] += R - L;
        //cout << x << " " << L << " " << R << '\n';
        if (R == n + 1) return;
        x = Get(id, R);
        ///x = Get(1, 1, n, id, R);
        L = R;
    }
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i][0] = a[i];
        //up(1, 1, n, i, a[i]);
    }
    for (int j = 1; j < 20; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            b[i][j] = GCD(b[i][j - 1], b[i + (1 << (j - 1))][j - 1]);
    }
    for (int i = 1; i <= n; i++) Jump(i, a[i]);
    int Test;
    cin >> Test;
    while (Test--) {
        int x;
        cin >> x;
        cout << M[x] << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
}
