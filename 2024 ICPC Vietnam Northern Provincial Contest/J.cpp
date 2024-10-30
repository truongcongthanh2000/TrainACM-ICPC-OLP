#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<vector<T>> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) {
        for (const auto &value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (auto &x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-9;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

struct Point {
    int x, y;
    Point() {};
    Point(int _x, int _y) : x(_x), y(_y) {};
};
struct Circle {
    int x, y, S;
    Circle() {};
    Circle(int _x, int _y, int _SS) : x(_x), y(_y), S(_SS) {};
};
bool CheckNamCircleg(Point A, Circle B) {
    int x = A.x - B.x;
    int y = A.y - B.y;
    long long Dist = 1LL * x * x + 1LL * y * y;
    return Dist <= B.S * B.S;
}
bool CheckGiao(Circle A, Circle B) {
    int x = A.x - B.x;
    int y = A.y - B.y;
    long long Dist = 1LL * x * x + 1LL * y * y;
    return Dist <= (A.S + B.S) * (A.S + B.S);
}

struct DinicFlow {       /// Base 0-th, The vertices are numbered from 0 to n - 1
    const int oo = 2e9;  /// if flow > int, use long long
    int n, numEdge;
    vector<int> point, next, head, Dist, work;
    vector<int> flow, cap;  /// if flow > int, use long long

    DinicFlow(int _n = 0) {
        n = _n;
        numEdge = 0;
        head.assign(n + 7, -1);
        work.assign(n + 7, -1);
        Dist.assign(n + 7, 0);
    }

    void add_Edge(int u, int v, int c1, int c2 = 0) {  /// if flow > int, use long long c1, c2
        /// u -> v: c1
        point.push_back(v);
        flow.push_back(0);
        cap.push_back(c1);
        next.push_back(head[u]);
        head[u] = numEdge++;
        /// v -> u: c2
        point.push_back(u);
        flow.push_back(0);
        cap.push_back(c2);
        next.push_back(head[v]);
        head[v] = numEdge++;
    }

    bool BFS(int s, int t) {  /// check has path from s to t
        queue<int> Q;
        for (int i = 0; i <= n; i++) Dist[i] = -1;
        Dist[s] = 0;
        Q.push(s);
        while ((int)Q.size() != 0) {
            int u = Q.front();
            Q.pop();
            for (int i = head[u]; i >= 0; i = next[i]) {
                int v = point[i];
                if (flow[i] < cap[i] && Dist[v] == -1) {
                    Dist[v] = Dist[u] + 1;
                    if (v == t) return true;
                    Q.push(v);
                }
            }
        }
        return false;
    }

    int DFS(int s, int t, int f) {  /// if flow > int, use long long
        if (f == 0)                 /// Min F always >= 0 so if f = 0 break recursive
            return f;
        if (s == t)
            return f;
        for (int &i = work[s]; i >= 0; i = next[i]) {  ///&i so important, don't use i = work[s] because it's maybe TLE
            int v = point[i];
            if (flow[i] < cap[i] && Dist[v] == Dist[s] + 1) {
                int D = DFS(v, t, min(f, cap[i] - flow[i]));
                if (D > 0) {
                    flow[i] += D;
                    flow[i ^ 1] -= D;
                    return D;
                }
            }
        }
        return 0;
    }

    int maxFlow(int s, int t) {  /// if flow > int, use long long
        int Flow = 0;
        while (BFS(s, t)) {
            for (int i = 0; i <= n; i++) work[i] = head[i];
            while (true) {
                int d = DFS(s, t, oo);
                if (d == 0) break;
                Flow += d;
            }
        }
        return Flow;
    }

    int GetFlow(int idEdge) {
        return flow[idEdge];
    }
};

void sol() {
    // A cannot go pass to B if all sensor cover all region from top (y = W) to down (y = 0) ( * )
    // In graph, if 2 sensor are intersect, we will have edge between them,
    //      Also for sensor reach the top or down, build the edge between sensor with top/down  
    // For (*), it can present how many independent paths that top can go to the down. Each sensor can use at most 1 for all of the paths
    // It's based on maximum flow problem with each edge can use at most 1
    // To transform into vertices, we can split each vertex into out(-) and in(+).
    /* Graph flow:
        Source: top vertex s
        Target: down vertex t
        Layer 1: All edge (s, sensor u): s -> vertex in u(+): cap = 1
        Layer 2: All vertex in u(+) -> vertex out u(-): cap = 1
        Layer 3: All edge (sensor u, sensor v): 
            vertex out v(-) -> vertex in u(+): cap = 1
            vertex out u(-) -> vertex in v(+): cap = 1
        Layer 4: All edge (sensor u, t): vertex out u(-) -> t: cap = 1 
    */
    int L, W, n;
    cin >> L >> W >> n;
    int s = 2 * n, t = 2 * n + 1;
    DinicFlow df(2 * n + 2);
    vector<Point> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
    for (int i = 0; i < n; i++) {
        if (a[i].y - 100 <= 0) {
            df.add_Edge(s, i, 1);
        }
        if (a[i].y + 100 >= W) {
            df.add_Edge(i + n, t, 1);
        }
        df.add_Edge(i, i + n, 1);
        for (int j = i + 1; j < n; j++) {
            if (CheckGiao(Circle(a[i].x, a[i].y, 100), Circle(a[j].x, a[j].y, 100))) {
                df.add_Edge(i + n, j, 1);
                df.add_Edge(j + n, i, 1);
            }
        }
    }
    cout << df.maxFlow(s, t) << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    // cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        // cout << "Case #" << TestCase << ": ";
        sol();
        // if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc, char *argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
