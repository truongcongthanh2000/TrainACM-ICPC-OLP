#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e5 + 1000;
const int maxn = 105;

struct SegmentTree{
    long long IT[maxN * 4];
    SegmentTree(){
        for (int i = 0; i < maxN * 4; i++) IT[i] = -INF_LL;
    };
    void update(int k, int l, int r, int u, long long val){
        if (u < l || u > r) return;
        if (l == r){
            IT[k] = max(IT[k], val);
            return;
        }
        int mid = (l + r) / 2;
        update(k * 2, l, mid, u, val);
        update(k * 2 + 1, mid + 1, r, u, val);
        IT[k] = max(IT[k * 2], IT[k * 2 + 1]);
    }

    long long get(int k, int l, int r, int u, int v){
        if (v < l || u > r) return -INF_LL;
        if (u <= l && r <= v) return IT[k];
        int mid = (l + r) / 2;
        long long L = get(k * 2, l, mid, u, v);
        long long R = get(k * 2 + 1, mid + 1, r, u, v);
        return max(L, R);
    }
};

struct Query{
    int k, l, r, value;
    Query(int _k, int _l, int _r, int _value): k(_k), l(_l), r(_r), value(_value) {}
};

typedef pair<int, int> i2;
vector<i2> a[maxn];
vector<Query> q;
SegmentTree T[maxn];
long long f[maxn][maxn];
void sol(){
    int Q, n, m;
    cin >> Q >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) f[i][j] = INF_LL;
        f[i][i] = 0;
    }
    for(int i = 0; i < m; i++){
        int x, y, w;
        cin >> x >> y >> w;
        f[x][y] = w;
        f[y][x] = w;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }

    vector<int> c;
    c.push_back(0);
    for(int i = 0; i < Q; i++){
        int k, l, r, val;
        cin >> k >> l >> r >> val;
        q.push_back(Query(k, l, r, val));
        //c.push_back(l);
        c.push_back(r);
    }
    sort(c.begin(), c.end());
    c.resize(unique(c.begin(), c.end()) - c.begin());
    int m_ = 0;
    for(int i = 0; i < Q; i++){
        int r = lower_bound(c.begin(), c.end(), q[i].r) - c.begin();
        m_ = max(m_, r);
    }

    sort(q.begin(), q.end(), [&](Query A, Query B){
//        if (A.r != B.r) return A.r < B.r;
//        return A.value > B.value;
        return A.l < B.l;
    });
    T[1].update(1, 0, m_, 0, 0);
    long long res = 0;
//    cout << Q << '\n';
    for(int i = 0; i < Q; i++){
        int L = q[i].l;
        int R = q[i].r;
        int u = q[i].k;
        int desR_u = lower_bound(c.begin(), c.end(), R) - c.begin();
        long long res_u = -INF_LL;
        for(int v = 1; v <= n; v++){
            int cost = f[u][v];
            int desR_v = upper_bound(c.begin(), c.end(), L - cost) - c.begin() - 1;
            res_u = max(res_u, T[v].get(1, 0, m_, 0, desR_v));
        }
        res_u += q[i].value;
        if (res_u >= 0) T[u].update(1, 0, m_, desR_u, res_u);
        res = max(res, res_u);
//        cout << res_u << '\n';
    }
    cout << res;
}

void solve() {
    int T;
//    cin >> T;
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
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
