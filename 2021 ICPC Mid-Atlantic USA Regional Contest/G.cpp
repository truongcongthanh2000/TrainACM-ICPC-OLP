#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T> >& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) {
        for (const auto& value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for (auto& x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-9;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
#ifdef THEMIS
    freopen(INP ".txt", "r", stdin);
    freopen(OUT ".txt", "w", stdout);
#endif  // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

template <typename T>
struct sum_2D {
    int n, m;
    vector<vector<T> > a;
    sum_2D(int _n, int _m) {
        n = _n;
        m = _m;
        a = vector<vector<T> >(n + 1, vector<T>(m + 1, 0));
    }

    void set_value(int x, int y, T value) {
        a[x][y] = value;
    }

    void precalc() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }

    T get(int xL, int yL, int xR, int yR) {
        return a[xR][yR] - a[xL - 1][yR] - a[xR][yL - 1] + a[xL - 1][yL - 1];
    }
};

/// Graham
struct Point {
    long long x, y;
    Point(){};
    Point(long long _x, long long _y) : x(_x), y(_y){};
    friend ostream& operator<<(ostream& os, const Point& A) {
        os << A.x << " " << A.y << '\n';
        return os;
    }
};

int S(Point A, Point B, Point C) {
    vector<Point> a = {A, B, C};
    a.push_back(A);
    int ans = 0;
    for (int i = 0; i < 3; i++) {
        ans += (a[i + 1].x - a[i].x) * (a[i + 1].y + a[i].y);
    }
    return ans;
}
void sol() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    cin >> s;

    auto id = [&](int x, int y, int delta = 0) {
        return x * (m + delta) + y;
    };

    auto check = [&](int xL, int yL, int xR, int yR) {
        Point A(xL, yL), B(xR + 1, yR + 1);
        int x = xL, y = yL;
        while (x != xR || y != yR) {
            if (s[x][y] == '#') {
                return false;
            }
            int area = S(A, Point(x + 1, y + 1), B);
            if (area < 0)
                y++;
            else {
                if (area == 0) {
                    x++;
                    y++;
                } else
                    x++;
            }
        }
        return s[xR][yR] != '#';
    };

    vector<vector<pair<int, double> > > adj(n * (m + 1) + 2 * m);
    auto addEdge = [&](int u, int v, double d) {
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int vertexL = id(i, j, 1);
            addEdge(vertexL, vertexL + 1, 1);
            addEdge(vertexL, vertexL + m + 1, 1);
            addEdge(vertexL + 1, vertexL + m + 2, 1);
            addEdge(vertexL + m + 1, vertexL + m + 2, 1);
            for (int u = i; u < n; u++) {
                for (int v = j; v < m; v++) {
                    if (check(i, j, u, v)) {
                        int vertexR = id(u, v, 1) + 2 + m;
                        double dist = sqrt((u - i + 1) * (u - i + 1) + (v - j + 1) * (v - j + 1));
                        addEdge(vertexL, vertexR, dist);
                    }
                }
            }
        }
    }

    typedef pair<double, int> i2;
    priority_queue<i2, vector<i2>, greater<i2> > Q;

    vector<double> d(n * (m + 1) + 2 * m, INF);
    d[id(0, 0)] = 0;
    Q.push({0, id(0, 0)});
    while ((int)Q.size() > 0) {
        i2 A = Q.top();
        Q.pop();
        int u = A.second;
        double du = A.first;
        if (abs(d[u] - du) > EPS) continue;
        for (auto it : adj[u]) {
            int v = it.first;
            double w = it.second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                Q.push({d[v], v});
            }
        }
    }
    cout << fixed << setprecision(10) << d[id(n - 1, m - 1, 1) + 2 + m];
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

int main(int argc, char* argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
