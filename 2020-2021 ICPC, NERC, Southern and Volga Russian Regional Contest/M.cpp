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

void sol(){
    int n;
    cin >> n;
    vector<vector<int> > s(n);
    map<int, int> id;
    int M = 0;
    int N = 0;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        M += k;
        s[i].resize(k);
        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            if (!id.count(x)) id[x] = N++;
            s[i][j] = id[x];
        }
        sort(s[i].begin(), s[i].end());
    }
    int block = (int)sqrt(M) + 1;
    vector<int> large, small;
    for (int i = 0; i < n; i++) {
        if ((int)s[i].size() >= block) large.push_back(i);
        else small.push_back(i);
    }

    int time = 0;
    vector<int> visited(N, 0);
    for (int u : large) {
        time++;
        for (int x : s[u]) visited[x] = time;
        for (int v = 0; v < n; v++) {
            if (u == v) continue;
            int d = 0;
            for (int val : s[v]) {
                d += visited[val] == time;
                if (d == 2) {
                    cout << u + 1 << " " << v + 1 << '\n';
                    return;
                }
            }
        }
    }

    vector<vector<int> > adj(N);
    for (int i = 0; i < n; i++) {
        for (int x : s[i]) adj[x].push_back(i);
    }
    vector<int> last(N, -1), pos(N, -1);
    for (int u = 0; u < N; u++) {
        for (int i : adj[u]) {
            if ((int)s[i].size() < block) {
                for (int j = 0; j < (int)s[i].size() && s[i][j] < u; j++) {
                    int v = s[i][j];
                    if (last[v] == u) {
                        cout << pos[v] + 1 << " " << i + 1 << '\n';
                        return;
                    }
                    last[v] = u;
                    pos[v] = i;
                }
            }
        }
    }

    cout << -1 << '\n';
}

void solve() {
    clock_t begin = clock();
    int T;
    cin >> T;
    //T = 1;
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
