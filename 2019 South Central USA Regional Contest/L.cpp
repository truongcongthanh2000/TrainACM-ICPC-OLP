#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

struct Point {
    double x, y;
    Point(){};
    Point(double _x, double _y) : x(_x), y(_y) {};
    Point(const Point &A) : x(A.x), y(A.y) {};
    int operator < (const Point &A) {
        return make_pair(x, y) < make_pair(A.x, A.y);
    }
    int operator == (const Point &A) {
        return make_pair(x, y) == make_pair(A.x, A.y);
    }
};

struct Circle {
    Point center;
    double r;
    Circle(){};
    Circle(double _x, double _y, double _r) : center(Point(_x, _y)), r(_r) {};
    Circle(Point _center, double _r) : center(_center), r(_r) {};
    Circle(const Circle &A) : center(A.center), r(A.r) {};
    int operator < (const Circle &A) {
        return r < A.r;
    }
};

double dist(Point A, Point B) {
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrtl(x * x + y * y);
}

bool inSide(Point A, Circle C) {
    return dist(A, C.center) <= C.r;
}

Point get_circle_center(double bx, double by,
                        double cx, double cy)
{
    double B = bx * bx + by * by;
    double C = cx * cx + cy * cy;
    double D = bx * cy - by * cx;
    return { (cy * B - by * C) / (2 * D),
             (bx * C - cx * B) / (2 * D) };
}

// Function to return a unique circle that
// intersects three points
Circle circle_three(Point A, Point B, Point C) {
    Point O = get_circle_center(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);
    O.x += A.x;
    O.y += A.y;
    return Circle(O, dist(O, A));
}

// Function to return the smallest circle
// that intersects 2 points
Circle circle_two(Point A, Point B) {
    // Set the center to be the midpoint of A and B
    Point O = Point((A.x + B.x) / 2.0, (A.y + B.y) / 2.0);

    // Set the radius to be half the distance AB
    return Circle(O, dist(A, B) / 2.0);
}

bool check_valid_circle(Circle C, vector<Point> p) {
    for (Point A : p) {
        if (!inSide(A, C)) return false;
    }
    return true;
}

// Function to return the minimum enclosing circle for N <= 3
Circle MEC_small(vector<Point> p) {
    assert((int)p.size() <= 3);
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

// Returns the MEC using Welzl's algorithm
// Takes a set of input points P and a set R
// points on the circle boundary.
// n represents the number of points in P
// that are not yet processed.
Circle welzl_helper(vector<Point>& P, vector<Point> R, int n)
{
    // Base case when all points processed or |R| = 3
    if (n == 0 || R.size() == 3) {
        return MEC_small(R);
    }

    // Pick a random point randomly
    int idx = rng() % n;
    Point p = P[idx];

    // Put the picked point at the end of P
    // since it's more efficient than
    // deleting from the middle of the vector
    swap(P[idx], P[n - 1]);

    // Get the MEC circle C from the
    // set of points P - {p}
    Circle C = welzl_helper(P, R, n - 1);

    // If C contains p, return C
    if (inSide(p, C)) {
        return C;
    }

    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);

    // Return the MEC for P - {p} and R U {p}
    return welzl_helper(P, R, n - 1);
}

///minimum enclosing circle O(N)
Circle MEC(vector<Point> p) {
    int n = (int)p.size();
    random_shuffle(p.begin(), p.end());
    return welzl_helper(p, {}, n);
}

///minimum enclosing circle O(N)
Circle get(vector<double> &x, vector<double> &y) {
    int n = (int)x.size();
    vector<Point> p(n);
    for (int i = 0; i < n; i++) p[i] = Point(x[i], y[i]);
    return MEC(p);
}

void sol() {
    int n;
    cin >> n;
    vector<double> x(n), y(n), z(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> z[i];
    Circle C1 = get(x, y);
    Circle C2 = get(x, z);
    Circle C3 = get(y, z);
    cout << fixed << setprecision(20);
    cerr << C1.r << " " << C2.r << " " << C3.r << '\n';
    cout << min(C1.r, min(C2.r, C3.r)) * 2.0;
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
