#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 8e18;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
//const int Base = 311;9
const long double EPS = 1e-10;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 3e5 + 100;

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}
struct ps {
    int x, y;
    ps(int _x = 0, int _y = 1) {
        x = _x;
        y = _y;
        norm();
    }
    void norm() {
        int z = gcd(x, y);
        x /= z;
        y /= z;
        if (y < 0) {
            x *= -1;
            y *= -1;
        }
        if (x == 0) y = 1;
    } 
    bool operator < (const ps &other) const {
        return 1LL * x * other.y < 1LL * y * other.x;
    }
    bool operator == (const ps &other) const {
        return 1LL * x * other.y == 1LL * y * other.x;
    }
    bool operator >  (const ps &other) const {
        return 1LL * x * other.y > 1LL * y * other.x;
    }
};
void sol(){
    int n;
    cin >> n;
    vector<int> x(n), v(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> v[i];
    
    auto get = [&](int i, int j, bool &ok) {
        if (v[i] == v[j]) {
            ok = false;
            return ps();
        }
        if (1LL * (x[j] - x[i]) * (v[i] - v[j]) < 0) {
            ok = false;
            return ps();
        }
        ok = true;
        return ps(x[j] - x[i], v[i] - v[j]);
    };

    set<int> remain;
    set<pair<ps, int> > dist;

    auto add = [&](int i) {
        if ((int)remain.size() == 0 || *remain.rbegin() == i) return false;
        bool ok = false;
        int nxt = *remain.lower_bound(i + 1);
        ps d = get(i, nxt, ok);
        if (ok) {
            dist.insert({d, i});
            return true;
        }
        else return false;
    };
    auto del = [&]() {
        auto it = dist.begin();
        int i = it->second;
        int nxt = *remain.lower_bound(i + 1);
        //cout << i << " " << nxt << '\n';
        dist.erase(it);
        int first = *remain.begin();
        int last = *remain.rbegin();
        remain.erase(i);
        remain.erase(nxt);
        if (i != first) {
            auto it = remain.lower_bound(i);
            int prv = *prev(it);
            bool ok = false;
            ps d = get(prv, i, ok);
            if (ok) {
                dist.erase({d, prv});
            }
        }
        if (nxt != last) {
            auto it = remain.lower_bound(i);
            int next_nxt = *it;
            bool ok = false;
            ps d = get(nxt, next_nxt, ok);
            if (ok) {
                dist.erase({d, nxt});
            }
        }
        if (i != first && nxt != last) {
            auto it = remain.lower_bound(i);
            int prv = *prev(it);
            int next_nxt = *it;
            bool ok = false;
            ps d = get(prv, next_nxt, ok);
            if (ok) dist.insert({d, prv});
        }
    };
    for (int i = 0; i < n; i++) remain.insert(i);
    for (int i = 0; i < n - 1; i++) add(i);
    while ((int)dist.size() > 0) del();
    cout << (int)remain.size() << '\n';
    for (int x : remain) cout << x + 1 << ' ';
}


void solve() {
    clock_t begin = clock();
    int T;
    //cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        //cout << "Test " << TestCase << ": ";
        sol();
    }
    clock_t end = clock();
    cerr << "Time: " << fixed << setprecision(10) << (double)(end - begin) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}