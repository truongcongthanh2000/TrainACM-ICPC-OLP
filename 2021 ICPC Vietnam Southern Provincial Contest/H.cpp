#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".txt","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

vector<int> adj[maxN];
int cha[maxN];
vector<int> t, L[maxN];
int F[maxN];
int depth[maxN];
vector<int> vF[maxN];
void DFS(int u){
    t.push_back(u);
    for(int v : adj[u]){
        if (cha[v] == 0){
            cha[v] = u;
            depth[v] = depth[u] + 1;
            DFS(v);
            F[u] = max(F[v] + 1, F[u]);
            vF[u].push_back(F[v] + 1);
            L[u].push_back(v);
        }
    }
    sort(vF[u].begin(), vF[u].end());
    sort(L[u].begin(), L[u].end(), [&](int A, int B){
        return F[A] > F[B];
    });
}

int dp[maxN];

void sol() {
    int n, T;
    cin >> n >> T;
    for(int i = 0; i < n - 1; i++){
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int root = 1;
    for (int i = 1; i <= n; i++) {
        if ((int)adj[i].size() == 1) {
            root = i;
            break;
        }
    }
    cha[root] = -1;
    DFS(root);
    for (int u : t) {
        int v = cha[u];
        dp[u] = depth[u];
        if (v != -1) dp[u] = max(dp[u], dp[v] + 1);
        for (int nu : L[v]) {
            if (nu == u) continue;
            dp[u] = max(dp[u], F[nu] + 2);
            break;
        }
    }
    while (T--) {
        int x, t;
        cin >> x >> t;
        int ans = (int)L[x].size();
        ans -= lower_bound(vF[x].begin(), vF[x].end(), t + 1) - vF[x].begin();
        if (dp[x] >= t + 1) ans++;
        cout << ans << '\n';
    }
}

void solve() {
    int T = 1;
    //cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
