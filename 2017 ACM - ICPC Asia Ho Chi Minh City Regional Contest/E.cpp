#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
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

const int maxN = 2e6 + 10;

template<class T, T oo> struct Hungary {
    static const int MAXN = 1000 + 5;
    static const int MAXM = 1000 + 5;
    int nx, ny, maty[MAXM], frm[MAXM], used[MAXM];
    T cst[MAXN][MAXM], fx[MAXN], fy[MAXM], dst[MAXM];
    void init(int nx, int ny) {
        this->nx = nx, this->ny = ny;
        fill_n(fx, nx + 1, 0), fill_n(fy, ny + 1, 0);
        fill_n(maty, nx + 1, 0);
        for (int i = 0; i <= nx; i++) {
            fill_n(cst[i], ny + 1, 0);
        }
    }
    void add(int x, int y, int c) {
        cst[x][y] = c;
    }
    T mincost() {
        for (int x = 1; x <= nx; x++) {
            int y0 = 0;
            maty[0] = x;
            for (int y = 0; y <= ny; y++) {
                dst[y] = oo + 1;
                used[y] = 0;
            }
            do {
                used[y0] = 1;
                int x0 = maty[y0], y1;
                T delta = oo + 1;
                for (int y = 1; y <= ny; y++) if (!used[y]) {
                    T curdst = cst[x0][y] - fx[x0] - fy[y];
                    if (dst[y] > curdst) {
                        dst[y] = curdst;
                        frm[y] = y0;
                    }
                    if (delta > dst[y]) {
                        delta = dst[y];
                        y1 = y;
                    }
                }
                for (int y = 0; y <= ny; y++) if (used[y]) {
                    fx[maty[y]] += delta;
                    fy[y] -= delta;
                }
                else {
                    dst[y] -= delta;
                }
                y0 = y1;
            }
            while (maty[y0] != 0);
            do {
                int y1 = frm[y0];
                maty[y0] = maty[y1];
                y0 = y1;
            }
            while (y0);
        }
        T res = 0;
        for (int y = 1; y <= ny; y++) {
            int x = maty[y];
            if (cst[x][y] < oo) res += cst[x][y];
        }
        return res;
    }
};
Hungary<int, (int) 1e9> hungary;
void sol() {
    int n, m, k;
    cin >> n >> m >> k;
    n = max(n, m);
    hungary.init(m, n);
    for (int i = 0; i < k; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        hungary.add(u, v, -w);
    }
    int cost = -hungary.mincost();
    cout << cost << '\n';
    vector<pair<int, int> > res;
    for (int i = 1; i <= n; i++) {
        int j = hungary.maty[i];
        if (hungary.cst[j][i]) res.push_back({j, i});
    }
    cout << (int)res.size() << '\n';
    for (auto it : res) cout << it.first << " " << it.second << '\n';
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
