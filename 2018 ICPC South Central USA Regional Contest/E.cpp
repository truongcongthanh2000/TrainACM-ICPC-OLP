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
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e5 + 1000;
struct DisjointSetUnion { ///Base 1th or Base 0th
    ///if u is root then p[u] < 0 and |p[u]| is size of the Set that u is root
    ///if u is not root then p[u] = x and x, u are belong the same Set
    int n;
    vector <int> p;
    DisjointSetUnion(){};
    DisjointSetUnion(int _n) {
        n = _n;
        p.assign(n + 7, -1); ///p[i] = -1 for all i
    }

    int find_root(int u) { ///find the root in the Set contain u
        if (p[u] < 0) return u; ///u is root
        return p[u] = find_root(p[u]); ///get the root and jump
    }

    void Union(int u, int v) {
        int x = find_root(u);
        int y = find_root(v);
        if (x == y) return;
        if (p[x] > p[y]) swap(x, y); ///small Set point to big Set, p[x] > p[y] so |p[x]| < |p[y]|
        p[x] += p[y];
        p[y] = x;
    }

    bool sameSet(int u, int v) {
        return find_root(u) == find_root(v);
    }

    int numSet() {
        int res = 0;
        for (int i = 1; i <= n; i++) res += p[i] < 0;
        return res;
    }
};

struct Circle{
    int x, y;
    double R;
    Circle (int _x, int _y, double _R) : x(_x), y(_y), R(_R){}
    double dis(Circle &A){
        double distance = (x - A.x) * (x - A.x) + (y - A.y) * (y - A.y);
        return sqrt(distance) - (R + A.R);
    }
};

struct Edge{
    int x, y;
    double dis;
    Edge(int _x, int _y, double _dis): x(_x), y(_y), dis(_dis){}
};

void sol(){
    int n;
    cin >> n;
    vector<Circle> c;
    for(int i = 0; i < n; i++){
        int x, y;
        double R;
        cin >> x >> y >> R;
        c.push_back(Circle(x, y, R));
    }

    vector<Edge> canh;
    for(int i = 0; i < n - 1; i++)
        for(int j = i + 1; j < n; j++)
            canh.push_back(Edge(i, j, c[i].dis(c[j])));
    sort(canh.begin(), canh.end(), [&](Edge A, Edge B){
        return A.dis < B.dis;
    });

    DisjointSetUnion DSU(n);
    double res = 0;
    for(Edge p : canh){
        int s = DSU.find_root(p.x);
        int t = DSU.find_root(p.y);
        if (s != t){
            DSU.Union(p.x, p.y);
            res += p.dis;
        }
    }
    cout << fixed << setprecision(10) << res;
}

void solve() {
    int T;
//    cin >> T;
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
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
