#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const double EPS = 1e-9;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e5 + 100;

long long arr[maxN];

struct node {
    long long left, right, val, sum;
    int pos;
    node(long long x) {
        val = sum = left = right = x;
    }
    node(long long _left, long long _right, long long _val, long long _sum) {
        val = _val;
        sum = _sum;
        left = _left;
        right = _right;
    }
    node() {
        val = 0;
        sum = 0;
        left = 0;
        right = 0;
    }
};
struct SegmentTree{
    node ST[maxN * 4];
    SegmentTree(){};

    node Merge(node a, node b) {
        node res = node();
        res.left = max(a.left, a.sum + b.left);
        res.right = max(b.right, b.sum + a.right);
        res.val = max(a.val, b.val);
        res.val = max(res.val, a.right + b.left);
        res.sum = a.sum + b.sum;
        return res;
    }

    void update(int id, int l, int r, int u, long long val) {
        if (l > u || r < u) {
            return;
        }
        if (l == r) {
            ST[id] = node(val);
            return;
        }
        int mid = (l + r) / 2;
        update(id * 2, l, mid, u, val);
        update(id * 2 + 1, mid + 1, r, u, val);
        ST[id] = Merge(ST[id * 2], ST[id * 2 + 1]);
    }

    node get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) {
            return node(-INF_LL, -INF_LL, -INF_LL, 0);
        }
        if (l >= u && r <= v) {
            return ST[id];
        }
        int mid = (l + r) / 2;
        node left = get(id * 2, l, mid, u, v);
        node right = get(id * 2 + 1, mid + 1, r, u, v);
        node res = Merge(left, right);
        return res;
    }
};

int v[maxN][7];
SegmentTree st[7][2];
void sol() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int d;
        cin >> v[i][0] >> d;
        for (int j = 1; j <= 3; j++) v[i][j] = v[i][0] + j * d;
        for (int j = 4; j <= 6; j++) v[i][j] = v[i][0] + (6 - j) * d;
    }
    for (int d = 0; d < 7; d++) {
        for (int i = 0; i < n - 1; i++) {
            int j = (d + i) % 7;
            int nj = (j + 1) % 7;
            st[d][0].update(1, 0, n - 1, i, v[i + 1][nj] - v[i][j]);
        }
        for (int i = n - 1; i > 0; i--) {
            int j = (d + (n - i - 1)) % 7;
            int nj = (j + 1) % 7;
            st[d][1].update(1, 0, n - 1, i, v[i - 1][nj] - v[i][j]);
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int s, t;
        cin >> s >> t;
        s--; t--;
        if (s < t) {
            int d = (7 - s % 7) % 7;
            cout << max(0LL, st[d][0].get(1, 0, n - 1, s, t - 1).val) << '\n';
        }
        else {
            int d = (7 - (n - s - 1) % 7) % 7;
            cout << max(0LL, st[d][1].get(1, 0, n - 1, t + 1, s).val) << '\n';
        }
    }
}

void solve() {
    int T;
    ///cin >> T;
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
