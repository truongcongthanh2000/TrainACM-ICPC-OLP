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
    int ax, ay;
    cin >> ax >> ay;
    int bx, by;
    cin >> bx >> by;
    map<pair<int, int>, int> M;
    vector<pair<int, int> > c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i].first >> c[i].second;
        M[c[i]] = 1;
    }
    M[{0, 0}] = true;
    auto canGet = [&](int sx, int sy, int tx, int ty) {
        if (sx == tx && sy == ty) return true;
        for (int i = 0; i < n; i++) {
            int u = sx + c[i].first;
            int v = sy + c[i].second;
            if (u >= 1 && u <= n && v >= 1 && v <= n) {
                if (M[{tx - u, ty - v}]) return true;
            }
        }   
        return false;
    };
    if (canGet(ax, ay, bx, by)) {
        cout << "Alice wins" << '\n';
        return;
    }
    for (int i = 0; i < 40; i++) {
        int x = rnd() % n + 1;
        int y = rnd() % n + 1;
        if (!canGet(bx, by, x, y)) {
            cout << "tie " << x << " " << y << '\n';
            return;
        }
    }
    cout << "Bob wins" << '\n';
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