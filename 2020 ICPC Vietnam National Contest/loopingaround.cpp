#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 998244353;
const int Base = 30;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

int IT[maxN * 4];

void build(int i, int L, int R) {
    IT[i] = 0;
    if (L == R) return;
    int mid = (L + R) >> 1;
    build(i << 1, L, mid);
    build(i << 1 | 1, mid + 1, R);
}
void update(int i, int L, int R, int u, int val) {
    if (L > u || R < u) return;
    if (L == R) {
        IT[i] += val;
        return;
    }
    int mid = (L + R) >> 1;
    update(i << 1, L, mid, u, val);
    update(i << 1 | 1, mid + 1, R, u, val);
    IT[i] = IT[i << 1] + IT[i << 1 | 1];
}

int get(int i, int L, int R, int u, int v) {
    if (L > v || R < u) return 0;
    if (L >= u && R <= v) return IT[i];
    int mid = (L + R) >> 1;
    int left = get(i << 1, L, mid, u, v);
    int right = get(i << 1 | 1, mid + 1, R, u, v);
    return left + right;
}

struct DisjointSetUnion { ///Base 1th or Base 0th
    ///if u is root then p[u] < 0 and |p[u]| is size of the Set that u is root
    ///if u is not root then p[u] = x and x, u are belong the same Set
    int n;
    vector <int> p;
    DisjointSetUnion(){};
    DisjointSetUnion(int _n) {
        n = _n;
        p.assign(n + 7, -1); ///p[i] = -1 for all i
    }

    int find_root(int u) { ///find the root in the Set contain u
        if (p[u] < 0) return u; ///u is root
        return p[u] = find_root(p[u]); ///get the root and jump
    }

    void Union(int u, int v) {
        int x = find_root(u);
        int y = find_root(v);
        if (x == y) return;
        if (p[x] > p[y]) swap(x, y); ///small Set point to big Set, p[x] > p[y] so |p[x]| < |p[y]|
        p[x] += p[y];
        p[y] = x;
    }

    bool sameSet(int u, int v) {
        return find_root(u) == find_root(v);
    }

    int numSet() {
        int res = 0;
        for (int i = 1; i <= n; i++) res += p[i] < 0;
        return res;
    }
};

struct Point {
    int x, y, id;
    Point(){};
    bool operator < (const Point &A) {
        if (x != A.x) return x < A.x;
        return y < A.y;
    }
};

struct Line {
    //type = 0: x y -1: update
    //type = 1: x yL yR //query
    //val = +- 1: update
    int a, b, c, type, val;
    Line(){};
    Line(int _a, int _b, int _c, int _type, int _val) {
        a = _a;
        b = _b;
        c = _c;
        type = _type;
        val = _val;
    }
    bool operator < (const Line &A) {
        if (a != A.a) return a < A.a;
        if (b != A.b) return b < A.b;
        if (type != A.type) return type < A.type;
        if (b != A.b) return b < A.b;
        return c < A.c;
    }
};

Point a[maxN];

void sol() {
    int n;
    cin >> n;
    vector<int> p;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].id = i;
        p.push_back(a[i].x);
        p.push_back(a[i].y);
    }
    sort(p.begin(), p.end());
    p.resize(unique(p.begin(), p.end()) - p.begin());
    int m = (int)p.size();
    build(1, 0, m - 1);

    vector<Line> L;
    DisjointSetUnion dsu(n);
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ){
        int j = i;
        while (j <= n && a[j].x == a[i].x) j++;
        int d = j - i;
        if (d % 2 == 1) {
            cout << "NO" << '\n';
            return;
        }
        for (int k = i; k < j; k += 2) {
            L.push_back({a[k].x, a[k].y, a[k + 1].y, 1, 0});
            int u = a[k].id;
            int v = a[k + 1].id;
            dsu.Union(u, v);
        }
        i = j;
    }
    for (int i = 1; i <= n; i++) swap(a[i].x, a[i].y);
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ){
        int j = i;
        while (j <= n && a[j].x == a[i].x) j++;
        int d = j - i;
        if (d % 2 == 1) {
            cout << "NO" << '\n';
            return;
        }
        for (int k = i; k < j; k += 2) {
            L.push_back({a[k].y, a[k].x, -1, 0, 1});
            L.push_back({a[k + 1].y, a[k].x, -1, 0, -1});
            int u = a[k].id;
            int v = a[k + 1].id;
            dsu.Union(u, v);
        }
        i = j;
    }
    if (dsu.numSet() > 1) {
        cout << "NO" << '\n';
        return;
    }
    sort(L.begin(), L.end());
    int sz = (int)L.size();
    for (int i = 0; i < sz; ) {
        int j = i;
        while (j < sz && L[i].a == L[j].a) j++;
        for (int k = i; k < j; k++) {
            if (L[k].type == 1) {
                int x = lower_bound(p.begin(), p.end(), L[k].b + 1) - p.begin();
                int y = lower_bound(p.begin(), p.end(), L[k].c) - p.begin() - 1;
                if (get(1, 0, m - 1, x, y) > 0) {
                    cout << "NO" << '\n';
                    return;
                }
            }
        }
        for (int k = i; k < j; k++) {
            if (L[k].type == 0) {
                int y = lower_bound(p.begin(), p.end(), L[k].b) - p.begin();
                update(1, 0, m - 1, y, L[k].val);
            }
        }
        i = j;
    }
    cout << "YES" << '\n';
}

void solve() {
    int T;
    cin >> T;
    //T = 1;
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
