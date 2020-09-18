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

int a[maxN], h[maxN];
int res[maxN];
int b[maxN];
void sol() {
    int n, m, s, d;
    cin >> n >> m >> s >> d;
    int sum = 0;
    for (int i = 1; i <= s; i++) {
        cin >> a[i];
        sum += a[i];
        h[i] = i;
    }
    if (sum < m) {
        cout << "impossible";
        return;
    }
    sort(h + 1, h + 1 + s, [&](int i, int j) {
        return a[i] > a[j];
    });
    long double prob = 0;
    int index = 0;
    for (int len = 1; len <= s; len++) {
        for (int i = 1; i <= s; i++) {
            res[i] = 0;
            b[i] = a[i];
        }
        int tmp = n;
        for (int j = len; j >= 1; j--) {
            int x = min(tmp, d - b[h[j]]);
            tmp -= x;
            b[h[j]] += x;
            res[h[j]] = x;
            if (tmp <= 0) {
                int tmp_m = m;
                int num = 0;
                int n2 = 0;
                for (int i = 1; i <= s; i++) {
                    if (b[i] > 0) n2++;
                }
                for (int k = j - 1; k >= 1; k--) {
                    tmp_m -= a[h[k]];
                    num += b[h[k]] > 0;
                }
                if (tmp_m <= 0) {
                    long double p = (long double)num / n2;
                    if (p > prob) {
                        index = len;
                        prob = p;
                    }
                }
            }
        }
    }
    if (index == 0) {
        cout << "impossible";
        return;
    }
    for (int i = 1; i <= s; i++) res[i] = 0;
    int tmp = n;
    int  len = index;
    for (int j = len; j >= 1; j--) {
        int x = min(tmp, d - a[h[j]]);
        tmp -= x;
        res[h[j]] = x;
        if (tmp <= 0) {
            int tmp_m = m;
            for (int k = j - 1; k >= 1; k--) {
                tmp_m -= a[h[k]];
            }
            if (tmp_m <= 0) {
                for (int i = 1; i <= s; i++) cout << res[i] << ' ';
                return;
            }
        }
    }
}

void solve() {
    int T;
    //cin >> T;
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
