#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".txt","r",stdin);
        freopen(OUT ".txt","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    int n;
    cin >> n;
    long long m;
    cin >> m;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

    auto ok = [&](long long x) {
        long long rm = m;
        for (int i = 0; i < n; i++) {
            long long use = x / (b[i] + 1);
            if (use > rm / a[i] / b[i]) return true;
            rm -= use * b[i] * a[i];
            if (rm <= 0) return true;

            long long t = x % (b[i] + 1);
            if (t > rm / a[i]) return true;
            rm -= t * a[i];
            if (rm <= 0) return true;
        }
        return false;
    };

    long long L = 1, R = 1e18, ans = R;
    while (L <= R) {
        long long mid = (L + R) >> 1;
        if (ok(mid)) {
            R = mid - 1;
            ans = mid;
        }
        else L = mid + 1;
    }
    cout << ans << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    //cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        //cout << "Case #" << TestCase << ": ";
        sol();
        //if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
