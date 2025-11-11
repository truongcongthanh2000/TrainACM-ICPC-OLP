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
    int c1, c2, c3;
    cin  >> c1 >> c2 >> c3;
    int a1, a2, a3, b, c;
    cin >> a1 >> a2 >> a3 >> b >> c;
    c1 -= a1;
    c2 -= a2;
    c3 -= a3;
    if (c1 < 0 || c2 < 0 || c3 < 0){
        cout << "NO" << '\n';
        return;
    }
    int x = max(b - c1, 0);
    int y = max(c - c2, 0);
    if (x + y <= c3){
        cout << "YES" << '\n';
        return;
    }
    cout << "NO" << '\n';
}

void solve() {
    clock_t begin = clock();
    int T;
    cin >> T;
    //T = 1;
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
