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
const int dx[6] = {0, 0, 1, -1, 1, -1};
const int dy[6] = {1, -1, 0, 0, 1, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 5e3 + 10;

void sol() {
    int n, q;
    cin >> n >> q;
    vector<vector<int> > h(n);
    vector<string> s(n);
    vector<int> p(n), id(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        int sz = (int)s[i].size();
        h[i].resize(sz + 1);
        for (int j = 1; j <= sz; j++) {
            h[i][j] = (1LL * h[i][j - 1] * Base + (int)s[i][j - 1]) % MOD;
        }
        p[i] = i;
    }
    auto LCP = [&](int i, int j) {
        int L = 1, R = min((int)s[i].size(), (int)s[j].size());
        int res = 0;
        while (L <= R) {
            int mid = (L + R) >> 1;
            if (h[i][mid] == h[j][mid]) {
                res = mid;
                L = mid + 1;
            }
            else R = mid - 1;
        }
        return res;
    };
    sort(p.begin(), p.end(), [&](int i, int j) {
        return s[i] < s[j];
    });
    for (int i = 0; i < n; i++) id[p[i]] = i;
    while (q--) {
        int k, L;
        cin >> k >> L;
        vector<int> x(k);
        for (int i = 0; i < k; i++) {
            cin >> x[i];
            x[i]--;
        }
        sort(x.begin(), x.end(), [&](int i, int j) {
            return id[i] < id[j];
        });
        int res = 0;
        for (int i = 0; i < k - L + 1; i++) {
            int cost = LCP(x[i], x[i + L - 1]);
            int cL = 0, cR = 0;
            if (i > 0) cL = LCP(x[i - 1], x[i]);
            if (i + L < k) cR = LCP(x[i], x[i + L]);
            res += cost - min(cost, max(cL, cR));
        }
        cout << res << '\n';
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
}
