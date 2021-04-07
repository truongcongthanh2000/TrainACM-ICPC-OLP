#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 3e5 + 10;

struct Book {
    long long cost;
    int L, d;
    Book(){};
    bool operator < (const Book &A) {
        if (d != A.d) return d < A.d;
        return L > A.L;
    }
};

Book a[maxN];
void sol() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i].L >> a[i].d;
    sort(a + 1, a + 1 + n);
    long long l = 1, r = 1e15, res = r;
    while (l <= r) {
        long long mid = (l + r) >> 1;
        multiset<int> S;
        int miss = 0;
        long long time = 0;
        for (int i = 1; i <= n; i++) {
            time += a[i].L;
            S.insert(a[i].L);
            if (time > mid * a[i].d) {
                auto it = S.end();
                it--;
                time -= *it;
                S.erase(it);
                miss++;
            }
        }
        if (miss <= m) {
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    cout << res;
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
