#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const int QQ = 3e5 + 10;
const int maxN = 3e5 + 10;
const int maxA = 1e6 + 10;
const long long oo = 1e16;
const int INF = 1e9 + 100;
const int MOD = 998244353;
const int Base = 30;
const long double du = 1e-9;
const string YES = "YES";
const string NO = "NO";
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void doc() {
    freopen(INP ".inp","r",stdin);
    freopen(OUT ".out","w",stdout);
}

struct FenwickTree{
    vector<int> fenwick;
    int N;
    FenwickTree(){};
    FenwickTree(int _N) {
        N = _N;
        fenwick = vector<int>(N + 1, 0);
    }

    void update(int x, int val) {
        for (; x <= N; x += x & (-x)) fenwick[x] += val;
    }

    int sum(int x) {
        int res = 0;
        for (; x; x -= x & (-x)) res += fenwick[x];
        return res;
    }

    int get(int L, int R) {
        return sum(R) - sum(L - 1);
    }
};

struct Point2D {
    int x, y;
    Point2D(){};
    Point2D(int _x, int _y) : x(_x), y(_y) {};
    bool operator < (const Point2D &A) {
        if (x != A.x) return x < A.x;
        return y < A.y;
    }
};

void sol() {
    ///Rotate 45 degree, |x1 - x2| + |y1 - y2| = abs(|xx1 - xx2|, |yy1 - yy2|);
    ///F(delta): number of pairwise distinct points A, B so Dist(A, B) <= delta
    ///Lenma: F(delta) <= F(delta + 1)
    ///So the answer is delta if delta is the lowest number that is F(delta) >= K
    ///Solution: Binary search delta, for each delta we calculate F(delta).
    vector<int> Nen;
    long long K;
    int n;
    cin >> n >> K;
    vector<Point2D> a(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i].x = x - y;
        a[i].y = x + y; ///Rotate 45 degree
        Nen.push_back(a[i].x);
        Nen.push_back(a[i].y);
    }

    function<void()> bruteForce = [&]() {
        vector<int> Dist;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x = abs(a[i].x - a[j].x);
                int y = abs(a[i].y - a[j].y);
                Dist.push_back(max(x, y));
            }
        }
        sort(Dist.begin(), Dist.end());
        for (int x : Dist) cout << x << ' ';
        cout << endl;
    };
    sort(a.begin(), a.end());

    sort(Nen.begin(), Nen.end());
    Nen.resize(unique(Nen.begin(), Nen.end()) - Nen.begin());
    function<int(int, int)> getID = [&](int x, int delta) { ///delta = 0: >= x; 1: <= x
        auto it = lower_bound(Nen.begin(), Nen.end(), x + delta);
        if (delta) it--;
        return it - Nen.begin() + 1;
    };

    int sz = (int)Nen.size();
    function<long long(int)> Fdelta = [&](int delta) {
        ///calculate pair (i, j) i < j:
        ///a[j].x - a[i].x <= delta
        ///|a[j].y - a[i].y| <= delta => a[i].y - delta <= a[j].y <= a[i].y + delta
        FenwickTree df(sz);
        int L = 0;
        long long res = 0;
        for (int i = 0; i < n; i++) {
            while (L < n && a[i].x - delta > a[L].x) df.update(getID(a[L++].y, 0), -1);
            int Ly = a[i].y - delta;
            int Ry = a[i].y + delta;
            int cost = df.get(getID(Ly, 0), getID(Ry, 1));
            res += cost;
            df.update(getID(a[i].y, 0), 1);
        }
        return res;
    };
    int L = 0;
    int R = Nen[sz - 1] - Nen[0];
    int res = R;
    while (L <= R) {
        int mid = L / 2 + R / 2 + (L % 2 + R % 2) / 2; ///be careful use (L + R) / 2, it maybe wrong be cause (L + R) >= 2^31
        long long F = Fdelta(mid);
        if (F >= K) {
            res = mid;
            R = mid - 1;
        }
        else L = mid + 1;
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
        ///cout << "Case #" << TestCase << ": ";
        sol();
    }
}

int main(int argc,char *argv[]) {
    srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
