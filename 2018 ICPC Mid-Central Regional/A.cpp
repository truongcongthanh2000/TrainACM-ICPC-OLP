#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "OB"
#define OUT "OB"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-7;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 3e5 + 10;

struct Point {
    double x, y;
    Point(){};
    Point(double _x, double _y) : x(_x), y(_y) {};
};

double dist(Point A, Point B) {
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt(x * x + y * y);
}

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

struct Edge{
    int x, y;
    double c;
    Edge(){};
    Edge(int _x, int _y, double _c) : x(_x), y(_y), c(_c) {};
};

vector<Edge> canh;
void sol() {
    int n, e, p;
    cin >> n >> e >> p;
    vector<Point> A = {{0, 0}};
    for(int i = 1; i <= n; i++){
        double x, y;
        cin >> x >> y;
        A.push_back(Point(x, y));
    }
    DisjointSetUnion DSU(n);

    for(int i = 1; i <= n; i++)
    for(int j = i + 1; j <= n; j++){
        canh.push_back(Edge(i, j, dist(A[i], A[j])));
    }

    sort(canh.begin(), canh.end(), [&](Edge A, Edge B){
        return A.c < B.c;
    });

    for(int i = 1; i <= e - 1; i++){
        DSU.Union(i, i + 1);
    }
    for(int i = 1; i <= p; i++){
        int x, y;
        cin >> x >> y;
        DSU.Union(x, y);
    }

    double res = 0;
    for(int i = 0; i < canh.size(); i++){
        int x = canh[i].x;
        int y = canh[i].y;
        if (DSU.find_root(x) != DSU.find_root(y)){
            DSU.Union(x, y);
            res += canh[i].c;
//            cout << x << " " << y << '\n';
        }
    }
    cout << res;
}

void solve() {
    int T;
    ///cin >> T;
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
