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

int n;
int h[maxN];
double calc(int g) {
    map<long long, int> M;
    M[0] = 0;
    long long s = 0;
    long long minS = 0;
    double res = 0;
    for (int i = 1; i <= n; i++) {
        int cost = h[i] - g;
        s += cost;
        if (s < minS) {
            minS = s;
            M[-s] = i;
        }
        else {
            auto it = M.lower_bound(-s);
            long long prev_s = it->first;
            int pos = it->second;
            if (pos == 0) {
                res = i;
            }
            else {
                int prev_cost = h[pos] - g;
                long long diff = -prev_s - s;
                double a = (double)diff / (double)prev_cost;
                res = max(res, a + i - pos);
            }
        }
    }
    return res;
}
void sol() {
    int k;
    cin >> n >> k;
    for (int i = 0; i <= n; i++) cin >> h[i];
    for (int i = n; i >= 1; i--) h[i] = h[i] - h[i - 1];
    while (k--) {
        long double x;
        cin >> x;
        int g = x * 10;
        double res = calc(g);
        reverse(h + 1, h + 1 + n);
        res = max(res, calc(g));
        if (res < 0.5) cout << "impossible" << '\n';
        else cout << fixed << setprecision(10) << res << '\n';
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
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
