#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".txt","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

///Graham
struct Point {
    long long x, y;
    Point(){};
    Point(long long _x, long long _y) : x(_x), y(_y) {};
    bool operator < (const Point &A) {
        return make_pair(x, y) < make_pair(A.x, A.y);
    }
    bool operator <= (const Point &A) {
        return make_pair(x, y) <= make_pair(A.x, A.y);
    }
    bool operator > (const Point &A) {
        return make_pair(x, y) > make_pair(A.x, A.y);
    }
    bool operator >= (const Point &A) {
        return make_pair(x, y) >= make_pair(A.x, A.y);
    }
    bool operator == (const Point &A) {
        return make_pair(x, y) == make_pair(A.x, A.y);
    }
    bool operator != (const Point &A) {
        return !(*this == A);
    }
    friend ostream& operator << (ostream &os, const Point &A) {
        os << A.x << " " << A.y << '\n';
        return os;
    }
};

void Tru(Point &A,Point B) {
    A.x -= B.x;
    A.y -= B.y;
}
bool CungChieu(Point O,Point A,Point B) {
    Tru(A,O);
    Tru(B,O);
    return 1ll * A.x * B.y < 1ll * A.y * B.x;
}
bool NguocChieu(Point O,Point A,Point B) {
    Tru(A,O);
    Tru(B,O);
    return 1ll * A.x * B.y > 1ll * A.y * B.x;
}
bool ThangHang(Point O,Point A,Point B) {
    Tru(A,O);
    Tru(B,O);
    return 1ll * A.x * B.y == 1ll * A.y * B.x;
}
long long Dist(Point A,Point B) {
    long long X = B.x - A.x;
    long long Y = B.y - A.y;
    return X * X + Y * Y;
}

vector<Point> ConvexHull(vector<Point> &a) {
    int n = (int)a.size();
    int j = 0;
    for (int i = 1; i < n; i++) {
        if (a[i].y < a[j].y || (a[i].y == a[j].y && a[i].x < a[j].x)) {
            j = i;
        }
    }
    swap(a[0], a[j]);
    sort(a.begin() + 1, a.begin() + n, [&](Point A, Point B) {
        if (ThangHang(a[0], A, B)) {
            return Dist(a[0], A) < Dist(a[0], B);
        }
        return NguocChieu(a[0], A, B);
    });
    int m = 0;
    a.push_back(a[0]);
    for (int i = 0; i <= n; i++) {
        while (m >= 2 && !NguocChieu(a[m - 2],a[m - 1],a[i])) {
            m--;
        }
        a[m++] = a[i];
    }
    n = m - 1;
    a.resize(n);
    return a;
}

void sol() {
    int n = 4;
    vector<Point> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
    a = ConvexHull(a);
    if ((int)a.size() == 4) cout << "YES" << '\n';
    else cout << "NO" << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
