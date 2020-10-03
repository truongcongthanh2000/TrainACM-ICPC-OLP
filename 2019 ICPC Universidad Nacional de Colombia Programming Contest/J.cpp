#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

int num[maxN * 4];
long long IT[maxN * 4], lazy[maxN * 4];
long long mn[maxN * 4];
int a[maxN];

void build(int i, int L, int R) {
    num[i] = (R - L + 1);
    if (L == R) {
        IT[i] = mn[i] = a[L];
        return;
    }
    int mid = (L + R) >> 1;
    build(i << 1, L, mid);
    build(i << 1 | 1, mid + 1, R);
    IT[i] = IT[i << 1] + IT[i << 1 | 1];
    mn[i] = min(mn[i << 1], mn[i << 1 | 1]);
}
void push_down(int i, int L, int R) {
    if (lazy[i] == 0) return;
    IT[i] -= lazy[i] * num[i];
    mn[i] -= lazy[i];
    if (L != R) {
        lazy[i << 1] += lazy[i];
        lazy[i << 1 | 1] += lazy[i];
    }
    lazy[i] = 0;
}

void update(int i, int L, int R, int u, int v, int val) {
    push_down(i, L, R);
    if (L > v || R < u) return;
    if (L >= u && R <= v && val <= mn[i]) {
        lazy[i] = val;
        push_down(i, L, R);
        return;
    }
    if (L == R && val >= mn[i]) {
        IT[i] = num[i] = 0;
        mn[i] = INF_LL;
        lazy[i] = 0;
        return;
    }
    int mid = (L + R) >> 1;
    update(i << 1, L, mid, u, v, val);
    update(i << 1 | 1, mid + 1, R, u, v, val);
    IT[i] = IT[i << 1] + IT[i << 1 | 1];
    num[i] = num[i << 1] + num[i << 1 | 1];
    mn[i] = min(mn[i << 1], mn[i << 1 | 1]);
}

long long get(int i, int L, int R, int u, int v) {
    push_down(i, L, R);
    if (L > v || R < u) return 0;
    if (L >= u && R <= v) return IT[i];
    int mid = (L + R) >> 1;
    long long Left = get(i << 1, L, mid, u, v);
    long long Right = get(i << 1 | 1, mid + 1, R, u, v);
    return Left + Right;
}

void sol() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int L, R;
            cin >> L >> R;
            if (L > R) cout << get(1, 1, n, L, n) + get(1, 1, n, 1, R) << '\n';
            else cout << get(1, 1, n, L, R) << '\n';
        }
        else {
            int L, R, x;
            cin >> L >> R >> x;
            if (L > R) {
                update(1, 1, n, L, n, x);
                update(1, 1, n, 1, R, x);
            }
            else {
                update(1, 1, n, L, R, x);
            }
        }
    }
}

void solve() {
    int T;
    //cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
