#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const int Base = 30;
const long double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e5 + 5;

vector<vector<vector<long long> > > IT(2);

void build(int mask, int h, int i, int L, int R) {
    IT[mask][h][i] = -INF_LL;
    if (L == R) return;
    int mid = (L + R) >> 1;
    build(mask, h, i << 1, L, mid);
    build(mask, h, i << 1 | 1, mid + 1, R);
}
void update(int mask, int h, int i, int L, int R, int u, long long val) {
    if (L > u || R < u) return;
    if (L == R) {
        IT[mask][h][i] = val;
        return;
    }
    int mid = (L + R) >> 1;
    update(mask, h, i << 1, L, mid, u, val);
    update(mask, h, i << 1 | 1, mid + 1, R, u, val);
    IT[mask][h][i] = max(IT[mask][h][i << 1], IT[mask][h][i << 1 | 1]);
}

long long get(int mask, int h, int i, int L, int R, int u, int v) {
    if (L > v || R < u) return -INF_LL;
    if (L >= u && R <= v) return IT[mask][h][i];
    int mid = (L + R) >> 1;
    long long Left = get(mask, h, i << 1, L, mid, u, v);
    long long Right = get(mask, h, i << 1 | 1, mid + 1, R, u, v);
    return max(Left, Right);
}

vector<int> adj[maxN];

long long cost(int mask, int h, int u, int v) {
    u = lower_bound(adj[h].begin(), adj[h].end(), u) - adj[h].begin();
    v = upper_bound(adj[h].begin(), adj[h].end(), v) - adj[h].begin() - 1;
    return get(mask, h, 1, 0, (int)adj[h].size() - 1, u, v);
}

void up(int mask, int h, int u, long long val) {
    u = lower_bound(adj[h].begin(), adj[h].end(), u) - adj[h].begin();
    update(mask, h, 1, 0, (int)adj[h].size() - 1, u, val);
}
int h[maxN], p[maxN];
long long dp[maxN];
int nxt[maxN], prv[maxN];
int L[maxN], R[maxN];
void sol() {
    int n;
    cin >> n;
    vector<int> nen;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        nen.push_back(h[i]);
        p[i] = i;
    }
    sort(nen.begin(), nen.end());
    nen.resize(unique(nen.begin(), nen.end()) - nen.begin());
    for (int i = 1; i <= n; i++) {
        h[i] = lower_bound(nen.begin(), nen.end(), h[i]) - nen.begin();
        adj[h[i]].push_back(i);
    }
    sort(p + 1, p + 1 + n, [&](int i, int j) {
        return h[i] > h[j];
    });
    for (int i = 1; i <= n; i++) {
        L[i] = i;
        if (i > 1 && h[i] == h[i - 1]) L[i] = L[L[i - 1]];
        prv[i] = i;
        int j = i - 1;
        while (j >= 1 && h[i] >= h[j]) {
            prv[i] = prv[j];
            j = prv[j] - 1;
        }
    }
    for (int i = n; i >= 1; i--) {
        R[i] = i;
        if (i < n && h[i] == h[i + 1]) R[i] = R[R[i + 1]];
        nxt[i] = i;
        int j = i + 1;
        while (j <= n && h[i] >= h[j]) {
            nxt[i] = nxt[j];
            j = nxt[j] + 1;
        }
    }

    int m = (int)nen.size();
    for (int i = 0; i < 2; i++) IT[i].resize(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 2; j++) {
            IT[j][i].resize((int)adj[i].size() * 4);
            build(j, i, 1, 0, (int)adj[i].size() - 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        prv[i]--;
        nxt[i]++;
        dp[i] = 0;
    }
    for (int i = 1; i <= n; ) {
        int j = i;
        while (j <= n && h[p[j]] == h[p[i]]) {
            int id = p[j++];
            for (int j = 1, u = prv[id]; u >= 1 && j <= 1; j++) {
                int v = prv[u];
                dp[id] = max(dp[id], cost(0, h[u], v + 1, u) + id);
                u = v;
            }
            for (int j = 1, u = nxt[id]; u <= n && j <= 1; j++) {
                int v = nxt[u];
                dp[id] = max(dp[id], cost(1, h[u], u, v - 1) - id);
                u = v;
            }
        }
        for (int k = i; k < j; k++) {
            int id = p[k];
            up(0, h[id], id, dp[id] - id);
            up(1, h[id], id, dp[id] + id);
        }
        i = j;
    }
    for (int i = 1; i <= n; i++) cout << dp[i] << ' ';
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
    srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
