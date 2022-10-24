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
const long double EPS = 1e-6;
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

/// minimum enclosing circle O(N)
/// https://www.geeksforgeeks.org/minimum-enclosing-circle-set-2-welzls-algorithm/
struct Point {
    double x, y;
    Point(){};
    Point(double _x, double _y) : x(_x), y(_y){};
    Point(const Point& A) : x(A.x), y(A.y){};
    int operator<(const Point& A) {
        return make_pair(x, y) < make_pair(A.x, A.y);
    }
    int operator==(const Point& A) {
        return abs(x - A.x) < EPS && abs(y - A.y) < EPS;
    }
};

struct Circle {
    Point center;
    double r;
    Circle(){};
    Circle(double _x, double _y, double _r) : center(Point(_x, _y)), r(_r){};
    Circle(Point _center, double _r) : center(_center), r(_r){};
    Circle(const Circle& A) : center(A.center), r(A.r){};
    int operator<(const Circle& A) {
        return r < A.r;
    }
};

double dist(Point A, Point B) {
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt(x * x + y * y);
}

bool inSide(Point A, Circle C) {
    return dist(A, C.center) <= C.r;
}

Point get_circle_center(double bx, double by,
                        double cx, double cy) {
    double B = bx * bx + by * by;
    double C = cx * cx + cy * cy;
    double D = bx * cy - by * cx;
    return {(cy * B - by * C) / (2 * D),
            (bx * C - cx * B) / (2 * D)};
}

Circle circle_three(Point A, Point B, Point C) {
    Point O = get_circle_center(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);
    O.x += A.x;
    O.y += A.y;
    return Circle(O, dist(O, A));
}

Circle circle_two(Point A, Point B) {
    Point O = Point((A.x + B.x) / 2.0, (A.y + B.y) / 2.0);
    return Circle(O, dist(A, B) / 2.0);
}

bool check_valid_circle(Circle C, const vector<Point>& p) {
    for (Point A : p) {
        if (!inSide(A, C)) return false;
    }
    return true;
}

// Function to return the minimum enclosing circle for N <= 3
Circle MEC_small(const vector<Point>& p) {
    if (p.empty()) return Circle(Point(0, 0), 0);
    if ((int)p.size() == 1) return Circle(p[0], 0);
    if ((int)p.size() == 2) return circle_two(p[0], p[1]);

    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            Circle C = circle_two(p[i], p[j]);
            if (check_valid_circle(C, p)) return C;
        }
    }
    Circle res = circle_three(p[0], p[1], p[2]);
    return res;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

Circle welzl_helper(vector<Point>& P, vector<Point> R, int n) {
    if (n == 0 || R.size() == 3) {
        return MEC_small(R);
    }

    int idx = rng() % n;
    Point p = P[idx];

    swap(P[idx], P[n - 1]);

    Circle C = welzl_helper(P, R, n - 1);

    if (inSide(p, C)) {
        return C;
    }

    R.push_back(p);

    return welzl_helper(P, R, n - 1);
}

/// minimum enclosing circle O(N)
Circle MEC(vector<Point>& p, int start, int n) {
    shuffle(p.begin() + start, p.begin() + n, rng);
    return welzl_helper(p, {}, n);
}

void sol() {
    int n;
    cin >> n;
    vector<Point> p(n * (n + 1) / 2);
    for (int i = 0; i < n * (n + 1) / 2; i++) cin >> p[i].x >> p[i].y;

    cout << fixed << setprecision(6);
    for (int i = 1; i <= n; i++) {
        Circle ans = MEC(p, i * (i - 1) / 2, i * (i + 1) / 2);

        cout << ans.center.x << " " << ans.center.y << " " << ans.r << '\n';
    }
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
    ios_base::sync_with_stdio(1);
    cin.tie(nullptr);
    cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
