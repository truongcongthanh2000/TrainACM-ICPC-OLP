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

vector<int> adj[maxN];

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
        prv[i] = i;
        int j = i - 1;
        while (j >= 1 && h[i] >= h[j]) {
            prv[i] = prv[j];
            j = prv[j] - 1;
        }
    }
    for (int i = n; i >= 1; i--) {
        nxt[i] = i;
        int j = i + 1;
        while (j <= n && h[i] >= h[j]) {
            nxt[i] = nxt[j];
            j = nxt[j] + 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        prv[i]--;
        nxt[i]++;
        dp[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        int u = prv[i];
        L[i] = lower_bound(adj[h[i]].begin(), adj[h[i]].end(), u + 1) - adj[h[i]].begin();
        L[i] = adj[h[i]][L[i]];
    }
    for (int i = 1; i <= n; i++) {
        int u = nxt[i];
        R[i] = lower_bound(adj[h[i]].begin(), adj[h[i]].end(), u) - adj[h[i]].begin() - 1;
        R[i] = adj[h[i]][R[i]];
    }
    for (int i = 1; i <= n; ) {
        int j = i;
        while (j <= n && h[p[j]] == h[p[i]]) {
            int id = p[j++];
            int u = prv[id], v = L[u];
            if (u >= 1) {
                dp[id] = max(dp[id], dp[u] + (id - u));
                dp[id] = max(dp[id], dp[v] + (id - v));
            }
            u = nxt[id], v = R[u];
            if (u <= n) {
                dp[id] = max(dp[id], dp[u] + (u - id));
                dp[id] = max(dp[id], dp[v] + (v - id));
            }
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
