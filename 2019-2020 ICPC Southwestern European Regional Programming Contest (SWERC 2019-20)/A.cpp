#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e6 + 10;

struct Point {
    int x, y;
    Point(){};
    Point(int _x, int _y) : x(_x), y(_y) {};
};

int Dist(Point A, Point B) {
    int x = A.x - B.x;
    int y = A.y - B.y;
    int z = x * x + y * y;
    int root_z = sqrt(z);
    while (root_z * root_z < z) root_z++;
    return root_z;
}
typedef pair<int, int> i2;
typedef pair<int, i2> i3;
vector<i3> adj[maxN];
int C[1234];
int d[1234][123];

void sol() {
    vector<Point> a;
    Point A;
    cin >> A.x >> A.y;
    Point B;
    cin >> B.x >> B.y;
    int B0;
    cin >> B0;
    cin >> C[0];
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) cin >> C[i];
    int N;
    cin >> N;
    a.push_back(A);
    for (int i = 0; i < N; i++) {
        Point X;
        cin >> X.x >> X.y;
        a.push_back(X);
        int L;
        cin >> L;
        while (L--) {
            int v;
            cin >> v;
            int ci;
            cin >> ci;
            adj[i + 1].push_back({v + 1, {C[ci], 0}});
            adj[v + 1].push_back({i + 1, {C[ci], 0}});
        }
    }
    a.push_back(B);
    for (int i = 1; i <= N; i++) {
        for (auto &it : adj[i]) {
            it.second.second = Dist(a[i], a[it.first]);
        }
    }
    for (int i = 0; i <= N + 1; i++) {
        for (int j = i + 1; j <= N + 1; j++) {
            if (i > 0 && j <= N) continue;
            adj[i].push_back({j, {C[0], Dist(a[i], a[j])}});
            adj[j].push_back({i, {C[0], Dist(a[i], a[j])}});
        }
    }
    for (int i = 0; i <= N + 1; i++) {
        for (int j = 0; j <= B0; j++) d[i][j] = INF;
    }
    priority_queue<i3, vector<i3>, greater<i3> > Q;
    d[0][0] = 0;
    Q.push({0, {0, 0}});
    while ((int)Q.size() != 0) {
        i3 A = Q.top(); Q.pop();
        int du = A.first;
        int u = A.second.first;
        int dd = A.second.second;
        if (d[u][dd] != du) continue;
        ///cout << u << " " << dd << " " << du << '\n';
        if (u == N + 1) {
            cout << du;
            return;
        }
        for (auto it : adj[u]) {
            int v = it.first;
            int ci = it.second.first;
            int dist = it.second.second;
            if (dd + dist <= B0) {
                if (d[v][dd + dist] > du + ci * dist) {
                    d[v][dd + dist] = du + ci * dist;
                    Q.push({d[v][dd + dist], {v, dd + dist}});
                }
            }
        }
    }
    cout << -1;
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
