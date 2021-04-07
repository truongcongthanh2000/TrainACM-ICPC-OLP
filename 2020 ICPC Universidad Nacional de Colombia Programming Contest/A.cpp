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

const int maxN = 2e4 + 100;

struct Point {
    double x, y;
    Point(){};
    Point(double _x, double _y) : x(_x), y(_y) {};
    void normal() {
        double dist = sqrt(x * x + y * y);
        x /= dist;
        y /= dist;
    }
    bool operator == (const Point &A) {
        return abs(x - A.x) < EPS && abs(y - A.y) < EPS;
    }
};

double Dist(Point A, Point B) {
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt(x * x + y * y);
}

Point nxt(Point A, Point AB, double k) {
    A.x += AB.x * k;
    A.y += AB.y * k;
    return A;
}

double f(double t, Point A, Point B, Point C, Point D) {
    Point AB(B.x - A.x, B.y - A.y); AB.normal();
    Point CD(D.x - C.x, D.y - C.y); CD.normal();
    A = nxt(A, AB, t);
    C = nxt(C, CD, t);
    return Dist(A, C);
}

double f2(double t, Point A, Point B, Point C) {
    Point AB(B.x - A.x, B.y - A.y); AB.normal();
    A = nxt(A, AB, t);
    return Dist(A, C);
}
double minF(Point A, Point B, Point C, Point D) {
    Point AB(B.x - A.x, B.y - A.y); AB.normal();
    Point CD(D.x - C.x, D.y - C.y); CD.normal();
    cerr << AB.x << " " << AB.y << " " << CD.x << " " << CD.y << '\n';
    double res = Dist(A, C);
    res = min(res, Dist(B, D));
    if (Dist(AB, CD) != 0) {
        double t = (A.x - C.x) * (AB.x - CD.x) + (A.y - C.y) * (AB.y - CD.y);
        t /= Dist(AB, CD) * Dist(AB, CD);
        t *= -1.0;
        cerr << t << '\n';
        Point U = nxt(A, AB, t);
        Point V = nxt(C, CD, t);
        if (U.x >= min(A.x, B.x) && U.x <= max(A.x, B.x) && U.y >= min(A.y, B.y) && U.y <= max(A.y, B.y)) {
            res = min(res, Dist(U, V));
        }
    }
    cerr << res << '\n';
    return res;
}

double minF2(Point A, Point E, Point B, Point D) {
    Point AB(B.x - A.x, B.y - A.y); AB.normal();
	double res = 1e18;
	res = min(res, Dist(D, E));
	res = min(res, Dist(D, B));
	double t = (A.x - D.x) * AB.x + (A.y - D.y) * AB.y;
	t *= -1.0;
	//cerr << t << '\n';
	Point mid = nxt(A, AB, t);
//	cerr << res << '\n';
//	cerr << "F2: " << mid.x << " " << mid.y << '\n';
//	//res = min(res, Dist(D, mid));
//	cerr << "E: " << E.x << " " << E.y << '\n';
//	cerr << "B: " << B.x << " " << B.y << '\n';
	if (mid.x >= min(E.x, B.x) && mid.x <= max(E.x, B.x) && mid.y >= min(E.y, B.y) && mid.y <= max(E.y, B.y)) {
        res = min(res, Dist(D, mid));
	}
	//cerr << res << '\n';
	return res;
}

void sol() {
    Point A, B, C, D;
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;
    if (Dist(A, B) < Dist(C, D)) {
        swap(A, C);
        swap(B, D);
    }
    if (A == B) {
        cout << fixed << setprecision(12) << Dist(A, C);
        return;
    }
    if (C == D) {
        cout << fixed << setprecision(12) << minF2(A, A, B, C);
        return;
    }
    Point AB(B.x - A.x, B.y - A.y); AB.normal();
    Point CD(D.x - C.x, D.y - C.y); CD.normal();
    double dAB = Dist(A, B);
    double dCD = Dist(C, D);
    Point mid = nxt(A, AB, dCD);
    //cerr << mid.x << " " << mid.y << '\n';
    double res = min(minF(A, mid, C, D), minF2(A, mid, B, D));
    cout << fixed << setprecision(12) << res;
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
