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
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T>>& a) {
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
const int INF = 2e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e6 + 100;
const int MOD = 123456789;

struct Point {
    long long x, yL, yR;
    int type;
    Point(){};
    Point(long long _x, long long _yL, long long _yR, int _type) : x(_x), yL(_yL), yR(_yR), type(_type){};
    bool operator<(const Point& A) {
        if (x != A.x) return x < A.x;
        return type < A.type;
    }
};
struct Node {
    long long X, Y;
    Node(){};
};
vector<long long> posY;
long long Length(int yL, int yR) {
    return posY[yR] - posY[yL];
}

struct IT_Area {
    Node IT[maxN * 4];
    int n;
    IT_Area(){};
    IT_Area(int _n) {
        n = _n;
        for (int i = 0; i < n * 4; i++) IT[i].X = IT[i].Y = 0;
    }
    void update(int i, int L, int R, int u, int v, int val) {
        if (L >= v || R <= u) return;
        if (L >= u && R <= v) {
            IT[i].X += val;
        } else {
            int mid = (L + R) >> 1;
            update(i << 1, L, mid, u, v, val);
            update(i << 1 | 1, mid, R, u, v, val);
        }
        if (IT[i].X >= 1)
            IT[i].Y = Length(L, R);
        else
            IT[i].Y = (L == R ? 0 : IT[i << 1].Y + IT[i << 1 | 1].Y);
    }

    void up_Y(int yL, int yR, int val) {
        update(1, 0, n - 1, yL, yR, val);
    }
};
long long Area(vector<Point>& a) {
    int m = (int)posY.size();
    IT_Area T(m);
    long long Res = 0;
    for (int i = 0; i < (int)a.size() - 1; i++) {
        long long yL = lower_bound(posY.begin(), posY.end(), a[i].yL) - posY.begin();
        long long yR = lower_bound(posY.begin(), posY.end(), a[i].yR) - posY.begin();
        T.up_Y(yL, yR, a[i].type);
        long long X = a[i + 1].x - a[i].x;
        long long Y = T.IT[1].Y;
        Res += X * Y;
    }
    return Res;
}

void sol() {
    int k, n;
    cin >> k >> n;
    long long x = 0, y = 0;
    vector<Point> a;
    for (int i = 0; i < n; i++) {
        char c;
        int d;
        cin >> c >> d;
        long long nx = x, ny = y;
        if (c == 'N') {
            ny -= d;
        }
        if (c == 'E') {
            nx += d;
        }
        if (c == 'S') {
            ny += d;
        }
        if (c == 'W') {
            nx -= d;
        }
        long long xL = min(x, nx);
        long long xR = max(x + k, nx + k);
        long long yL = min(y, ny);
        long long yR = max(y + k, ny + k);
        if (xL > xR) swap(xL, xR);
        if (yL > yR) swap(yL, yR);
        posY.push_back(yL);
        posY.push_back(yR);
        a.push_back(Point(xL, yL, yR, 1));
        a.push_back(Point(xR, yL, yR, -1));
        x = nx, y = ny;
    }
    sort(a.begin(), a.end());
    sort(posY.begin(), posY.end());
    posY.resize(unique(posY.begin(), posY.end()) - posY.begin());
    cout << Area(a) << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    // cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        // cerr << "Processing test = " << TestCase << '\n';
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
    solve();
    return 0;
}
