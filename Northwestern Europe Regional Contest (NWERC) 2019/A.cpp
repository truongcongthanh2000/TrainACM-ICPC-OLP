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
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 10;

long long lazy[maxN * 4], IT[maxN * 4];

void push_down(int i, int L, int R) {
    IT[i] += lazy[i] * (R - L + 1);
    if (L != R) {
        lazy[i << 1] += lazy[i];
        lazy[i << 1 | 1] += lazy[i];
    }
    lazy[i] = 0;
}

void update(int i, int L, int R, int u, int v, int val) {
    push_down(i, L, R);
    if (L > v || R < u) return;
    if (L >= u && R <= v) {
        lazy[i] = val;
        push_down(i, L, R);
        return;
    }
    int mid = (L + R) >> 1;
    update(i << 1, L, mid, u, v, val);
    update(i << 1 | 1, mid + 1, R, u, v, val);
    IT[i] = IT[i << 1] + IT[i << 1 | 1];
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

int value[maxN];
long long res[maxN];
vector<int> adj[maxN];
vector<array<int, 3> > up[maxN];
void sol() {
    int n, w;
    cin >> n >> w;
    for (int i = 1; i <= n; i++) adj[i].push_back(0);
    for (int i = 1; i <= w; i++) {
        int sz;
        cin >> sz;
        vector<int> c(sz);
        for (int j = 0; j < sz; j++) {
            cin >> c[j];
            value[c[j]]++;
            adj[c[j]].push_back(i);
        }
    }
    for (int i = 1; i <= n; i++) adj[i].push_back(w + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (int)adj[i].size() - 1; j++) {
            int L = adj[i][j];
            int R = adj[i][j + 1];
            up[j].push_back({L, R - 1, i});
        }
    }
    for (int time = w; time >= 0; time--) {
        if ((int)up[time].size() == 0) continue;
        for (auto [L, R, i] : up[time]) {
            long long cost = get(1, 0, w, L, R);
            res[i] += cost;
        }
        for (auto [L, R, i] : up[time]) {
            update(1, 0, w, L, R, 1);
        }
    }
    cout << fixed << setprecision(10);
    for (int i = 1; i <= n; i++) {
        //cout << res[i] << ' ';
        res[i] += w;
        cout << (long double)res[i] / w << '\n';
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
