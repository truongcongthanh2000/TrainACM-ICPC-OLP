#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const int QQ = 3e5 + 10;
const int maxN = 3e5 + 100; ///maxN = 2e5 + 100 is not worked
const int maxM = 3e5 + 10;
const long long oo = 1e18;
const int module = 1e9 + 7;
const long double du = 1e-9;

void doc() {
    freopen(INP ".inp","r",stdin);
    freopen(OUT ".out","w",stdout);
}
struct Point {
    int x, yL, yR, type;
    Point(){};
    Point(int _x, int _yL, int _yR, int _type) : x(_x), yL(_yL), yR(_yR), type(_type) {};
    bool operator < (const Point &A) {
        if (x != A.x) return x < A.x;
        return type < A.type;
    }
};
struct Node {
    int X, Y;
    Node(){};
    Node(int _X, int _Y) : X(_X), Y(_Y) {};
};
vector <int> posY;
int Length(int yL, int yR) {
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
        }
        else {
            int mid = (L + R) >> 1;
            update(i << 1, L, mid, u, v, val);
            update(i << 1 | 1, mid, R, u, v, val);
        }
        if (IT[i].X >= 1) IT[i].Y = Length(L, R);
        else IT[i].Y = (L == R ? 0 : IT[i << 1].Y + IT[i << 1 | 1].Y);
    }

    void up_Y(int yL, int yR, int val) {
        update(1, 0, n - 1, yL, yR, val);
    }
};
long long Area(vector <Point> &a) {
    int m = (int)posY.size();
    IT_Area T(m);
    long long Res = 0;
    for (int i = 0; i < (int)a.size() - 1; i++) {
        int yL = lower_bound(posY.begin(), posY.end(), a[i].yL) - posY.begin();
        int yR = lower_bound(posY.begin(), posY.end(), a[i].yR) - posY.begin();
        T.up_Y(yL, yR, a[i].type);
        int X = a[i + 1].x - a[i].x;
        int Y = T.IT[1].Y;
        Res += 1LL * X * Y;
    }
    return Res;
}

struct IT_AreaLe {
    Node IT[maxN * 4];
    int n;
    int Lazy[maxN * 4];
    IT_AreaLe(){};
    IT_AreaLe(int _n) {
        n = _n;
        for (int i = 0; i < n * 4; i++) Lazy[i] = IT[i].X = IT[i].Y = 0;
    }
    void cn(int i, int L, int R) {
        if (Lazy[i] == 0) return;
        IT[i].Y = Length(L, R) - IT[i].Y;
        if (L + 1 < R) { ///L + 1 == R is leaf
            Lazy[i << 1] = (Lazy[i << 1] + Lazy[i]) % 2;
            Lazy[i << 1 | 1] = (Lazy[i << 1 | 1] + Lazy[i]) % 2;
        }
        Lazy[i] = 0;
    }
    void update(int i, int L, int R, int u, int v, int val) {
        cn(i, L, R);
        if (L >= v || R <= u) return;
        if (L >= u && R <= v) {
            Lazy[i] += val;
            cn(i, L, R);
        }
        else {
            int mid = (L + R) >> 1;
            update(i << 1, L, mid, u, v, val);
            update(i << 1 | 1, mid, R, u, v, val);
            IT[i].Y = IT[i << 1].Y + IT[i << 1 | 1].Y;
        }
    }

    void up_Y(int yL, int yR, int val) {
        update(1, 0, n - 1, yL, yR, val);
    }
};
long long AreaLe(vector <Point> &a) {
    int m = (int)posY.size();
    IT_AreaLe T(m);
    long long Res = 0;
    for (int i = 0; i < (int)a.size() - 1; i++) {
        int yL = lower_bound(posY.begin(), posY.end(), a[i].yL) - posY.begin();
        int yR = lower_bound(posY.begin(), posY.end(), a[i].yR) - posY.begin();
        T.up_Y(yL, yR, 1);
        int X = a[i + 1].x - a[i].x;
        int Y = T.IT[1].Y;
        Res += 1LL * X * Y;
    }
    return Res;
}
void solve() {
    int n;
    cin >> n;
    vector <Point> a;
    for (int i = 0; i < n; i++) {
        int xL, xR, yL, yR;
        cin >> xL >> yL >> xR >> yR;
        if (xL > xR) swap(xL, xR);
        if (yL > yR) swap(yL, yR);
        posY.push_back(yL);
        posY.push_back(yR);
        a.push_back(Point(xL, yL, yR, 1));
        a.push_back(Point(xR, yL, yR, -1));
    }
    {
        sort(a.begin(), a.end());
        sort(posY.begin(), posY.end());
        posY.resize(unique(posY.begin(), posY.end()) - posY.begin());
    }
    ///cout << AreaLe(a) << '\n';
    long long S = Area(a) - AreaLe(a);
    cout << S;
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    ///doc();
    solve();
}
