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

typedef pair<int, int> i2;
int firstplay[1234][1234];
int timeplay[1234][1234];
i2 last[1234];
vector<int> want[maxN];
int kid[maxN], toy[maxN];
void sol() {
    int n, m, d, e;
    cin >> n >> m >> d >> e;
    if (m < n) {
        cout << "impossible";
        return;
    }
    for (int i = 1; i <= n; i++) last[i] = i2(-1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) firstplay[i][j] = d + 1;
    }
    for (int i = 1; i <= e; i++) {
        int s, k, t;
        cin >> s >> k >> t;
        if (t) firstplay[k][t] = min(firstplay[k][t], s);
        if (last[k].first != -1) {
            timeplay[k][last[k].first] += s - last[k].second;
        }
        last[k] = i2(t, s);
    }
    for (int i = 1; i <= n; i++) {
        if (last[i].first != -1) {
            timeplay[i][last[i].first] += d - last[i].second;
        }
    }
    for (int i = 1; i <= n; i++) {
        want[i].resize(m);
        iota(want[i].begin(), want[i].end(), 1);
        sort(want[i].begin(), want[i].end(), [&](int a, int b) {
            return firstplay[i][a] > firstplay[i][b];
        });
    }
    for (int i = 1; i <= n; i++) {
        int j = i;
        while (j >= 1) {
            int t = want[j].back(); want[j].pop_back();
            if (kid[t] == 0 || timeplay[j][t] < timeplay[kid[t]][t]) {
                toy[j] = t;
                swap(j, kid[t]);
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << toy[i] << ' ';
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
