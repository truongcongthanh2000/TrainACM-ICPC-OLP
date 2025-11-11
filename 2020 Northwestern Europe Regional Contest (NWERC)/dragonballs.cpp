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

void sol(){
    int n;
    cin >> n;

    int num = 0;
    auto f = [&](int x, int y) {
        cout << x << " " << y << endl;
        long long d;
        cin >> d;
        num += d == 0;
        if (num == n) exit(0);
        return d;
    };
    
    for (int _ = 0; _ < n; _++) {
        int L = 0, R = 1e6;
        while (L < R) {
            int x1 = (L + L + R) / 3;
            int x2 = (L + R + R + 1) / 3;
            if (f(x1, 0) < f(x2, 0)) R = x2 - 1;
            else L = x1 + 1;
        }
        long long d = f(L, 0);
        f(L, (int)sqrt(d));
    }
}


void solve() {
    clock_t begin = clock();    int T;
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