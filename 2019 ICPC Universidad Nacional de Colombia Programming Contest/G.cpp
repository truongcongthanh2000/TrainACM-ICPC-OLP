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

vector<int> adj[maxN];
int num[maxN];
int Used[maxN];

void DFS(int u, int d) {
    num[d]++;
    if (Used[u] == 1) return;
    for (int v : adj[u]) {
        DFS(v, d + 1);
    }
}
void sol() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> u;
        adj[u].push_back(i);
    }
    DFS(0, 0);
    int last = n;
    while (num[last] == 0) last--;
    int ans = 0;
    int sum = 0;
    for (int i = last; i > 0; i--) {
        ans++;
        sum += num[i];
        ans = max(ans, (sum + k - 1) / k);
    }
    cout << ans;
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
