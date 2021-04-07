#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-9;
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

const int maxN = 2e6 + 1000;

struct taps {
    int t, a, b;
    taps(){};
    bool operator < (const taps &A) {
        return t < A.t;
    }
};

taps t[maxN];
int delta[maxN];
void sol() {
    int k;
    cin >> k;
    for (int i = 1; i <= k; i++) {
        cin >> t[i].t >> t[i].a >> t[i].b;
    }
    sort(t + 1, t + 1 + k);
    auto check = [&](int x, int y) {
        long long xy = 1LL * x * y;
        int sa = 0, sb = 0;
        for (int i = 1; i <= k; i++) {
            sa += t[i].a;
            sb += t[i].b;
        }
        if (sa > y || sb < y) return false;
        int tmp = sa;
        for (int i = 1; tmp < y && i <= k; i++) {
            int x = min(t[i].b - t[i].a, y - tmp);
            delta[i] = x;
            tmp += x;
            t[i].a += x;
        }
        long long s = 0;
        for (int i = 1; i <= k; i++) {
            s += 1LL * t[i].a * t[i].t;
        }
        for (int i = 1; i <= k; i++) {
            t[i].a -= delta[i];
            delta[i] = 0;
        }
        if (s > xy) return false;
        tmp = sa;
        for (int i = k; tmp < y && i >= 1; i--) {
            int x = min(t[i].b - t[i].a, y - tmp);
            delta[i] = x;
            tmp += x;
            t[i].a += x;
        }
        s = 0;
        for (int i = 1; i <= k; i++) {
            s += 1LL * t[i].a * t[i].t;
        }
        for (int i = 1; i <= k; i++) {
            t[i].a -= delta[i];
            delta[i] = 0;
        }
        return s >= xy;
    };
    int Q;
    cin >> Q;
    while (Q--) {
        int x, y;
        cin >> x >> y;
        if (check(x, y)) cout << "yes" << '\n';
        else cout << "no" << '\n';
    }
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
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
