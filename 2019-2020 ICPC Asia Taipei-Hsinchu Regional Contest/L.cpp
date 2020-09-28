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

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e5 + 10;

struct Point{
    int x,y;
    Point(){};
    Point (int a,int b) {
        x = a;
        y = b;
    }
};
int n;
Point a[maxN];
void Tru(Point &A,Point B) {
    A.x -= B.x;
    A.y -= B.y;
}
bool CungChieu(Point O,Point A,Point B) {
    Tru(A,O);
    Tru(B,O);
    return 1LL * A.x * B.y < 1LL * A.y * B.x;
}
bool NguocChieu(Point O,Point A,Point B) {
    Tru(A,O);
    Tru(B,O);
    return 1LL * A.x * B.y > 1LL * A.y * B.x;
}
bool ThangHang(Point O,Point A,Point B) {
    Tru(A,O);
    Tru(B,O);
    return 1LL * A.x * B.y == 1LL * A.y * B.x;
}
long long Dist(Point A,Point B) {
    long long X = A.x - B.x;
    long long Y = A.y - B.y;
    return X * X + Y * Y;
}
bool cmp(Point A,Point B) {
    return NguocChieu(a[0],A,B) || (ThangHang(a[0],A,B) && Dist(a[0],A) < Dist(a[0],B));
}
void FindPoint() {
    int j = 0;
    for (int i = 1; i < n; i++) {
        if (a[i].y < a[j].y || (a[i].y == a[j].y && a[i].x < a[j].x)) j = i;
    }
    swap(a[0],a[j]);
}

vector<Point> old;
void GraHam() {
    FindPoint();
    sort(a + 1, a + n,cmp);
    int m = 0;
    a[n] = a[0];
    for (int i = 0; i <= n; i++) {
        while (m >= 2 && !NguocChieu(a[m - 2],a[m - 1],a[i])) {
            old.push_back(a[m - 1]);
            m--;
        }
        a[m++] = a[i];
    }
    n = m - 1;
}

long long S(Point A,Point B,Point C) {
    Point stk[4];
    stk[0] = A; stk[1] = B; stk[2] = C; stk[3] = A;
    long long Res = 0;
    for (int i = 0; i < 3; i++) Res += 1ll * (stk[i + 1].x - stk[i].x) * (stk[i + 1].y + stk[i].y);
    return abs(Res);
}


long long S4(Point A,Point B,Point C,Point O) {
    long long s1 = S(O, A, B) + S(O, B, C);
    long long s2 = S(O, B, C) + S(O, C, A);
    long long s3 = S(O, C, A) + S(O, A, B);
    return max(s1, max(s2, s3));
}

long long F1[5005][5005], F2[5005][5005];

void sol() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
    old.clear();
    GraHam();
    if (n <= 2) {
        cout << 0 << '\n';
        return;
    }
    if (n == 3) {
        long long res = 0;
        for (Point b : old) {
            long long s1 = S4(a[0], a[1], a[2], b);
            res = max(res, s1);
        }
        cout << res / 2 << (res & 1 ? ".5" : "") << '\n';
        return;
    }
    for (int i = 0; i < n; i++) {
        int L = i;
        for (int j = (i + 1) % n; j != i; j = (j + 1) % n) {
            int nxtL = (L + 1) % n;
            while (S(a[i],a[L],a[j]) < S(a[i],a[nxtL],a[j])) L = nxtL;
            F1[i][j] = S(a[i], a[L], a[j]);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        int L = i;
        for (int j = (i - 1 + n) % n; j != i; j = (j - 1 + n) % n) {
            if (i == j) continue;
            int nxtL = (L - 1 + n) % n;
            while (S(a[i],a[L],a[j]) < S(a[i],a[nxtL],a[j])) L = nxtL;
            F2[i][j] = S(a[i], a[L], a[j]);
        }
    }
    long long Res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (abs(i - j) == 1) continue;
            if (F1[i][j] == 0 || F2[i][j] == 0) continue;
            Res = max(Res, F1[i][j] + F2[i][j]);
        }
    }
    cout << Res / 2 << (Res & 1 ? ".5" : "") << '\n';
}

void solve() {
    int T;
    cin >> T;
    ///T = 1;
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
