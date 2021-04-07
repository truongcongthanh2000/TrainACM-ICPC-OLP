#pragma GCC diagnostic ignored "-Wunused-parameter"

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

const int maxN = 1e6 + 10;

void sol() {
    long double w, g, h, r;
    cin >> w >> g >> h >> r;

    auto F = [&](long double x) -> long double {
        return sqrtl((g - r) * (g - r) + x * x) + sqrtl((h - r) * (h - r) + (w - x) * (w - x));
    };
    long double x1 = 0, x2 = w, x3 = w * (g - r) / (h + g - r * 2);
    long double F1 = sqrtl(w * w + (g - h) * (g - h));
    long double F2 = F(x2);
    long double F3 = sqrtl(w * w + (g + h - 2 * r) * (g + h - 2 * r));
    cout << fixed << setprecision(10);
    cout << F1 << " " << F3 << '\n';
}

void solve() {
    int T;
    cin >> T;
    //T = 1;
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
