#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 8e18;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
//const int Base = 311;9
const long double EPS = 1e-10;
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

const int maxN = 1e6 + 100;

vector<int> adj[maxN];

int used[maxN];
int ans[maxN];
int L = 0, R = 0;

void DFS(int u, int pa) {
    vector<int> not_assign;
    int balance = 0;
    for (int v : adj[u]) {
        if (used[v] == 0) {
            not_assign.push_back(v);
        }
        else {
            if (ans[v] > ans[u]) balance++;
            else balance--;
        }
    }
    int sz = (int)not_assign.size();
    assert(abs(balance) <= 1);
    if (balance < 0) {
        for (int i = 0; i < (sz + 1) / 2; i++) {
            ans[not_assign[i]] = ++R;
            used[not_assign[i]] = 1;
        }
        for (int i = (sz + 1) / 2; i < sz; i++) {
            ans[not_assign[i]] = --L;
            used[not_assign[i]] = 1;
        }
    }
    else {
        for (int i = 0; i < (sz + 1) / 2; i++) {
            ans[not_assign[i]] = --L;
            used[not_assign[i]] = 1;

        }
        for (int i = (sz + 1) / 2; i < sz; i++) {
            ans[not_assign[i]] = ++R;
            used[not_assign[i]] = 1;
        }
    }
    for (int v : adj[u]) {
        if (v != pa) DFS(v, u);
    }
}
void sol(){
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    used[0] = 1;
    ans[0] = 0;
    DFS(0, -1);
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int i, int j) {
        return ans[i] < ans[j];
    });
    for (int x : p) cout << x << ' ';
    cout << '\n';
}

void solve() {
    clock_t begin = clock();
    int T;
//    cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        //cout << "Test " << TestCase << ": ";
        sol();
    }
    clock_t end = clock();
    cerr << "Time: " << fixed << setprecision(10) << (double)(end - begin) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
