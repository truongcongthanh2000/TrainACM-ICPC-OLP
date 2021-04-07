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

const int maxN = 3e5 + 100;

vector<int> adj[maxN];
void sol(){
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    set<int> A;
    for (int i = 1; i <= n; i++) A.insert(i);

    set<int> B;
    vector<int> path;
    vector<int> used(n + 1, 0);
    function<bool(int)> DFS = [&](int u) {
        A.erase(u);
        path.push_back(u);
        used[u] = 1;
        if ((int)A.size() == (int)B.size()) return true;
        for (int v : adj[u]) {
            if (used[v] == 0 && DFS(v)) return true;
        }
        if ((int)A.size() == (int)B.size()) return true;
        B.insert(u);
        path.pop_back();
        if ((int)A.size() == (int)B.size()) return true;
        return false;
    };
    assert(DFS(1) == true);
    cout << (int)path.size() << " " << (int)A.size() << '\n';
    for (int x : path) cout << x << ' ';
    cout << '\n';
    for (auto vec : {A, B}) {
        for (int x : vec) cout << x << ' ';
        cout << '\n';
    }
}


void solve() {
    clock_t begin = clock();
    int T;
    //cin >> T;
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