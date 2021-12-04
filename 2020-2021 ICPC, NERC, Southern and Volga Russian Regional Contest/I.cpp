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
    int xa, ya, xb, yb;
    cin >> xa >> ya >> xb >> yb;
    if (abs(1LL * xa * yb - 1LL * xb * ya) != n) {
        cout << "NO";
        return;
    }
    if (xa < 0) {
        xa *= -1;
        ya *=  -1;
    }
    if (xb < 0) {
        xb *= -1;
        yb *= -1;
    }
    if (xa == 0) {
        xa += xb;
        ya += yb;
    }
    if (xb == 0) {
        xb += xa;
        yb += ya;
    }
    while (xa != xb) {
        if (xa > xb) {
            xa -= xb;
            ya -= yb;
        }
        else {
            xb -= xa;
            yb -= ya;
        }
    }
    if (ya < yb) swap(ya, yb);
    //cout << xa << " " << ya << " " << yb << '\n';
    cout << "YES" << '\n';

    map<pair<int, int>, int> used;
    set<pair<int, int> > vv;
    auto print = [&](int x, int y) {
        assert(used[make_pair(x, y)] == 0);
        //cout << x << " " << y << '\n';
        vv.insert({x, y});
        used[make_pair(x, y)] = 1;
    };
    vector<pair<int, int> > tren;
    {
        int z = abs(__gcd(xa, ya));
        int x = 0, y = 0;
        for (int t = 1; t < z; t++){
            x += xa / z;
            y += ya / z;
            print(x, y);
            tren.push_back({x, y});
        }
    }
    vector<pair<int, int> > duoi;
    {
        int z = abs(__gcd(xa, yb));
        int x = 0, y = 0;
        for (int t = 1; t < z; t++){
            x += xa / z;
            y += yb / z;
            print(x, y);
            duoi.push_back({x, y});
        }
    }
    vector<pair<int, int> > v;
    for (int x = 0; x < xa; x++) {
        int upper = ceil(1.0 * ya / xa * x);
        int lower = floor(1.0 * yb / xa * x);
        //cout << lower + 1 << " " << upper - 1 << '\n';
        //cout << "num = " << (upper - lower - 1) * 2 << '\n';
        for (int y = lower + 1; y <= upper - 1; y++) {
            v.push_back({x, y});
            print(x, y);
            print(2 * xa - x, ya + yb - y);
        }
    }
    {
        //cout << "num = " << ya - yb - 1 << '\n';
        print(0, 0);
        for (int y = yb + 1; y < ya; y++) print(xa, y);
    }
    //cout << "size = " << (int)vv.size() << '\n';
    for (auto id : vv) cout << id.first << " " << id.second << '\n';
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
