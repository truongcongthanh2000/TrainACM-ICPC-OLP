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
// const long double EPS = 1e-6;
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

const double PI = acos(-1.0);
#define double double
#define EPS 1e-6
struct point_t {
    double x, y;
    point_t() : x(0), y(0) {}
    point_t(double x, double y) : x(x), y(y) {}
    point_t(const point_t& p) : x(p.x), y(p.y) {}
    int operator<(const point_t& rhs) const { return make_pair(y, x) < make_pair(rhs.y, rhs.x); }
    int operator==(const point_t& rhs) const { return make_pair(y, x) == make_pair(rhs.y, rhs.x); }
    point_t operator+(const point_t& p) const { return point_t(x + p.x, y + p.y); }
    point_t operator-(const point_t& p) const { return point_t(x - p.x, y - p.y); }
    point_t operator*(double c) const { return point_t(x * c, y * c); }
    point_t operator/(double c) const { return point_t(x / c, y / c); }
    double norm() { return x * x + y * y; }
};
double cross(point_t p, point_t q) { return p.x * q.y - p.y * q.x; }
double area(point_t a, point_t b, point_t c) { return fabs(cross(a, b) + cross(b, c) + cross(c, a)) / 2; }
double area2(point_t a, point_t b, point_t c) { return cross(a, b) + cross(b, c) + cross(c, a); }
double dot(point_t p, point_t q) { return p.x * q.x + p.y * q.y; }
double dist(point_t p, point_t q) { return sqrt(dot(p - q, p - q)); }
double dist2(point_t p, point_t q) { return dot(p - q, p - q); }
point_t RotateCCW90(point_t p) { return point_t(-p.y, p.x); }
point_t RotateCW90(point_t p) { return point_t(p.y, -p.x); }
point_t RotateCCW(point_t p, double t) { return point_t(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t)); }
int sign(double x) { return x < -EPS ? -1 : x > EPS; }
int sign(double x, double y) { return sign(x - y); }
ostream& operator<<(ostream& os, const point_t& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

// Project c on Line(a, b)
point_t ProjectPointLine(point_t a, point_t b, point_t c) {
    return a + (b - a) * dot(c - a, b - a) / dot(b - a, b - a);
}

double angle(point_t a, point_t o, point_t b) {  // min of directed angle AOB & BOA
    a = a - o;
    b = b - o;
    return acos(dot(a, b) / sqrt(a.norm()) / sqrt(b.norm()));
}

void sol() {
    point_t O;
    double R;
    cin >> O.x >> O.y >> R;

    int n;
    cin >> n;
    vector<point_t> pt(n);
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        pt[i] = point_t(x, y);
    }

    auto transform = [&](point_t A) -> point_t {  // return AA
        auto dOA = dist(O, A);
        // OA * OAA = R * R
        auto dOAA = R * R / dOA;
        return O + point_t((A.x - O.x) * dOAA / dOA, (A.y - O.y) * dOAA / dOA);
    };

    auto dienTich = [&](point_t O, point_t A, point_t B, point_t X) -> double {
        if (area(A, B, O) < EPS) {
            return 0.0;
        }
        double R = dist(O, X) / 2;
        double AOX = abs(angle(A, O, X));
        double BOX = abs(angle(B, O, X));
        double AOB = abs(angle(A, O, B));
        assert(PI - 2 * AOX > 0);
        assert(PI - 2 * BOX > 0);
        double Saox = R * R * (sin(PI - 2 * AOX) / 2 + AOX);
        double Sbox = R * R * (sin(PI - 2 * BOX) / 2 + BOX);
        if (abs(AOX + BOX - AOB) < EPS) {
            return Saox + Sbox;
        }
        return abs(Saox - Sbox);
    };

    double ans = 0;
    for (int i = 0; i < n; i++) {
        point_t A = pt[i], B = pt[(i + 1) % n];
        point_t X = ProjectPointLine(A, B, O);
        double S = dienTich(O, transform(A), transform(B), transform(X));
        if (cross(A - O, B - O) < 0)
            ans += S;
        else
            ans -= S;
    }
    cout << fixed << setprecision(10) << abs(ans) << '\n';
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
