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

vector<int> adj[maxN];
int h[maxN];
int get(int n, vector<string> &a) {
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        h[i] = i;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < i + 1; j++) {
            if (a[i][j] == '1') {
                adj[i + 1].push_back(j);
            }
            else {
                adj[j].push_back(i + 1);
            }
        }
    }
    sort(h, h + n, [&](int i, int j) {
        return (int)adj[i].size() < (int)adj[j].size();
    });
    int res = 0;
    int sum_outdegree = 0;
    for (int i = 0; i < n - 1; i++) {
        int cost = i * (i + 1) / 2;
        sum_outdegree += (int)adj[h[i]].size();
        cost = sum_outdegree - cost;
        res = max(res, cost);
    }
    return res;
}

void sol() {
    int n;
    cin >> n;
    vector<string> a(n - 1);
    for (int i = 0; i < n - 1; i++) cin >> a[i];
    int res = get(n, a);
    cout << res;
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
