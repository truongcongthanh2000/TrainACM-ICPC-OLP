#include <bits/stdc++.h>

using namespace std;

void open_file() {
#ifdef THEMIS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif  // THEMIS
}

const int MOD = 998244353;

vector<pair<int, int> > xy;
void gen() {
    int limit = 1500;
    for (int i = 1; i < limit; i++) {
        for (int j = 1; j < limit; j++) {
            int x = i * i + j * j;
            int y = sqrt(x);
            if (y * y == x && __gcd(i, j) == 1) {
                xy.push_back({i, j});
            }
        }
    }
}

struct Point {
    int x, y;
};

long long dist(Point A, Point B) {
    int x = A.x - B.x;
    int y = A.y - B.y;
    return 1LL * x * x + 1LL * y * y;
}

void tru(Point &A, Point B) {
    A.x -= B.x;
    A.y -= B.y;
}

bool CungChieu(Point O, Point A, Point B) {
    tru(B, O);
    tru(A, O);
    return 1LL * A.x * B.y < 1LL * A.y * B.x;
}

bool NguocChieu(Point O, Point A, Point B) {
    tru(B, O);
    tru(A, O);
    return 1LL * A.x * B.y < 1LL * A.y * B.x;
}

bool ThangHang(Point O, Point A, Point B) {
    tru(B, O);
    tru(A, O);
    return 1LL * A.x * B.y == 1LL * A.y * B.x;
}

bool check(vector<pair<int, int> > pp) {
    int n = (int)pp.size();

    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        p[i].x = pp[i].first;
        p[i].y = pp[i].second;
    }

    for (int i = 0; i < n; i++) {
        if (!CungChieu(p[i], p[(i + 1) % n], p[(i + 2) % n])) {
            cout << p[i].x << " " << p[i].y << endl;
            cout << p[(i + 1) % n].x << " " << p[(i + 1) % n].y << endl;
            cout << p[(i + 2) % n].x << " " << p[(i + 2) % n].y << endl;
        }
        assert(CungChieu(p[i], p[(i + 1) % n], p[(i + 2) % n]));
    }
}
void sol() {
    gen();
    sort(xy.begin(), xy.end(), [&](pair<int, int> a, pair<int, int> b) {
        return a.first * b.second > a.second * b.first;
    });

    int n;
    cin >> n;

    if (n % 2 == 1) {
        int x = 0, y = -1e6;
        cout << "YES" << '\n';
        cout << x << " " << y << endl;
        n--;

        vector<pair<int, int> > ans;
        for (auto it : xy) {
            if (n == 0) break;
            x -= it.first;
            y += it.second;
            ans.push_back({x, y});
            n -= 2;
        }

        int R = (int)ans.size() - 1;
        while (R >= 0) {
            ans.push_back({-ans[R].first, ans[R].second});
            R--;
        }

        //        for (int i = 0; i < (int)ans.size(); i++) {
        //            int ni = (i + 1) % (int)ans.size();
        //            long long x = ans[ni].first - ans[i].first;
        //            long long y = ans[ni].second - ans[i].second;
        //            long long d = (x * x + y * y);
        //            long long u = sqrt(d);
        //            assert(u * u == d);
        //        }
        //        check(ans);
        for (auto it : ans) cout << it.first << " " << it.second << '\n';
    } else {
        int x = -1, y = -1e6;
        cout << "YES" << '\n';
        vector<pair<int, int> > ans;

        for (auto it : xy) {
            ans.push_back({x, y});
            x -= it.first;
            y += it.second;
            n -= 2;
            if (n == 0) break;
        }
        int R = (int)ans.size() - 1;
        while (R >= 0) {
            ans.push_back({-ans[R].first, ans[R].second});
            R--;
        }
        //        for (int i = 0; i < (int)ans.size(); i++) {
        //            int ni = (i + 1) % (int)ans.size();
        //            long long x = ans[ni].first - ans[i].first;
        //            long long y = ans[ni].second - ans[i].second;
        //            long long d = (x * x + y * y);
        //            long long u = sqrt(d);
        //            assert(u * u == d);
        //        }
        //        check(ans);
        for (auto it : ans) cout << it.first << " " << it.second << '\n';
    }
}
int main() {
    open_file();
    int t = 1;
    // cin >> t;
    while (t--) sol();
}
